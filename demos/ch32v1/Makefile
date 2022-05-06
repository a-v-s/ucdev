################################################################################
# Set the MCU
################################################################################
MCU ?= CH32V103

# Use the xPack compiler rather then the arch compiler
# The arch compiler appears to have issues with passing parameters to functions
PREFIX=riscv-none-embed-
################################################################################
# Set Output Filename 
################################################################################
TARGET = ch32v103_demo

################################################################################
# Set the root directory of the ucdev enviorement 
################################################################################
UCDEV_ROOT=../..


C_SOURCES += main.c

#ASM_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Startup/startup_ch32v10x.S
ASM_SOURCES += riscv32f103.S
ASM_SOURCES += startup_ch32v10x.S

C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Core/core_riscv.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Debug/debug.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_adc.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_bkp.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_crc.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_dbgmcu.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_dma.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_exti.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_flash.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_gpio.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_i2c.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_iwdg.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_misc.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_pwr.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_rcc.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_rtc.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_spi.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_tim.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_usart.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_usb.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_usb_host.c
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/src/ch32v10x_wwdg.c

C_INCLUDES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC
C_INCLUDES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Debug
C_INCLUDES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Core
C_INCLUDES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/SRC/Peripheral/inc

C_INCLUDES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/WWDG/User/
C_SOURCES += $(UCDEV_ROOT)//ext/ch32v103/EVT/EXAM/WWDG/User/system_ch32v10x.c

LDFLAGS += -nostartfiles

# link script
LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld 

MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  

