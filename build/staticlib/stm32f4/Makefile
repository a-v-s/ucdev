######################################
# building variables
######################################

TARGET ?= STM32F401xC
MCU = $(TARGET)
include ../../make/mcu.mk
include ../../make/opt.mk


CFLAGS += -D$(TARGET)

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
CUBEF4_ROOT =     ../../../ext/STM32CubeF4

CUBEF4_HAL_SRC_ROOT = $(CUBEF4_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src
CUBEF4_HAL_INC_ROOT = $(CUBEF4_ROOT)/Drivers/STM32F4xx_HAL_Driver/Inc

HALGUE_INC = ../../../lib/libhalglue/hal

CFLAGS += --std=gnu11

INC += -I$(CUBEF4_HAL_INC_ROOT)
INC += -I$(CUBEF4_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Include/
INC += -I$(CUBEF4_ROOT)/Drivers/CMSIS/Include/
INC += -I$(HALGUE_INC)/stm32

C_SOURCES 	+= $(CUBEF4_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c

ASM_SOURCES += $(CUBEF4_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).s

C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_adc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_adc_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_can.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_cec.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_cortex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_crc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_cryp.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_cryp_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dac.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dac_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dcmi.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dcmi_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dfsdm.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dma2d.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dma.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dma_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_dsi.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_eth.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_exti.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_flash.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_flash_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_flash_ramfunc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_fmpi2c.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_fmpi2c_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_gpio.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_hash.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_hash_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_hcd.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_i2c.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_i2c_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_i2s.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_i2s_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_irda.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_iwdg.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_lptim.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_ltdc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_ltdc_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_mmc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_nand.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_nor.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_pccard.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_pcd.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_pcd_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_pwr.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_pwr_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_qspi.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_rcc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_rcc_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_rng.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_rtc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_rtc_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_sai.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_sai_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_sd.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_sdram.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_smartcard.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_smbus.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_spdifrx.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_spi.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_sram.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_tim.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_tim_ex.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_uart.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_usart.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_hal_wwdg.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_adc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_crc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_dac.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_dma2d.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_dma.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_exti.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_fmc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_fsmc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_gpio.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_i2c.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_lptim.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_pwr.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_rcc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_rng.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_rtc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_sdmmc.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_spi.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_tim.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_usart.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_usb.c
C_SOURCES 	+= $(CUBEF4_HAL_SRC_ROOT)/stm32f4xx_ll_utils.c



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
C_DEFS =  -DUSBD_LPM_ENABLED -DUSE_HAL_DRIVER 



# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  $(INC) -I. 


# compile gcc flags
ASFLAGS += $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


all: $(C_SOURCES) $(ASM_SOURCES) $(OUT_DIR) $(OUT_DIR)/lib$(shell tr '[:upper:]' '[:lower:]' <<< $(TARGET)).a


#######################################
# build the library
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

$(OUT_DIR):
	mkdir $@		

$(OUT_DIR)/%.a: $(OBJECTS) Makefile
	$(AR) rcs $@ $(OBJECTS)

$(C_SOURCES) $(ASM_SOURCES):
	git submodule init $(CUBEF4_ROOT)
	git submodule update $(CUBEF4_ROOT)

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
