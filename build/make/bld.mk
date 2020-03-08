BUILD_DIR = build_$(shell echo $(BUILD_MODE) | tr A-Z a-z)
OUT_DIR = out_$(shell echo $(BUILD_MODE) | tr A-Z a-z)


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
# Handle both .s (eg STM32Cube) and .S (eg nrfx) asm files 
OBJ_ASM_TMP1 =  $(ASM_SOURCES:.s=.o)
OBJ_ASM_TMP2 =  $(OBJ_ASM_TMP1:.S=.o)

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(OBJ_ASM_TMP2)  ))

vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

SLIB=$(SLIB_DIR)/lib$(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).a

all: $(SLIB) $(OUT_DIR)/$(TARGET).elf $(OUT_DIR)/$(TARGET).hex $(OUT_DIR)/$(TARGET).bin

clean: 
	rm -rf $(BUILD_DIR) $(OUT_DIR)


$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
	
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
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
	mkdir $@	

$(OUT_DIR):
	mkdir $@		
	


################################################################################
$(SLIB):
	make -C $(SLIB_DIR) TARGET=$(MCU) 


