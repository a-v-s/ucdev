TARGET ?= GD32F10X_MD
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

ASM_SOURCES += $(GD32F_CMSIS_SRC)/GCC/startup_$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).s
C_SOURCES += $(GD32F_CMSIS_SRC)/system_gd32f10x.c

C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_adc.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_bkp.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_can.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_crc.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_dac.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_dbg.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_dma.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_enet.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_exmc.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_exti.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_fmc.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_fwdgt.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_gpio.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_i2c.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_misc.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_pmu.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_rcu.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_rtc.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_sdio.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_spi.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_timer.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_usart.c
C_SOURCES += $(GD32F_STDPH_SRC)/gd32f10x_wwdgt.c




#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
AR = $(GCC_PATH)/$(PREFIX)ar
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
AR = $(PREFIX)ar
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
A = $(AR)
 

all: $(OUT_DIR) $(OUT_DIR)/lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a


#######################################
# build the library
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))


$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
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
