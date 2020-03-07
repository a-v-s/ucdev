TARGET = STM32F4USB


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
CUBEF4_ROOT =     ../../../ext/STM32CubeF4
LIBHLUSBD_ROOT =  ../../../lib/libhlusbd
LIBHALGLUE_ROOT = ../../../lib/libhalglue
LIBHALGLUE_INC = $(LIBHALGLUE_ROOT)/hal
SLIB_DIR = ../../../build/staticlib/stm32f4
LD_DIR = ../../../build/linker

CUBEF4_HAL_SRC_ROOT = $(CUBEF4_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src
CUBEF4_HAL_INC_ROOT = $(CUBEF4_ROOT)/Drivers/STM32F4xx_HAL_Driver/Inc


C_SOURCES += $(LIBHALGLUE_ROOT)/common/serialnumber.c
INC += -I$(LIBHALGLUE_ROOT)/common/
INC += -I$(LIBHALGLUE_INC) -I$(LIBHALGLUE_INC)/stm32

INC += -I$(CUBEF4_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Include/
INC += -I$(CUBEF4_ROOT)/Drivers/CMSIS/Include/




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
# ASM_SOURCES +=  


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
# STM32F4x is an Cortex-M4F
# cpu
CPU = -mcpu=cortex-m4
# fpu
FPU       = -mfpu=fpv4-sp-d16
# float-abi
FLOAT-ABI = -mfloat-abi=hard


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSBD_LPM_ENABLED \
-DUSE_HAL_DRIVER \
-DSTM32F401xC


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  $(INC) -I. \
-I$(CUBEF4_HAL_INC_ROOT)


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
LDSCRIPT = stm32f401xc.ld

# libraries
LIBS = -lc -lm -lnosys -lstm32f401xc
LIBDIR = -L$(SLIB_DIR) -L$(LD_DIR)
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
