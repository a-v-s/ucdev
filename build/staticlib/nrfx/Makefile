MCU ?= NRF52840
TARGET =  $(shell tr '[:upper:]' '[:lower:]' <<< $(MCU))
UCDEV_ROOT = ../../../
BUILD_LIBRARY = 1

#######################################
# source of the library
#######################################


ifeq ($(MCU),NRF52832)
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


include $(UCDEV_ROOT)/build/make/all.mk
