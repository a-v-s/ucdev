################################################################################
# Set the MCU
################################################################################
MCU = NRF52840

################################################################################
# Set Output Filename 
################################################################################
TARGET = usb_demo

################################################################################
# Set the root directory of the ucdev enviorement 
################################################################################
UCDEV_ROOT=../../..

################################################################################
# Sources
################################################################################
C_SOURCES += main.c
C_SOURCES += ../demo.c
C_SOURCES += $(LIBHALGLUE_ROOT)/common/serialnumber.c
C_SOURCES += $(LIBHLUSBD_ROOT)/drivers/usbd_nrfx.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd_descriptors.c
C_SOURCES += $(LIBHLUSBD_ROOT)/ConvertUTF/ConvertUTF.c

################################################################################
# Includes
################################################################################
C_INCLUDES += .
C_INCLUDES += ...
C_INCLUDES += $(LIBHLUSBD_ROOT)/drivers/
C_INCLUDES += $(LIBHLUSBD_ROOT)/
C_INCLUDES += $(LIBHLUSBD_ROOT)/ConvertUTF
C_INCLUDES += $(LIBHALGLUE_ROOT)/common/
C_INCLUDES += $(LIBHALGLUE_INC) 
C_INCLUDES += $(LIBHALGLUE_INC)/nrfx

C_INCLUDES += $(NRFX_ROOT)/
C_INCLUDES += $(NRFX_ROOT)/mdk
C_INCLUDES += $(NRFX_ROOT)/hal
C_INCLUDES += $(NRFX_ROOT)/soc
C_INCLUDES += $(NRFX_ROOT)/drivers/include
C_INCLUDES += $(NRFX_ROOT)/drivers/src


# link script
#LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld
LDSCRIPT = nrf52840_xxaa.ld

MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  
