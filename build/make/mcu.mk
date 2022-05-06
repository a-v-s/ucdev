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

ifneq (,$(findstring CH32V,$(MCU)))
	FAMILY?=CH32V
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
	
    C_INCLUDES += $(LIBHALGLUE_INC)    
	C_INCLUDES += $(LIBHALGLUE_INC)/nrfx
	
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

	C_INCLUDES +=$(CMSIS_ROOT)/CMSIS/Core/Include

    C_INCLUDES += $(NRFX_ROOT) 
    C_INCLUDES += $(NRFX_ROOT)/mdk 
    C_INCLUDES += $(NRFX_ROOT)/hal 
    C_INCLUDES += $(NRFX_ROOT)/soc
    C_INCLUDES += $(NRFX_ROOT)/drivers
    C_INCLUDES += $(NRFX_ROOT)/drivers/include

endif

ifeq ($(FAMILY), STM32)
	ARCH?=ARM
	CFLAGS += -DUSBD_LPM_ENABLED -DUSE_HAL_DRIVER
    C_INCLUDES += $(LIBHALGLUE_INC)    
	C_INCLUDES += $(LIBHALGLUE_INC)/stm32

	ifneq (,$(findstring F0,$(MCU)))
		SUBARCH?=M0
		SERIES?=STM32F0
		C_INCLUDES +=$(CUBEF0_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEF0_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEF0_CMSIS_INC_CORE)
        #C_INCLUDES +=$(LIBHALGLUE_INC)/stm32f0
	endif	

	ifneq (,$(findstring F1,$(MCU)))
		SUBARCH?=M3
		SERIES?=STM32F1
		C_INCLUDES +=$(CUBEF1_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEF1_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEF1_CMSIS_INC_CORE)
        #C_INCLUDES +=$(LIBHALGLUE_INC)/stm32f1
	endif

	ifneq (,$(findstring F2,$(MCU)))
		SUBARCH?=M3
		SERIES?=STM32F2
		C_INCLUDES +=$(CUBEF2_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEF2_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEF2_CMSIS_INC_CORE)
		#C_INCLUDES +=$(LIBHALGLUE_INC)/stm32f2
	endif

	ifneq (,$(findstring F3,$(MCU)))
		SUBARCH?=M4F
		SERIES?=STM32F3
		C_INCLUDES +=$(CUBEF3_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEF3_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEF3_CMSIS_INC_CORE)
		C_INCLUDES +=$(LIBHALGLUE_INC)/stm32f3
	endif


	ifneq (,$(findstring F4,$(MCU)))
		SUBARCH?=M4F
		SERIES?=STM32F4
		C_INCLUDES +=$(CUBEF4_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEF4_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEF4_CMSIS_INC_CORE)
		#C_INCLUDES +=$(LIBHALGLUE_INC)/stm32f4
	endif


	ifneq (,$(findstring L0,$(MCU)))
		SUBARCH?=M0P
		SERIES?=STM32L0
		C_INCLUDES +=$(CUBEL0_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEL0_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEL0_CMSIS_INC_CORE)
	endif

	ifneq (,$(findstring L1,$(MCU)))
		SUBARCH?=M3
		SERIES?=STM32L1
		C_INCLUDES +=$(CUBEL1_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEL1_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEL1_CMSIS_INC_CORE)
	endif


	ifneq (,$(findstring L4,$(MCU)))
		SUBARCH?=M4F
		SERIES?=STM32L4
		C_INCLUDES +=$(CUBEL4_HAL_INC_ROOT)
		C_INCLUDES +=$(CUBEL4_CMSIS_INC_DEV)
		C_INCLUDES +=$(CUBEL4_CMSIS_INC_CORE)
		#C_INCLUDES +=$(LIBHALGLUE_INC)/stm32f4
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
		#C_INCLUDES +=$(GD32F1_USBOTG_INC)
		C_INCLUDES +=$(GD32F1_USBD_INC)
		C_INCLUDES +=$(GD32F1_CMSIS_INC)
		C_INCLUDES +=$(GD32F1_STDPH_INC)
		C_INCLUDES +=$(GD32F1_CMSIS_INC)
		C_INCLUDES +=$(CMSIS_INC_CORE)
		C_INCLUDES +=$(LIBHALGLUE_INC)/gd32
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
		C_INCLUDES +=$(GD32VF1_STDPH_ROOT)
		C_INCLUDES +=$(GD32VF1_USBOTG_INC)
		C_INCLUDES +=$(GD32VF1_RISCV_DRV)
		C_INCLUDES +=$(GD32VF1_STDPH_INC)
		C_INCLUDES +=$(GD32VF1_RISCV_DRV)
		C_INCLUDES +=$(LIBHALGLUE_INC)/gd32
		C_DEFS     += -DHXTAL_VALUE=8000000UL
		C_DEFS     += -DUSE_STDPERIPH_DRIVER
		C_DEFS     += -DGD32USBOTG
		SLIB_BLD?=$(SLIB_ROOT)/$(shell echo $(SERIES) | tr A-Z a-z)
		SLIB_DIR?=$(SLIB_BLD)/$(shell echo $(BUILD_MODE) | tr A-Z a-z)

		LIBS += -l$(shell echo $(MCU) | tr A-Z a-z)
		SLIB=$(SLIB_DIR)/lib$(shell echo $(MCU) | tr A-Z a-z).a
	endif
endif

ifeq ($(FAMILY), CH32V)
	ARCH?=RISCV
	SUBARCH?=RV32IMAC
	SERIES?=CH32V # TODO
	SLIB_BLD?=.   # TODO
endif 


ifeq ($(FAMILY), FE3)
	ARCH?=RISCV
	SUBARCH?=RV32IMAC
endif

ifeq ($(FAMILY), STM8)
	ARCH?=STM8

	C_INCLUDES +=$(STM8S_INC)
endif

ifeq ($(FAMILY), AVR)
	ARCH?=AVR
endif

C_DEFS += -D$(MCU) -D$(SERIES) -I$(SLIB_BLD)






#$(info MCU: C_INCLUDES 	   $(C_INCLUDES))












