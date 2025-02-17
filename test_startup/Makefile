TARGET = test

C_SOURCES+=$(UCDEV_ROOT)/lib/startup.c
C_SOURCES+=main.c

LDFLAGS +=  -L$(UCDEV_ROOT)/build/staticlib/rtt/debug/arm_m3  -lrtt
C_SOURCES +=  $(UCDEV_ROOT)/ext/RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.c
C_INCLUDES += $(UCDEV_ROOT)/ext/RTT//Syscalls/
C_INCLUDES += $(UCDEV_ROOT)/ext/RTT//RTT/
C_INCLUDES += $(UCDEV_ROOT)/ext/RTT//Config/

C_INCLUDES += $(UCDEV_ROOT)/ext/CMSIS_6/CMSIS/Core/Include/

C_SOURCES += $(UCDEV_ROOT)/lib/libhalglue/common/nosysfix.c 

LDFLAGS+= -L $(UCDEV_ROOT)/build/linker
LDSCRIPT=ld_cortex-m.ld

ARCH=ARM
SUBARCH=M3

UCDEV_ROOT=..
include $(UCDEV_ROOT)/build/make/all.mk

