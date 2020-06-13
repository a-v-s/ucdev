TARGET ?= NRF52840

COMPILER_TYPE=GCC
include ../../make/opt.mk


include ../../make/opt.mk

CFLAGS += -D$(TARGET) -D$(TARGET)_XXAA

#######################################
# paths
#######################################
# Build path
BUILD_DIR = BUILD_$(TARGET)_$(BUILD_MODE)

OUT_DIR = $(shell tr '[:upper:]' '[:lower:]' <<< $(BUILD_MODE))


######################################
# source
######################################
# C sources
NRFX_ROOT =     ../../../ext/nrfx
CMSIS_ROOT = 	../../../ext/CMSIS_5/CMSIS/Core/Include
UCDEV_HAL_ROOT = ../../../lib/libhalglue/hal


NRFX_HAL_ROOT = $(NRFX_ROOT)/hal
NRFX_MDK_ROOT = $(NRFX_ROOT)/mdk
NRFX_SOC_ROOT = $(NRFX_ROOT)/soc
NRFX_DRV_ROOT = $(NRFX_ROOT)/drivers
NRFX_DRV_SRC = $(NRFX_DRV_ROOT)/src
NRFX_DRV_INC = $(NRFX_DRV_ROOT)/include


CFLAGS += --std=gnu11

INC += -I$(UCDEV_HAL_ROOT) -I$(NRFX_ROOT) -I$(CMSIS_ROOT) -I$(NRFX_MDK_ROOT) 
INC += -I$(NRFX_HAL_ROOT) -I$(NRFX_DRV_ROOT) -I$(NRFX_DRV_SRC) -I$(NRFX_DRV_INC)  
INC += -I$(NRFX_SOC_ROOT)


ifeq ($(TARGET),NRF52832)
	C_SOURCES   +=  $(NRFX_MDK_ROOT)/system_nrf52.c
	ASM_SOURCES +=  $(NRFX_MDK_ROOT)/gcc_startup_nrf52.S
else
	C_SOURCES   +=  $(NRFX_MDK_ROOT)/system_$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).c
	ASM_SOURCES +=  $(NRFX_MDK_ROOT)/gcc_startup_$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).S
endif



C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_adc.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_clock.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_comp.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_dppi.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_egu.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_gpiote.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_i2s.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_ipc.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_lpcomp.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_nfct.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_nvmc.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_pdm.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_power.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_ppi.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_pwm.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_qdec.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_qspi.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_rng.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_rtc.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_saadc.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_spi.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_spim.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_spis.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_systick.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_temp.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_timer.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_twi.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_twim.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_twis.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_twi_twim.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_uart.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_uarte.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_usbd.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_usbreg.c
C_SOURCES   += $(NRFX_DRV_SRC)/nrfx_wdt.c
C_SOURCES   += $(NRFX_DRV_SRC)/prs/nrfx_prs.c




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
AR = $(GCC_PATH)/$(PREFIX)ar
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
AR = $(PREFIX)ar
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
A = $(AR)
 
#######################################
# CFLAGS
#######################################

# Please note: The CPU/FPU flags cover nRF51 and nRF52
#	For nRF52 and nRF91 series, I still need to figure out the required flags
#	I don't have any hardware in this category so this is not a priority now

# cpu

ifeq ($(TARGET),$(filter $(TARGET),NRF51))
	CPU = -mcpu=cortex-m0	
else
	CPU = -mcpu=cortex-m4	
endif

# fpu
# float-abi

ifeq ($(TARGET),$(filter $(TARGET),NRF52832 NRF52833 NRF52840))
	FLOAT-ABI = -mfloat-abi=hard
	FPU       = -mfpu=fpv4-sp-d16
else
	FLOAT-ABI = -mfloat-abi=soft
endif






# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS =  -D$(TARGET)_XXAA 

# C defines
C_DEFS += -D$(TARGET)_XXAA



# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  $(INC) -I. 



# compile gcc flags
ASFLAGS += $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

all: $(OUT_DIR) $(OUT_DIR)/lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a


#######################################
# build the library
#######################################
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
# Handle both .s (eg STM32Cube) and .S (eg nrfx) asm files 
OBJ_ASM_TMP1 =  $(ASM_SOURCES:.s=.o)
OBJ_ASM_TMP2 =  $(OBJ_ASM_TMP1:.S=.o)

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(OBJ_ASM_TMP2)  ))

vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))


$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
	
$(BUILD_DIR):
	mkdir $@		

$(OUT_DIR):
	mkdir $@		

$(OUT_DIR)/%.a: $(OBJECTS) Makefile
	$(AR) rcs $@ $(OBJECTS)

#######################################
# clean up
#######################################
clean:
	rm -fR $(BUILD_DIR)
	rm $(OUT_DIR)/lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
