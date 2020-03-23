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
INC += -I. -I..
INC += -I $(LIBHLUSBD_ROOT)/drivers/
INC += -I $(LIBHLUSBD_ROOT)/
INC += -I $(LIBHLUSBD_ROOT)/ConvertUTF
INC += -I$(LIBHALGLUE_ROOT)/common/
INC += -I$(LIBHALGLUE_INC) -I$(LIBHALGLUE_INC)/nrfx

INC += -I $(NRFX_ROOT)/
INC += -I $(NRFX_ROOT)/mdk
INC += -I $(NRFX_ROOT)/hal
INC += -I $(NRFX_ROOT)/soc
INC += -I $(NRFX_ROOT)/drivers/include
INC += -I $(NRFX_ROOT)/drivers/src

# C includes
C_INCLUDES =  $(INC) -I. 

# link script
#LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld
LDSCRIPT = nrf52840_xxaa.ld

MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  
