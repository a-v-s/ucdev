################################################################################
# MCUs: Determine family of MCU
################################################################################

ifneq (,$(findstring STM32,$(MCU)))
	FAMILY?=STM32
endif

ifneq (,$(findstring STM8,$(MCU)))
	FAMILY?=STM8
endif

ifneq (,$(findstring NRF5,$(MCU)))
	FAMILY?=NRF5
endif

ifneq (,$(findstring GD32,$(MCU)))
	ifneq (,$(findstring GD32V,$(MCU)))
		FAMILY?=GD32V
	else 
		FAMILY?=GD32
	endif
endif

ifneq (,$(findstring FE310,$(MCU)))
	# SiFive HiFive 1 -- we should import their SDK some time
	FAMILY?=FE3
endif


################################################################################
# MCU Families: Determine the architecture of the family
################################################################################
ifeq ($(FAMILY), NRF5)
	ARCH?=ARM
	
	
	ifneq (,$(findstring 51,$(MCU)))
		SUBARCH?=M0
		SERIES=NRF51_SERIES
        C_DEFS += -D$(MCU)_XXAA
	endif	

	ifneq (,$(findstring 5281,$(MCU)))
		SUBARCH?=M4
		SERIES=NRF52_SERIES
        C_DEFS += -D$(MCU)_XXAA
	endif

	ifneq (,$(findstring 5283,$(MCU)))
		SUBARCH?=M4F
		SERIES=NRF52_SERIES
        C_DEFS += -D$(MCU)_XXAA
	endif

	ifneq (,$(findstring 5284,$(MCU)))
		SUBARCH?=M4F
		SERIES=NRF52_SERIES
        C_DEFS += -D$(MCU)_XXAA
	endif

	ifneq (,$(findstring 53,$(MCU)))
        ifneq (,$(findstring APP,$(MCU)))
		    SUBARCH?=M33F
		    SERIES=NRF53_SERIES
            C_DEFS += -DNRF5340_XXAA_APPLICATION
        endif
        ifneq (,$(findstring NET,$(MCU)))
		    SUBARCH?=M33
		    SERIES=NRF53_SERIES
            C_DEFS += -DNRF5340_XXAA_NETWORK
        endif
	endif

	SLIB_BLD?=$(SLIB_ROOT)/nrfx
	SLIB_DIR?=$(SLIB_BLD)/$(shell echo $(BUILD_MODE) | tr A-Z a-z)
	LIBS += -l$(shell echo $(MCU) | tr A-Z a-z)
	SLIB=$(SLIB_DIR)/lib$(shell echo $(MCU) | tr A-Z a-z).a

	LIBS += -lc -lm -lnosys -L$(NRFX_ROOT)/mdk/

	C_INCLUDES += -I$(CMSIS_ROOT)/CMSIS/Core/Include

    C_INCLUDES += -I$(NRFX_ROOT) -I$(NRFX_ROOT)/mdk 
    C_INCLUDES += -I$(NRFX_ROOT)/hal -I$(NRFX_ROOT)/soc
    C_INCLUDES += -I$(NRFX_ROOT)/drivers -I$(NRFX_ROOT)/drivers/include

endif

ifeq ($(FAMILY), STM32)
	ARCH?=ARM
	CFLAGS += -DUSBD_LPM_ENABLED -DUSE_HAL_DRIVER
    C_INCLUDES += -I$(LIBHALGLUE_INC)/stm32

	ifneq (,$(findstring F0,$(MCU)))
		SUBARCH?=M0
		SERIES?=STM32F0
		C_INCLUDES += -I$(CUBEF0_HAL_INC_ROOT)
		C_INCLUDES += -I$(CUBEF0_CMSIS_INC_DEV)
		C_INCLUDES += -I$(CUBEF0_CMSIS_INC_CORE)
        #C_INCLUDES += -I$(LIBHALGLUE_INC)/stm32f0
	endif	

	ifneq (,$(findstring F1,$(MCU)))
		SUBARCH?=M3
		SERIES?=STM32F1
		C_INCLUDES += -I$(CUBEF1_HAL_INC_ROOT)
		C_INCLUDES += -I$(CUBEF1_CMSIS_INC_DEV)
		C_INCLUDES += -I$(CUBEF1_CMSIS_INC_CORE)
        #C_INCLUDES += -I$(LIBHALGLUE_INC)/stm32f1
	endif

	ifneq (,$(findstring F2,$(MCU)))
		SUBARCH?=M3
		SERIES?=STM32F2
		C_INCLUDES += -I$(CUBEF2_HAL_INC_ROOT)
		C_INCLUDES += -I$(CUBEF2_CMSIS_INC_DEV)
		C_INCLUDES += -I$(CUBEF2_CMSIS_INC_CORE)
		#C_INCLUDES += -I$(LIBHALGLUE_INC)/stm32f2
	endif

	ifneq (,$(findstring F3,$(MCU)))
		SUBARCH?=M4F
		SERIES?=STM32F3
		C_INCLUDES += -I$(CUBEF3_HAL_INC_ROOT)
		C_INCLUDES += -I$(CUBEF3_CMSIS_INC_DEV)
		C_INCLUDES += -I$(CUBEF3_CMSIS_INC_CORE)
		C_INCLUDES += -I$(LIBHALGLUE_INC)/stm32f3
	endif


	ifneq (,$(findstring F4,$(MCU)))
		SUBARCH?=M4F
		SERIES?=STM32F4
		C_INCLUDES += -I$(CUBEF4_HAL_INC_ROOT)
		C_INCLUDES += -I$(CUBEF4_CMSIS_INC_DEV)
		C_INCLUDES += -I$(CUBEF4_CMSIS_INC_CORE)
		#C_INCLUDES += -I$(LIBHALGLUE_INC)/stm32f4
	endif

	ifneq (,$(findstring L4,$(MCU)))
		SUBARCH?=M4F
		SERIES?=STM32L4
		C_INCLUDES += -I$(CUBEL4_HAL_INC_ROOT)
		C_INCLUDES += -I$(CUBEL4_CMSIS_INC_DEV)
		C_INCLUDES += -I$(CUBEL4_CMSIS_INC_CORE)
		#C_INCLUDES += -I$(LIBHALGLUE_INC)/stm32f4
	endif


		SLIB_BLD?=$(SLIB_ROOT)/$(shell echo $(SERIES) | tr A-Z a-z)
		SLIB_DIR?=$(SLIB_BLD)/$(shell echo $(BUILD_MODE) | tr A-Z a-z)

		LIBS += -l$(shell echo $(MCU) | tr A-Z a-z)
		SLIB=$(SLIB_DIR)/lib$(shell echo $(MCU) | tr A-Z a-z).a
endif


ifeq ($(FAMILY), GD32)
	ARCH?=ARM

	ifneq (,$(findstring F1,$(MCU)))
		SUBARCH?=M3
		SERIES?=GD32F1
		# Hmmm... determine whether we need USBD or USBOTG???
		#C_INCLUDES += -I$(GD32F1_USBOTG_INC)
		C_INCLUDES += -I$(GD32F1_USBD_INC)
		C_INCLUDES += -I$(GD32F1_CMSIS_INC)
		C_INCLUDES += -I$(GD32F1_STDPH_INC)
		C_INCLUDES += -I$(LIBHALGLUE_INC)/gd32
		C_DEFS     += -DUSE_STDPERIPH_DRIVER
		C_DEFS     += -DGD32USBFS

		SLIB_BLD?=$(SLIB_ROOT)/$(shell echo $(SERIES) | tr A-Z a-z)
		SLIB_DIR?=$(SLIB_BLD)/$(shell echo $(BUILD_MODE) | tr A-Z a-z)

		LIBS += -l$(shell echo $(MCU) | tr A-Z a-z)
		SLIB=$(SLIB_DIR)/lib$(shell echo $(MCU) | tr A-Z a-z).a
	endif
endif

ifeq ($(FAMILY), GD32V)
	ARCH?=RISCV
	ifneq (,$(findstring F1,$(MCU)))
		SUBARCH?=RV32IMAC
		SERIES?=GD32VF1
		C_INCLUDES += -I$(GD32VF1_STDPH_ROOT)
		C_INCLUDES += -I$(GD32VF1_USBOTG_INC)
		C_INCLUDES += -I$(GD32VF1_RISCV_DRV)
		C_INCLUDES += -I$(GD32VF1_STDPH_INC)
		C_INCLUDES += -I$(LIBHALGLUE_INC)/gd32
		C_DEFS     += -DHXTAL_VALUE=8000000UL
		C_DEFS     += -DUSE_STDPERIPH_DRIVER
		C_DEFS     += -DGD32USBOTG
		SLIB_BLD?=$(SLIB_ROOT)/$(shell echo $(SERIES) | tr A-Z a-z)
		SLIB_DIR?=$(SLIB_BLD)/$(shell echo $(BUILD_MODE) | tr A-Z a-z)

		LIBS += -l$(shell echo $(MCU) | tr A-Z a-z)
		SLIB=$(SLIB_DIR)/lib$(shell echo $(MCU) | tr A-Z a-z).a
	endif
endif

ifeq ($(FAMILY), FE3)
	ARCH?=RISCV
	SUBARCH?=RV32IMAC
endif

ifeq ($(FAMILY), STM8)
	ARCH?=STM8

	C_INCLUDES += -I$(STM8S_INC)
endif

ifeq ($(FAMILY), AVR)
	ARCH?=AVR
endif

################################################################################
# Architectures:	Set the compiler and flags for the architecture
################################################################################
ifeq ($(ARCH), ARM)
	COMPILER_TYPE?=GCC
	PREFIX?=arm-none-eabi-
	SPECS ?=  -specs=nano.specs

	ifeq ($(SUBARCH), M0)
			CPU?=	-mcpu=cortex-m0
			FPU?=
			ABI?=	-mfloat-abi=soft
	endif

	ifeq ($(SUBARCH), M0P)
			CPU?=	-mcpu=cortex-m0plus
			FPU?=
			ABI?=	-mfloat-abi=soft
	endif

	ifeq ($(SUBARCH), M3)
			CPU?=	-mcpu=cortex-m3
			FPU?=
			ABI?=	-mfloat-abi=soft
	endif

	ifeq ($(SUBARCH), M4)
			CPU?=	-mcpu=cortex-m4
			FPU?=
			ABI?=	-mfloat-abi=soft
	endif

	ifeq ($(SUBARCH), M7)
			CPU?=	-mcpu=cortex-m7
			FPU?=
			ABI?=	-mfloat-abi=soft
	endif

	ifeq ($(SUBARCH), M7F)
			CPU?=	-mcpu=cortex-m7
			FPU?=	-mfpu=fpv5-sp-d16
			ABI?=	-mfloat-abi=hard
	endif

	ifeq ($(SUBARCH), M4F)
			CPU?=	-mcpu=cortex-m4
			FPU?=	-mfpu=fpv4-sp-d16
			ABI?=	-mfloat-abi=hard 
	endif

	ifeq ($(SUBARCH), M23)
			CPU?=	-mcpu=cortex-m23
			FPU?=	
			ABI?=	-mfloat-abi=soft
	endif

	ifeq ($(SUBARCH), M33)
			CPU?=	-mcpu=cortex-m33+nodsp+nofp
			FPU?=	
			ABI?=	-mfloat-abi=soft
	endif

	ifeq ($(SUBARCH), M33F)
			CPU?=	-mcpu=cortex-m33
			FPU?=	-mfpu=fpv5-sp-d16
			ABI?=	-mfloat-abi=hard
	endif
endif

# For now the focus is on ARM Cortex-M MCUs and gcc. These are placeholders
# for the future to extend support to other architectures.

ifeq ($(ARCH), RISCV)
	COMPILER_TYPE?=GCC
	
	# Older toolchains use riscv64-unknown-elf-  	(built from AUR)
	# Newer toolchains use riscv64-elf-				(community repo)
	#PREFIX?=riscv64-unknown-elf-
	PREFIX?=riscv64-elf-

	ifeq ($(SUBARCH), RV32IMAC)
		CPU?=	-march=rv32imac
		FPU?=	
		ABI?=	-mabi=ilp32
	endif

endif

ifeq ($(ARCH), MCS51)
	COMPILER_TYPE?=SDCC
endif

ifeq ($(ARCH), STM8)
	COMPILER_TYPE?=SDCC
endif

ifeq ($(ARCH), AVR)
	COMPILER_TYPE?=GCC
	PREFIX?=avr-
endif




################################################################################
# Compiler types: Configure the executables for the compiler
################################################################################

$(info DEBUG: Configuring Compiler)
$(info DEBUG: Compile type $(COMPILER_TYPE))

ifeq ($(COMPILER_TYPE),GCC)


$(info DEBUG: Configuring GCC)

	CC  = $(PREFIX)gcc
	AS  = $(PREFIX)gcc -x assembler-with-cpp
	CP  = $(PREFIX)objcopy
	SZ  = $(PREFIX)size
	HEX = $(CP) -O ihex
	BIN = $(CP) -O binary -S

	# libraries
	LIBDIR = -L$(SLIB_DIR) -L$(LD_DIR)

	C_DEFS += -D$(MCU) -D$(SERIES) -I$(SLIB_BLD)

$(info DEBUG: OPT IN MCU 	   $(OPT))

	# Flags for assembler, C compiler and linker
	ASFLAGS  += $(CPU) $(FPU) $(ABI) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections 
	CFLAGS   += $(CPU) $(FPU) $(ABI) $(C_DEFS)  $(C_INCLUDES)  $(OPT) -Wall -fdata-sections -ffunction-sections 
	CXXFLAGS   += $(CPU) $(FPU) $(ABI) $(CXX_DEFS)  $(CXX_INCLUDES)  $(OPT) -Wall -fdata-sections -ffunction-sections 
	LDFLAGS  += $(CPU) $(FPU) $(ABI) $(SPECS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(MCU).map,--cref -Wl,--gc-sections

	# Generate dependency information
	CFLAGS +=  -MMD -MP -MF"$(@:%.o=%.d)"
	ASFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
endif


# TODO: Can we support clang as well?


# For now there is no support for SDCC MCUs. These are untested placeholders.
ifeq ($(COMPILER_TYPE), SDCC)

$(info DEBUG: Configuring SDCC)

	AR=sdar
	CC=sdcc
	LD=sdlc
    SZ=size
    CP=sdobjcopy
    BIN=$(CP) -O binary -S

	ifeq ($(ARCH), MCS51)
		AS=sdas8051
	endif

	ifeq ($(ARCH), STM8)
		AS=asstm8
		CFLAGS += -mstm8 --debug $(C_INCLUDES)  --out-fmt-elf 
        LDFLAGS += -mstm8 --debug --out-fmt-elf 
	endif

endif


$(info DEBUG: MCU          $(MCU))
$(info DEBUG: Family       $(FAMILY))

$(info DEBUG: Architecture $(ARCH))
$(info DEBUG: Compile type $(COMPILER_TYPE))

$(info DEBUG: CC           $(CC))

$(info DEBUG: LIBDIR 	   $(LIBDIR))
$(info DEBUG: ASFLAGS  	   $(ASFLAGS))
$(info DEBUG: CFLAGS 	   $(CFLAGS))
$(info DEBUG: LDFLAGS  	   $(LDFLAGS))
$(info ------------------------------------------------------------------------)

#ifeq (,$(COMPILER_TYPE) )
#	$(error Compiler type not set)
#endif

















