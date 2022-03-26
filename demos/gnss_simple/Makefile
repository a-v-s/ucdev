################################################################################
# Set the MCU
################################################################################
MCU?=STM32F103xB
#MCU?=STM32F411xE

DIS?=ST7735
################################################################################
# Set Output Filename 
################################################################################
TARGET = gnss_demo

################################################################################
# Set the root directory of the ucdev enviorement 
################################################################################
UCDEV_ROOT=../..


U8G2_DIR = $(UCDEV_ROOT)/ext/u8g2/csrc
UCG_DIR = $(UCDEV_ROOT)/ext/ucglib/csrc

################################################################################
# Sources
################################################################################


ASM_SOURCES += hf.s
C_SOURCES += main.c
C_SOURCES += i2c.c
C_SOURCES += nmea.c

C_SOURCES  += $(UCDEV_ROOT)/ext/minmea/minmea.c
C_INCLUDES +=  $(UCDEV_ROOT)/ext/minmea
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/bshal_uart.c


C_SOURCES  += $(UCDEV_ROOT)/ext/libgeohash/geohash.c
C_INCLUDES +=  $(UCDEV_ROOT)/ext/libgeohash


ifneq (,$(findstring STM32,$(MCU)))

	C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_uart_stm32.c
	C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_gpio_stm32.c
	C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_i2cm_stm32.c
	

	ifneq (,$(findstring F1,$(MCU)))
		C_SOURCES += $(LIBHALGLUE_ROOT)/hal/stm32f1/clocksetup.c		
		C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_spim_stm32f1.c
		C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_i2cm_stm32f1.c
		LDFLAGS +=  -L$(UCDEV_ROOT)/build/staticlib/u8g2/debug/arm_m3
		LDFLAGS +=  -L$(UCDEV_ROOT)/build/staticlib/ucg/debug/arm_m3
	endif

	ifneq (,$(findstring F4,$(MCU)))
		C_SOURCES += $(LIBHALGLUE_ROOT)/hal/stm32f4/clocksetup.c		
		C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_spim_stm32f4.c
		C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/stm32/bshal_i2cm_stm32f4.c
		LDFLAGS +=  -L$(UCDEV_ROOT)/build/staticlib/u8g2/debug/arm_m4f
		LDFLAGS +=  -L$(UCDEV_ROOT)/build/staticlib/ucg/debug/arm_m4f
	endif

endif

ifeq ($(DIS),SSD1306)
	CFLAGS += -DSSD1306
	C_SOURCES += dis_ssd1306.c
	C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/extlib/u8x8_i2c.c
	C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/extlib/u8x8_gpio_delay.c
	C_INCLUDES += $(U8G2_DIR) 
	CFLAGS += -DU8X8_WITH_USER_PTR
	LDFLAGS +=  -lu8g2
	
else 
ifeq ($(DIS),ST7735)
	CFLAGS += -DST7735
	C_SOURCES += dis_st7735.c
	# New hal ain't working yet
	C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/extlib/ucg_spi.c
	CFLAGS += -DUSE_OLD_HAL
	C_SOURCES += old_hal/ucglib_hal.c
	C_INCLUDES += old_hal
	C_INCLUDES += $(UCG_DIR)
	CFLAGS += -DWITH_USER_PTR
	LDFLAGS +=  -lucg
else
    $(error display "$(DISPLAY)" unknown)
endif
endif	









C_SOURCES += $(LIBHALGLUE_ROOT)/common/arm_cpuid.c
C_SOURCES += $(LIBHALGLUE_ROOT)/common/bshal_delay.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/bshal_i2cm.c
C_SOURCES += $(LIBHALGLUE_ROOT)/bshal/bshal_spim.c





################################################################################
# Includes
################################################################################


C_INCLUDES += $(LIBHALGLUE_ROOT)/bshal/extlib/
C_INCLUDES += $(LIBHALGLUE_ROOT)/common/
C_INCLUDES += $(LIBHALGLUE_ROOT)/bshal/


# link script
LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld



LDFLAGS += -u _printf_float


MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  
