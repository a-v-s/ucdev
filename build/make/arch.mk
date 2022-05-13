
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
	SPECS+= --specs=nosys.specs
	# Older toolchains use riscv64-unknown-elf-  	(built from AUR)
	# Newer toolchains use riscv64-elf-				(community repo)
	#PREFIX?=riscv64-unknown-elf-
	#PREFIX?=riscv64-elf-
	PREFIX ?= riscv-none-embed-

	ifeq ($(SUBARCH), RV32IMAC)
		CPU?=	-march=rv32imac 
		FPU?=	
		ABI?=	-mabi=ilp32 -mcmodel=medlow

		# This wouldn't be the correct place to include this but
		# As the GD32VF/CH32V in one is still a work in progress
		# For now, do it here
		C_INCLUDES +=$(NMSIS_INC_CORE)
		
		
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

#$(info ARCH: Configuring Compiler)
#$(info ARCH: Compile type $(COMPILER_TYPE))

ifeq ($(COMPILER_TYPE),GCC)


#$(info ARCH: Configuring GCC)

#	CC  ?= $(PREFIX)gcc
	CC  = $(PREFIX)gcc
	AS  = $(PREFIX)gcc -x assembler-with-cpp
	CP  = $(PREFIX)objcopy
	SZ  = $(PREFIX)size
	HEX = $(CP) -O ihex
	BIN = $(CP) -O binary -S

	# libraries
	LIBDIR = -L$(SLIB_DIR) -L$(LD_DIR)


#$(info ARCH: OPT IN MCU 	   $(OPT))



	ASFLAGS  += $(foreach d, $(AS_INCLUDES), -I$d)
	CFLAGS   += $(foreach d, $(C_INCLUDES), -I$d)
	CXXFLAGS += $(foreach d, $(CXX_INCLUDES), -I$d)

	# Flags for assembler, C compiler and linker
	ASFLAGS  += $(CPU) $(FPU) $(ABI) $(AS_DEFS)  $(OPT) -Wall -fdata-sections -ffunction-sections 
	CFLAGS   += $(CPU) $(FPU) $(ABI) $(C_DEFS)   $(OPT) -Wall -fdata-sections -ffunction-sections  
	CXXFLAGS += $(CPU) $(FPU) $(ABI) $(CXX_DEFS) $(OPT) -Wall -fdata-sections -ffunction-sections 
	LDFLAGS  += $(CPU) $(FPU) $(ABI) $(SPECS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(MCU).map,--cref -Wl,--gc-sections

	# Generate dependency information
	CFLAGS +=  -MMD -MP -MF"$(@:%.o=%.d)"
	ASFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
endif


# TODO: Can we support clang as well?


# For now there is no support for SDCC MCUs. These are untested placeholders.
ifeq ($(COMPILER_TYPE), SDCC)

#$(info ARCH: Configuring SDCC)

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
		CFLAGS += -mstm8 --debug  --out-fmt-elf 
        LDFLAGS += -mstm8 --debug --out-fmt-elf 
	endif

endif


$(info MCU           $(MCU))
$(info Family        $(FAMILY))

$(info Architecture  $(ARCH))
$(info Compile type  $(COMPILER_TYPE))

#$(info ARCH: CC           $(CC))
#
#$(info ARCH: LIBDIR 	   $(LIBDIR))
#$(info ARCH: ASFLAGS  	   $(ASFLAGS))
#$(info ARCH: CFLAGS 	   $(CFLAGS))
#$(info ARCH: LDFLAGS  	   $(LDFLAGS))
#$(info ------------------------------------------------------------------------)
