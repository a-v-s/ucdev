MCU?=STM32L151xB
TARGET = $(shell echo $(MCU) |  tr '[:upper:]' '[:lower:]')
UCDEV_ROOT = ../../../
BUILD_SYSTEM_LIBRARY = 1

#######################################
# source of the library
#######################################

C_SOURCES 	+= $(CUBEL1_CMSIS_DEV)/Source/Templates/system_stm32l1xx.c
ASM_SOURCES += $(CUBEL1_CMSIS_DEV)/Source/Templates/gcc/startup_$(shell echo $(MCU) |  tr '[:upper:]' '[:lower:]').s


C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_adc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_adc_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_comp.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_cortex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_crc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_cryp.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_cryp_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_dac.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_dac_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_dma.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_exti.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_flash.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_flash_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_flash_ramfunc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_gpio.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_i2c.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_i2s.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_irda.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_iwdg.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_lcd.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_msp_template.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_nor.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_opamp.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_opamp_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_pcd.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_pcd_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_pwr.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_pwr_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_rcc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_rcc_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_rtc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_rtc_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_sd.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_smartcard.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_spi.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_sram.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_tim.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_timebase_tim_template.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_tim_ex.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_uart.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_usart.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_hal_wwdg.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_adc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_comp.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_crc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_dac.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_dma.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_exti.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_fsmc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_gpio.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_i2c.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_opamp.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_pwr.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_rcc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_rtc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_sdmmc.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_spi.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_tim.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_usart.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_usb.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/stm32l1xx_ll_utils.c
C_SOURCES += $(CUBEL1_HAL_SRC_ROOT)/



include $(UCDEV_ROOT)/build/make/all.mk
