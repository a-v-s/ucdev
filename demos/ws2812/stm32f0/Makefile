################################################################################
# Set the MCU
################################################################################
MCU = STM32F030x6


################################################################################
# Set Output Filename 
################################################################################
TARGET = ws2812_demo

################################################################################
# Set the root directory of the ucdev enviorement 
################################################################################
UCDEV_ROOT=../../..


################################################################################
# Sources
################################################################################
C_SOURCES += main.c
# C_SOURCES += $(LIBHALGLUE_ROOT)/hal/stm32f0/clocksetup.c  # Not comatible with F030
C_SOURCES += $(LIBHALGLUE_ROOT)/common/bshal_delay.c
C_SOURCES += $(UCDEV_ROOT)/lib/libws2812dma/ws2812.c


C_INCLUDES += $(LIBHALGLUE_ROOT)/bshal/extlib/
C_INCLUDES += $(LIBHALGLUE_ROOT)/common/
C_INCLUDES += $(LIBHALGLUE_ROOT)/bshal/
C_INCLUDES += $(UCDEV_ROOT)//lib/libws2812dma/
C_INCLUDES += $(UCDEV_ROOT)//lib/libws2812dma/drivers



# link script
LDSCRIPT = STM32F030F4.ld

MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  



