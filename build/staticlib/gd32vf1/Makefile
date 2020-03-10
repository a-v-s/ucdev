TARGET ?= GD32VF103xB
MCU = $(TARGET)

UCDEV_ROOT = ../../..

include ../../make/dir.mk
include ../../make/mcu.mk
include ../../make/opt.mk

CFLAGS += -D$(TARGET)

#######################################
# paths
#######################################
# Build path
BUILD_DIR = BUILD_$(TARGET)_$(BUILD_MODE)

OUT_DIR = $(shell tr '[:upper:]' '[:lower:]' <<< $(BUILD_MODE))


######################################
# source
######################################
# C sources


C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_adc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_bkp.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_can.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_crc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_dac.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_dbg.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_dma.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_eclic.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_exmc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_exti.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_fmc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_fwdgt.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_gpio.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_i2c.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_pmu.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_rcu.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_rtc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_spi.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_timer.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_usart.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_wwdgt.c

C_SOURCES += $(GD32VF1_RISCV_DRV)/n200_func.c
C_SOURCES += $(GD32VF1_STDPH_ROOT)/system_gd32vf103.c

C_SOURCES += $(GD32VF1_ECLIPSE)/handlers.c
C_SOURCES += $(GD32VF1_ECLIPSE)/init.c

ASM_SOURCES += $(GD32VF1_ECLIPSE)/entry.S
ASM_SOURCES += $(GD32VF1_ECLIPSE)/start.S





all: $(OUT_DIR) $(OUT_DIR)/lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a


#######################################
# build the library
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))


$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
	
$(BUILD_DIR):
	mkdir $@		

$(OUT_DIR):
	mkdir $@		

$(OUT_DIR)/%.a: $(OBJECTS) Makefile
	$(AR) rcs $@ $(OBJECTS)



#######################################
# clean up
#######################################
clean:
	rm -fR $(BUILD_DIR)
	rm $(OUT_DIR)/lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
