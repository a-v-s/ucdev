MCU = STM32F103xB
TARGET = riscv32f103
ARCH=RISCV
SUBARCH=RV32IMAC
UCDEV_ROOT = ../../../
CUBEF1_CMSIS_INC_CORE=.
BUILD_SYSTEM_LIBRARY = 1


#######################################
# source of the library
#######################################


#C_SOURCES += $(CUBEF1_ROOT)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
#ASM_SOURCES +=  $(CUBEF1_ROOT)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_$(shell echo $(MCU) |  tr '[:upper:]' '[:lower:]').s

C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_i2c.c

C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal.c
#C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_cortex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_rcc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_rcc_ex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_gpio.c

C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_adc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_adc_ex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_can.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_cec.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_crc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_dac.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_dac_ex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_dma.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_eth.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_exti.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_flash.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_flash_ex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_gpio_ex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_hcd.c
# !! C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_i2c.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_i2s.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_irda.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_iwdg.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_mmc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_nand.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_nor.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pccard.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pcd.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pcd_ex.c
# !! C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pwr.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_rtc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_rtc_ex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_sd.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_smartcard.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_spi.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_sram.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_tim.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_tim_ex.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_uart.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_usart.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_wwdg.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_adc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_crc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_dac.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_dma.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_exti.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_fsmc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_gpio.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_i2c.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_pwr.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_rcc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_rtc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_sdmmc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_spi.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_tim.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_usart.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_usb.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_utils.c



include $(UCDEV_ROOT)/build/make/all.mk
