OUT_DIR =   $(shell echo $(BUILD_MODE) | tr A-Z a-z)
BUILD_DIR = $(OUT_DIR)/build


################################################################################
## Add verbose option													       #
## https://stackoverflow.com/questions/9314322/controlling-verbosity-of-make   #
################################################################################
V ?= 0
ACTUAL_CC := $(CC)
CC_0 = @echo "Compiling $<..."; $(ACTUAL_CC)
CC_1 = $(ACTUAL_CC)
CC = $(CC_$(V))




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
OBJ_ASM_TMP1 =  $(ASM_SOURCES:.s=.s$(OBJ_SUFFIX))
OBJ_ASM_TMP2 =  $(OBJ_ASM_TMP1:.S=.S$(OBJ_SUFFIX))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(OBJ_ASM_TMP2)  ))

vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))



all: $(SLIB) $(OUT_DIR)/$(TARGET).elf $(OUT_DIR)/$(TARGET).hex $(OUT_DIR)/$(TARGET).bin

clean: 
	-rm -rf $(BUILD_DIR) $(OUT_DIR)


$(BUILD_DIR)/%.c.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.s.o $(BUILD_DIR)/%.S.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
	
$(BUILD_DIR)/%.c.rel: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) $< -l $(BUILD_DIR)/$<.lst -o $@





ifeq ($(COMPILER_TYPE),GCC)
$(OUT_DIR)/%.hex: $(OUT_DIR)/%.elf | $(OUT_DIR)
	$(HEX) $< $@
	
$(OUT_DIR)/%.bin: $(OUT_DIR)/%.elf | $(OUT_DIR)
	$(BIN) $< $@	

$(OUT_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(OUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
endif

ifeq ($(COMPILER_TYPE),SDCC)
$(OUT_DIR)/%.hex: $(OBJECTS) Makefile $(OUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) --out-fmt-ihx -o $@
	
$(OUT_DIR)/%.bin: $(OUT_DIR)/%.hex | $(OUT_DIR)
	$(CP) -I ihex $<  $@

$(OUT_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(OUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) --out-fmt-elf -o $@
	$(SZ) $@
endif


$(OUT_DIR)/%.a: $(OBJECTS) Makefile
	$(AR) rcs $@ $(OBJECTS)
	
$(BUILD_DIR):
	mkdir -p $@	

$(OUT_DIR):
	mkdir -p $@		
	
################################################################################
# Build the HAL as a static library
################################################################################
$(SLIB):
	make -C $(SLIB_BLD) TARGET=$(MCU) 

################################################################################
# Dependencies
################################################################################
-include $(wildcard $(BUILD_DIR)/*.d)



