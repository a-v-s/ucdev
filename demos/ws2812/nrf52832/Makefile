TARGET = NRFXWS2812


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
NRFX_ROOT =     ../../../ext/nrfx
LIBWS2812DMA_ROOT =  ../../../lib/libws2812dma
CMSIS_ROOT = ../../../ext/CMSIS_5/CMSIS/Core/

CFLAGS += --std=GNU11


C_SOURCES += $(NRFX_ROOT)/mdk/system_nrf52.c 
C_SOURCES += $(NRFX_ROOT)/drivers/src/nrfx_power.c 
C_SOURCES += $(NRFX_ROOT)/drivers/src/nrfx_clock.c 
C_SOURCES += $(NRFX_ROOT)/drivers/src/nrfx_systick.c
C_SOURCES += $(NRFX_ROOT)/drivers/src/nrfx_pwm.c





C_SOURCES += main.c
C_SOURCES += ../demo.c


C_SOURCES += $(LIBWS2812DMA_ROOT)/ws2812.c
C_SOURCES += $(LIBWS2812DMA_ROOT)/drivers/ws2812_nrfx.c


INC += -I. -I..

INC += -I $(CMSIS_ROOT)/Include

INC += -I $(NRFX_ROOT)/
INC += -I $(NRFX_ROOT)/mdk
INC += -I $(NRFX_ROOT)/hal
INC += -I $(NRFX_ROOT)/soc
INC += -I $(NRFX_ROOT)/drivers/include
INC += -I $(NRFX_ROOT)/drivers/src


INC += -I $(LIBWS2812DMA_ROOT)/drivers/
INC += -I $(LIBWS2812DMA_ROOT)/


# ASM sources
ASM_SOURCES += $(NRFX_ROOT)/mdk/gcc_startup_nrf52.S 


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
CPU = -mcpu=cortex-m4

# fpu
# NONE for Cortex-M0/M0+/M3

# For Cortex M4, there is M4 without FPU, (eg nRF52810) so these have none
# For Cortex M4F, set to fpv4-sp-d16

FPU = -mfpu=fpv4-sp-d16

# float-abi

# There is an different ABI for MCUs with and without FPU support, so libraries
# compiled with abi=hard and abi=soft cannot link together. There is a middle
# way softfp. softfp is the soft abi but allows fpu instructions within 
# functions. When using the FPU, the hard abi offers best performance.

FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  -DNRF52832_XXAA


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
LDSCRIPT = $(NRFX_ROOT)/mdk/nrf52832_xxaa.ld



# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = -L$(NRFX_ROOT)/mdk
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
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
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
