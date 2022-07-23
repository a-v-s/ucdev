################################################################################
# Set the MCU
################################################################################
MCU ?= RV32F103

# Use the xPack compiler rather then the arch compiler
# The arch compiler appears to have issues with passing parameters to functions
# Update: problem still exists for gcc 12 in the arch repo
#PREFIX=riscv-none-embed-

# Updating to gcc 12:
# The function parameter problem still exists, however,
# By default we get messages like
#
# int.h: Assembler messages:
# int.h:108: Error: unrecognized opcode `csrr a5,marchid'
#
# This is solved by specifying the ISA spec to version 2.2
# CFLAGS += -misa-spec=2.2


################################################################################
# Set Output Filename 
################################################################################
TARGET = ch32v103_demo
################################################################################
# Set the root directory of the ucdev enviorement 
################################################################################
UCDEV_ROOT=../..

C_SOURCES += main.c

SPECS =  --specs=nano.specs

# link script
LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld 



#C_SOURCES += $(UCDEV_ROOT)/ext/GD32VF103_Firmware_Library/Firmware/RISCV/stubs/sbrk.c
C_SOURCES += $(UCDEV_ROOT)/ext/GD32VF103_Firmware_Library/Firmware/RISCV/stubs/close.c
C_SOURCES += $(UCDEV_ROOT)/ext/GD32VF103_Firmware_Library/Firmware/RISCV/stubs/lseek.c
C_SOURCES += $(UCDEV_ROOT)/ext/GD32VF103_Firmware_Library/Firmware/RISCV/stubs/fstat.c
C_SOURCES += $(UCDEV_ROOT)/ext/GD32VF103_Firmware_Library/Firmware/RISCV/stubs/isatty.c


MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  

