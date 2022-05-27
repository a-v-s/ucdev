MCU=RV32F103
TARGET = $(shell echo $(MCU) |  tr '[:upper:]' '[:lower:]')

# Outdated stuff for when we were hacking support in before the build system
# supported it
#MCU = STM32F103xB
#TARGET = rv32f103
#ARCH=RISCV
#SUBARCH=RV32IMAC
#CUBEF1_CMSIS_INC_CORE=$(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103
#PREFIX=riscv-none-embed-

UCDEV_ROOT = ../../../
BUILD_SYSTEM_LIBRARY = 1


#######################################
# source of the library
#######################################


ASM_SOURCES += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/ch32.S
ASM_SOURCES += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/gd32.S
ASM_SOURCES += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/rv32f103.S
ASM_SOURCES += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/irq.S
ASM_SOURCES += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/gd32_intexc.S
C_SOURCES   += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/gd32_intexc.c
C_SOURCES   += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/ch32.c
C_SOURCES   += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/gd32.c
C_SOURCES   += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/common.c

C_SOURCES   += $(UCDEV_ROOT)/lib/libhalglue/compat/rv32f103/rv32f1xx_hal.c




C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_i2c.c
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
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_i2c.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_i2s.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_irda.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_iwdg.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_mmc.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_nand.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_nor.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pccard.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pcd.c
C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pcd_ex.c
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

#C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_usb.c			# Different peripherals

#C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_ll_utils.c		# Cortex-M specific
#C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal.c
#C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_cortex.c
#C_SOURCES += $(CUBEF1_HAL_SRC_ROOT)/stm32f1xx_hal_pwr.c 


include $(UCDEV_ROOT)/build/make/all.mk
