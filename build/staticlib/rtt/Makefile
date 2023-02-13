ARCH?=ARM
SUBARCH?=M3
TARGET =  rtt

UCDEV_ROOT = ../../../

RTT_DIR 	= $(UCDEV_ROOT)/ext/RTT


## Library Compile Time Config

CFLAGS += -DSEGGER_RTT_SECTION=\".SEGGER_RTT\"

C_SOURCES  += $(RTT_DIR)/RTT/SEGGER_RTT.c
C_SOURCES  += $(RTT_DIR)/RTT/SEGGER_RTT_printf.c
C_INCLUDES += $(RTT_DIR)/RTT
C_INCLUDES += $(RTT_DIR)/Config


#######################################
# source of the library
#######################################



BUILD_LIBRARY = 1

include $(UCDEV_ROOT)/build/make/arch.mk
include $(UCDEV_ROOT)/build/make/opt.mk
include $(UCDEV_ROOT)/build/make/bld.mk

#include $(UCDEV_ROOT)/build/make/all.mk


