LD_DIR 						?= $(UCDEV_ROOT)/build/linker
SLIB_ROOT 					?= $(UCDEV_ROOT)/build/staticlib

LIBHLUSBD_ROOT 				?= $(UCDEV_ROOT)/lib/libhlusbd
LIBHALGLUE_ROOT 			?= $(UCDEV_ROOT)/lib/libhalglue
LIBHALGLUE_INC 				?= $(LIBHALGLUE_ROOT)/hal

CMSIS_ROOT 					?= $(UCDEV_ROOT)/ext/CMSIS_5/
CMSIS_INC_CORE 				?= $(CMSIS_ROOT)/CMSIS/Core/Include/

NMSIS_ROOT 					?= $(UCDEV_ROOT)/ext/NMSIS
NMSIS_INC_CORE 				?= $(NMSIS_ROOT)/NMSIS/Core/Include/

CUBEF0_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f0xx_hal_driver/Src
CUBEF0_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f0xx_hal_driver/Inc
CUBEF0_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_f0
CUBEF0_CMSIS_INC_DEV  =    $(CUBEF0_CMSIS_DEV)/Include/
CUBEF0_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEF1_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f1xx_hal_driver/Src
CUBEF1_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f1xx_hal_driver/Inc
CUBEF1_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_f1
CUBEF1_CMSIS_INC_DEV  =    $(CUBEF1_CMSIS_DEV)/Include/
CUBEF1_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEF2_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f2xx_hal_driver/Src
CUBEF2_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f2xx_hal_driver/Inc
CUBEF2_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_f2
CUBEF2_CMSIS_INC_DEV  =    $(CUBEF2_CMSIS_DEV)/Include/
CUBEF2_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEF3_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f3xx_hal_driver/Src
CUBEF3_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f3xx_hal_driver/Inc
CUBEF3_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_f3
CUBEF3_CMSIS_INC_DEV  =    $(CUBEF3_CMSIS_DEV)/Include/
CUBEF3_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEF4_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f4xx_hal_driver/Src
CUBEF4_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f4xx_hal_driver/Inc
CUBEF4_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_f4
CUBEF4_CMSIS_INC_DEV  =    $(CUBEF4_CMSIS_DEV)/Include/
CUBEF4_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEF7_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f7xx_hal_driver/Src
CUBEF7_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32f7xx_hal_driver/Inc
CUBEF7_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_f7
CUBEF7_CMSIS_INC_DEV  =    $(CUBEF7_CMSIS_DEV)/Include/
CUBEF7_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEL0_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l0xx_hal_driver/Src
CUBEL0_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l0xx_hal_driver/Inc
CUBEL0_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_l0
CUBEL0_CMSIS_INC_DEV  =    $(CUBEL0_CMSIS_DEV)/Include/
CUBEL0_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEL1_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l1xx_hal_driver/Src
CUBEL1_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l1xx_hal_driver/Inc
CUBEL1_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_l1
CUBEL1_CMSIS_INC_DEV  =    $(CUBEL1_CMSIS_DEV)/Include/
CUBEL1_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEL4_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l4xx_hal_driver/Src
CUBEL4_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l4xx_hal_driver/Inc
CUBEL4_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_l4
CUBEL4_CMSIS_INC_DEV  =    $(CUBEL4_CMSIS_DEV)/Include/
CUBEL4_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

CUBEL5_HAL_SRC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l5xx_hal_driver/Src
CUBEL5_HAL_INC_ROOT   =    $(UCDEV_ROOT)/ext/stm32/stm32l5xx_hal_driver/Inc
CUBEL5_CMSIS_DEV      =    $(UCDEV_ROOT)/ext/stm32/cmsis_device_l5
CUBEL5_CMSIS_INC_DEV  =    $(CUBEL5_CMSIS_DEV)/Include/
CUBEL5_CMSIS_INC_CORE =    $(CMSIS_INC_CORE)

NRFX_ROOT ?=               	$(UCDEV_ROOT)/ext/nrfx
NRFX_HAL_ROOT ?= 			$(NRFX_ROOT)/hal
NRFX_MDK_ROOT ?= 			$(NRFX_ROOT)/mdk
NRFX_SOC_ROOT ?= 			$(NRFX_ROOT)/soc
NRFX_DRV_ROOT ?= 			$(NRFX_ROOT)/drivers
NRFX_DRV_SRC ?= 				$(NRFX_DRV_ROOT)/src
NRFX_DRV_INC ?= 				$(NRFX_DRV_ROOT)/include

GD32F1_ROOT ?=               $(UCDEV_ROOT)/ext/GD32F10x_Firmware_Library
GD32F1_FWLIB_ROOT ?=       $(GD32F1_ROOT)/Firmware
GD32F1_STDPH_INC  ?=       $(GD32F1_FWLIB_ROOT)/GD32F10x_standard_peripheral/Include
GD32F1_STDPH_SRC  ?=       $(GD32F1_FWLIB_ROOT)/GD32F10x_standard_peripheral/Source
GD32F1_USBOTG_SRC  ?=       $(GD32F1_FWLIB_ROOT)/GD32F10x_usbfs_driver/Source
GD32F1_USBOTG_INC  ?=       $(GD32F1_FWLIB_ROOT)/GD32F10x_usbfs_driver/Include
GD32F1_USBD_SRC   ?=       $(GD32F1_FWLIB_ROOT)/GD32F10x_usbd_driver/Source
GD32F1_USBD_INC   ?=       $(GD32F1_FWLIB_ROOT)/GD32F10x_usbd_driver/Include
GD32F1_CMSIS_SRC  ?=       $(GD32F1_FWLIB_ROOT)/CMSIS/GD/GD32F10x/Source
GD32F1_CMSIS_INC  ?=       $(GD32F1_FWLIB_ROOT)/CMSIS/GD/GD32F10x/Include

GD32VF1_FWLIB_ROOT ?=        $(UCDEV_ROOT)/ext/GD32VF103_Firmware_Library/Firmware
GD32VF1_STDPH_ROOT ?=        $(GD32VF1_FWLIB_ROOT)/GD32VF103_standard_peripheral
GD32VF1_STDPH_INC  ?=        $(GD32VF1_FWLIB_ROOT)/GD32VF103_standard_peripheral/Include
GD32VF1_STDPH_SRC  ?=        $(GD32VF1_FWLIB_ROOT)/GD32VF103_standard_peripheral/Source
GD32VF1_USBOTG_SRC  ?=        $(GD32VF1_FWLIB_ROOT)/GD32VF103_usbfs_driver/Source
GD32VF1_USBOTG_INC  ?=        $(GD32VF1_FWLIB_ROOT)/GD32VF103_usbfs_driver/Include
GD32VF1_RISCV_DRV  ?=        $(GD32VF1_FWLIB_ROOT)/RISCV/drivers
GD32VF1_RISCV_STUB ?=        $(GD32VF1_FWLIB_ROOT)/RISCV/stubs
GD32VF1_ECLIPSE    ?=        $(GD32VF1_FWLIB_ROOT)/RISCV/env_Eclipse

STM8S_INC           ?=    $(UCDEV_ROOT)/ext/stm8-header

GECKO_ROOT			?=     $(UCDEV_ROOT)/ext/gecko_sdk
GECKO_EMLIB_INC		?=		$(GECKO_ROOT)/platform/emlib/inc
GECKO_EMLIB_SRC		?=		$(GECKO_ROOT)/platform/emlib/src
 
