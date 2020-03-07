#TARGET = stm32f103cb


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
#OPT = -Og
OPT = -O0



TARGET ?= STM32F303xC

CFLAGS += -D$(TARGET)

#######################################
# paths
#######################################
# Build path
BUILD_DIR = BUILD_$(TARGET)
OUT_DIR = out

######################################
# source
######################################
# C sources
CUBEF3_ROOT =     ../../../ext/STM32CubeF3

CUBEF3_HAL_SRC_ROOT = $(CUBEF3_ROOT)/Drivers/STM32F3xx_HAL_Driver/Src
CUBEF3_HAL_INC_ROOT = $(CUBEF3_ROOT)/Drivers/STM32F3xx_HAL_Driver/Inc

HALGUE_INC = ../../../lib/libhalglue/hal

CFLAGS += --std=gnu11

INC += -I$(CUBEF3_ROOT)/Drivers/CMSIS/Device/ST/STM32F3xx/Include/
INC += -I$(CUBEF3_ROOT)/Drivers/CMSIS/Include/
INC += -I$(HALGUE_INC)/stm32

C_SOURCES 	+= $(CUBEF3_ROOT)/Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/system_stm32f3xx.c

# Build fails for STM32F348x6 as the .s file as startup_stm32f348xx.s so this automatic name generation won't work for that target
ASM_SOURCES += $(CUBEF3_ROOT)/Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/gcc/startup_$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).s


C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_adc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_adc_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_can.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_cec.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_comp.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_cortex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_crc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_crc_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_dac.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_dac_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_dma.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_exti.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_flash.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_flash_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_gpio.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_hrtim.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_i2c.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_i2c_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_i2s.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_i2s_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_irda.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_iwdg.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_nand.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_nor.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_opamp.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_opamp_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_pccard.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_pcd.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_pcd_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_pwr.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_pwr_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_rcc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_rcc_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_rtc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_rtc_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_sdadc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_smartcard.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_smartcard_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_smbus.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_spi.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_spi_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_sram.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_tim.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_tim_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_tsc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_uart.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_uart_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_usart.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_usart_ex.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_hal_wwdg.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_adc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_comp.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_crc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_dac.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_dma.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_exti.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_fmc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_gpio.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_hrtim.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_i2c.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_opamp.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_pwr.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_rcc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_rtc.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_spi.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_tim.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_usart.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_usb.c
C_SOURCES 	+= $(CUBEF3_HAL_SRC_ROOT)/stm32f3xx_ll_utils.c



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

# STM32F3x is an Cortex-M4F
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
C_DEFS =  -DUSBD_LPM_ENABLED -DUSE_HAL_DRIVER 



# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  $(INC) -I. \
-I$(CUBEF3_HAL_INC_ROOT)


# compile gcc flags
ASFLAGS += $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"



#default action: build all

all: lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a






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
	
$(BUILD_DIR):
	mkdir $@		


%.a: $(OBJECTS) Makefile
	$(AR) rcs $@ $(OBJECTS)




#######################################
# clean up
#######################################
clean:
	rm -fR $(BUILD_DIR)
	rm lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***