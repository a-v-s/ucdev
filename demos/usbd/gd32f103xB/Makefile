################################################################################
# Set the MCU
################################################################################
MCU = GD32F10X_MD

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
C_SOURCES += $(LIBHLUSBD_ROOT)/drivers/usbd_gd.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd_descriptors.c
C_SOURCES += $(LIBHLUSBD_ROOT)/ConvertUTF/ConvertUTF.c

#C_SOURCES += $(LIBHALGLUE_ROOT)/hal/stm32f1/clocksetup.c

################################################################################
# Includes
################################################################################
INC += -I. -I..
INC += -I $(LIBHLUSBD_ROOT)/drivers/
INC += -I $(LIBHLUSBD_ROOT)/
INC += -I $(LIBHLUSBD_ROOT)/ConvertUTF
INC += -I$(LIBHALGLUE_ROOT)/common/
INC += -I$(LIBHALGLUE_INC) #-I$(LIBHALGLUE_INC)/stm32
INC += -I$(LIBHALGLUE_INC)/gd32

# C includes
C_INCLUDES =  $(INC) -I. 

# link script
LDSCRIPT = $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU)).ld

MK_DIR=$(UCDEV_ROOT)/build/make
include $(MK_DIR)/all.mk
  
