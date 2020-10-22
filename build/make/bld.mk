OUT_DIR =   $(shell echo $(BUILD_MODE) | tr A-Z a-z)
BUILD_DIR = $(OUT_DIR)/build

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.c.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
# Handle both .s (eg STM32Cube) and .S (eg nrfx) asm files 
OBJ_ASM_TMP1 =  $(ASM_SOURCES:.s=.s.o)
OBJ_ASM_TMP2 =  $(OBJ_ASM_TMP1:.S=.S.o)

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(OBJ_ASM_TMP2)  ))

vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))



all: $(SLIB) $(OUT_DIR)/$(TARGET).elf $(OUT_DIR)/$(TARGET).hex $(OUT_DIR)/$(TARGET).bin

clean: 
	-rm -rf $(BUILD_DIR) $(OUT_DIR)


$(BUILD_DIR)/%.c.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.s.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
	
$(BUILD_DIR)/%.S.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@


$(OUT_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(OUT_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(OUT_DIR)/%.hex: $(OUT_DIR)/%.elf | $(OUT_DIR)
	$(HEX) $< $@
	
$(OUT_DIR)/%.bin: $(OUT_DIR)/%.elf | $(OUT_DIR)
	$(BIN) $< $@	

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



