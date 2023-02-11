
ifeq ($(BUILD_LIBRARY),1)
OUT_DIR     =   $(shell echo $(BUILD_MODE) | tr A-Z a-z)/$(shell echo $(ARCH) | tr A-Z a-z)_$(shell echo $(SUBARCH) | tr A-Z a-z)
BUILD_DIR 	= 	$(OUT_DIR)/build
else 
ifeq ($(BUILD_SYSTEM_LIBRARY),1)
OUT_DIR     =   $(shell echo $(BUILD_MODE) | tr A-Z a-z)
BUILD_DIR   =   $(OUT_DIR)/$(shell echo $(MCU) | tr A-Z a-z)/build
BUILD_LIBRARY=1
else
OUT_DIR     =   $(shell echo $(BUILD_MODE) | tr A-Z a-z)/$(shell echo $(MCU) | tr A-Z a-z)
BUILD_DIR   =   $(OUT_DIR)/build
endif
endif





################################################################################
## Add verbose option													       #
## https://stackoverflow.com/questions/9314322/controlling-verbosity-of-make   #
################################################################################
V ?= 0
ACTUAL_CC := $(CC)
CC_0 = @echo "Compiling $<..."; $(ACTUAL_CC)
CC_1 = $(ACTUAL_CC)
CC = $(CC_$(V))


ACTUAL_AS := $(AS)
AS_0 = @echo "Assembling $<..."; $(ACTUAL_AS)
AS_1 = $(ACTUAL_AS)
AS = $(AS_$(V))

ACTUAL_AR := $(AR)
AR_0 = @echo "Archiving $@..."; $(ACTUAL_AR)
AR_1 = $(ACTUAL_AR)
AR = $(AR_$(V))


#######################################
# build the application
#######################################

ifeq ($(COMPILER_TYPE),GCC)
    OBJ_SUFFIX = .o
endif

ifeq ($(COMPILER_TYPE),SDCC)
    OBJ_SUFFIX = .rel
endif


# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.c$(OBJ_SUFFIX))))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
# Handle both .s (eg STM32Cube) and .S (eg nrfx) asm files 
# TODO : .https://twitter.com/yannsionneau/status/1557994026464419841
# .s goes to $(AS)
# .S goes to $(CC) 

OBJ_ASM_TMP1 =  $(ASM_SOURCES:.s=.s$(OBJ_SUFFIX))
OBJ_ASM_TMP2 =  $(OBJ_ASM_TMP1:.S=.S$(OBJ_SUFFIX))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(OBJ_ASM_TMP2)  ))

vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

ifeq ($(BUILD_LIBRARY),1)
all: $(OUT_DIR)/lib$(TARGET).a
else
all: $(SLIB) $(OUT_DIR)/$(TARGET).elf $(OUT_DIR)/$(TARGET).hex $(OUT_DIR)/$(TARGET).bin
endif

clean: 
	-rm -rf $(BUILD_DIR) $(OUT_DIR)


$(BUILD_DIR)/%.c.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) $< -o $@
# Disabled the generation of assembly listing as this triggers a gcc bug
# causing corrupted DWARF debug data when building for RISCV
#	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.s.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.S.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

ifeq ($(COMPILER_TYPE),GCC)
$(OUT_DIR)/%.hex: $(OUT_DIR)/%.elf | $(OUT_DIR)
	$(HEX) $< $@
	
$(OUT_DIR)/%.bin: $(OUT_DIR)/%.elf | $(OUT_DIR)
	$(BIN) $< $@	

$(OUT_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(OUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -Wl,-Map=$(OUT_DIR)/$(TARGET).map,--cref -o $@
	$(SZ) $@

$(OUT_DIR)/lib$(TARGET).a: $(OBJECTS) Makefile $(OUT_DIR)
	$(AR) rcs $@ $(OBJECTS)
endif

ifeq ($(COMPILER_TYPE),SDCC)
$(BUILD_DIR)/%.c.rel: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) $(OPT) $< -l $(BUILD_DIR)/$<.lst -o $@


$(OUT_DIR)/%.hex: $(OBJECTS) Makefile $(OUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) --out-fmt-ihx -o $@
	
$(OUT_DIR)/%.bin: $(OUT_DIR)/%.hex | $(OUT_DIR)
	$(CP) -I ihex $<  $@

$(OUT_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(OUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) --out-fmt-elf -o $@
	$(SZ) $@
endif


	
$(BUILD_DIR):
	mkdir -p $@	

$(OUT_DIR):
	mkdir -p $@		
	
################################################################################
# Build the HAL as a static library
################################################################################



$(SLIB):
	echo Bulding $(SLIB)
#	make -C $(SLIB_BLD) TARGET=$(MCU) 
	make -C $(SLIB_BLD) MCU=$(MCU)

################################################################################
# Dependencies
################################################################################
-include $(wildcard $(BUILD_DIR)/*.d)



