MCU?=STM32L051xx
TARGET =  $(MCU)
UCDEV_ROOT = ../../../
BUILD_LIBRARY = 1

#######################################
# source of the library
#######################################

C_SOURCES 	+= $(CUBEL0_ROOT)/Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c
ASM_SOURCES += $(CUBEL0_ROOT)/Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_$(shell echo $(MCU) |  tr '[:upper:]' '[:lower:]').s

C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_adc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_adc_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_comp.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_comp_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_cortex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_crc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_crc_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_cryp.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_cryp_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_dac.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_dac_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_dma.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_exti.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_firewall.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_flash.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_flash_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_flash_ramfunc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_gpio.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_i2c.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_i2c_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_i2s.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_irda.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_iwdg.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_lcd.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_lptim.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_pcd.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_pcd_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_pwr.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_pwr_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_rcc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_rcc_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_rng.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_rtc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_rtc_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_smartcard.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_smartcard_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_smbus.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_smbus_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_spi.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_tim.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_tim_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_tsc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_uart.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_uart_ex.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_usart.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_hal_wwdg.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_adc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_comp.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_crc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_crs.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_dac.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_dma.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_exti.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_gpio.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_i2c.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_lptim.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_lpuart.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_pwr.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_rcc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_rng.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_rtc.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_spi.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_tim.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_usart.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_usb.c
C_SOURCES += $(CUBEL0_HAL_SRC_ROOT)/stm32l0xx_ll_utils.c


include $(UCDEV_ROOT)/build/make/all.mk
