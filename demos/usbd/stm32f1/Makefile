TARGET = STM32USB


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
#OPT = -Og
OPT = -O0


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
CUBEF1_ROOT =     ../../../ext/STM32CubeF1
STATIC_LIB_DIR = ../../../build/staticlib/

LIBHLUSBD_ROOT =  ../../../lib/libhlusbd
LIBHALGLUE_ROOT = ../../../lib/libhalglue

PROTOCOL_ROOT = ../../../lib/protocol

CUBEF1_HAL_SRC_ROOT = $(CUBEF1_ROOT)/Drivers/STM32F1xx_HAL_Driver/Src
CUBEF1_HAL_INC_ROOT = $(CUBEF1_ROOT)/Drivers/STM32F1xx_HAL_Driver/Inc


CFLAGS += -DSTM32F103xB
CFLAGS += -mcpu=cortex-m3

CFLAGS += --std=GNU11

INC += -I$(PROTOCOL_ROOT)
C_SOURCES += $(PROTOCOL_ROOT)/protocol.c


INC += -I$(CUBEF1_ROOT)/Drivers/CMSIS/Device/ST/STM32F1xx/Include/
INC += -I$(CUBEF1_ROOT)/Drivers/CMSIS/Include/

C_SOURCES += $(LIBHALGLUE_ROOT)/hal/cubef1/clocksetup.c
C_SOURCES += $(LIBHALGLUE_ROOT)/common/serialnumber.c
INC += -I$(LIBHALGLUE_ROOT)/common/



C_SOURCES += main.c
C_SOURCES += ../demo.c


C_SOURCES += $(LIBHLUSBD_ROOT)/drivers/usbd_stm.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd.c
C_SOURCES += $(LIBHLUSBD_ROOT)/usbd_descriptors.c
C_SOURCES += $(LIBHLUSBD_ROOT)/ConvertUTF/ConvertUTF.c

INC += -I. -I..


INC += -I $(LIBHLUSBD_ROOT)/drivers/
INC += -I $(LIBHLUSBD_ROOT)/
INC += -I $(LIBHLUSBD_ROOT)/ConvertUTF

# ASM sources
ASM_SOURCES +=  $(CUBEF1_ROOT)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSBD_LPM_ENABLED \
-DUSE_HAL_DRIVER \
-DSTM32F103xB


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  $(INC) -I. \
-I$(CUBEF1_HAL_INC_ROOT)


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F103XB_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys -lstm32f103xb
LIBDIR += -L$(STATIC_LIB_DIR)/stm32f1
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
