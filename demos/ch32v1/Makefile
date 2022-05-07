################################################################################
# Set the MCU
################################################################################
MCU ?= CH32V103

# Use the xPack compiler rather then the arch compiler
# The arch compiler appears to have issues with passing parameters to functions
PREFIX=riscv-none-embed-
#PREFIX=riscv32-unknown-elf-
################################################################################
# Set Output Filename 
################################################################################
TARGET = ch32v103_demo

CFLAGS += -DSTM32F103xB
################################################################################
# Set the root directory of the ucdev enviorement 
################################################################################
UCDEV_ROOT=../..


C_SOURCES += main.c

C_INCLUDES += stm32_hal_test/Inc
#C_SOURCES  += stm32_hal_test/Src/stm32f1xx_hal.c
C_SOURCES  += stm32_hal_test/Src/stm32f1xx_hal_gpio.c
C_SOURCES  += stm32_hal_test/Src/stm32f1xx_hal_rcc.c

ASM_SOURCES += riscv32f103.S
#ASM_SOURCES += startup_ch32v10x.S
ASM_SOURCES += ch32.S
ASM_SOURCES += gd32.S
C_SOURCES += ch32.c
C_SOURCES += gd32.c
ASM_SOURCES += irq.S


# link script
#LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld 
LDSCRIPT=test.ld
#LDSCRIPT=GD32VF103xB.lds

#C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/WWDG/User/system_ch32v10x.c



LDFLAGS += -nostartfiles



MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  

