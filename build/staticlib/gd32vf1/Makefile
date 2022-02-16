MCU ?= GD32VF103
TARGET = $(shell echo $(MCU) |  tr '[:upper:]' '[:lower:]')
UCDEV_ROOT = ../../../
BUILD_SYSTEM_LIBRARY = 1

#######################################
# source of the library
#######################################

C_SOURCES += $(GD32VF1_STDPH_ROOT)/system_gd32vf103.c
C_SOURCES += $(GD32VF1_ECLIPSE)/init.c
C_SOURCES += $(GD32VF1_ECLIPSE)/handlers.c
C_SOURCES += $(GD32VF1_RISCV_DRV)/n200_func.c
ASM_SOURCES  += $(GD32VF1_ECLIPSE)/entry.S
ASM_SOURCES  += $(GD32VF1_ECLIPSE)/start.S

C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_adc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_bkp.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_can.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_crc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_dac.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_dbg.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_dma.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_eclic.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_exmc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_exti.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_fmc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_fwdgt.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_gpio.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_i2c.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_pmu.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_rcu.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_rtc.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_spi.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_timer.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_usart.c
C_SOURCES += $(GD32VF1_STDPH_SRC)/gd32vf103_wwdgt.c

LDSCRIPT=test.ld


include $(UCDEV_ROOT)/build/make/all.mk
