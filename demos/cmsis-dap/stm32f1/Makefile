TARGET = STM32DAP
MCU ?= STM32F103xB
UCDEV_ROOT=../../..

######################################
# source
######################################
# C sources
CMSISDAP_ROOT = ../../../ext/CMSIS_5/CMSIS/DAP/Firmware

## CMSIS-DAP FILES  ############################################################
INC += -I$(CMSISDAP_ROOT)/Include

C_SOURCES += $(CMSISDAP_ROOT)/Source/DAP.c
C_SOURCES += $(CMSISDAP_ROOT)/Source/DAP_vendor.c
C_SOURCES += $(CMSISDAP_ROOT)/Source/JTAG_DP.c
C_SOURCES += $(CMSISDAP_ROOT)/Source/SW_DP.c
C_SOURCES += $(CMSISDAP_ROOT)/Source/SWO.c

################################################################################
C_SOURCES += main.c
C_SOURCES += ../demo.c

C_SOURCES += $(LIBHLUSBD_ROOT)/drivers/usbd_stm.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd_descriptors.c
C_SOURCES += $(LIBHLUSBD_ROOT)/ConvertUTF/ConvertUTF.c

C_INCLUDES += . 
C_INCLUDES += ..
C_INCLUDES += $(LIBHLUSBD_ROOT)
C_INCLUDES += $(CMSISDAP_ROOT)/Include
C_INCLUDES += $(LIBHLUSBD_ROOT)/drivers/
C_INCLUDES += $(LIBHLUSBD_ROOT)/
C_INCLUDES += $(LIBHLUSBD_ROOT)/ConvertUTF

LDSCRIPT = stm32f103xb.ld

MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk

