################################################################################
# Set the MCU
################################################################################
MCU = STM32F103xB

################################################################################
# Set Output Filename 
################################################################################
TARGET = radio_demo

################################################################################
# Set the root directory of the ucdev enviorement 
################################################################################
UCDEV_ROOT=../../..

################################################################################
# Sources
################################################################################
C_SOURCES += radio_test.c




C_SOURCES += $(LIBHALGLUE_ROOT)/hal/stm32f1/clocksetup.c
C_SOURCES += $(LIBHALGLUE_ROOT)/common/arm_cpuid.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_gpio_stm32.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_i2cm_stm32.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_spim_stm32f1.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_i2cm_stm32f1.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/bshal_i2cm.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/bshal_spim.c
C_SOURCES += $(LIBHALGLUE_ROOT)/common/bshal_delay.c


C_INCLUDES += $(LIBHALGLUE_ROOT)/bshal/
C_INCLUDES += $(LIBHALGLUE_ROOT)/common/

##### DISPLAY #####
CFLAGS += -DU8X8_WITH_USER_PTR
C_INCLUDES +=  $(UCDEV_ROOT)/ext/u8g2/csrc
LDFLAGS +=  -L$(UCDEV_ROOT)/build/staticlib/u8g2/debug/arm_m3  -lu8g2
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/extlib/u8x8_i2c.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/extlib/u8x8_gpio_delay.c
C_INCLUDES += $(LIBHALGLUE_ROOT)/bshal/extlib/

# link script
LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld

# SEMIHOSTING
#LDFLAGS += --specs=rdimon.specs -lc -lrdimon


MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  
