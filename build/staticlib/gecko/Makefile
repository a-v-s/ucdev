# EFR32MG1P232F256GM48	# eByte E76-2G4M20S
# EFR32MG1B232F256GM32	# eByte E180-2G120A/B
# EFR32FG1P131F256GM48	# eByte E76-868M20S
# EFR32BG22C224F512GM32	# eByte E104-BT53A3
# EFR32BG22C112F352GM32	# eByte E104-BT53A1

MCU ?= EFR32MG1P232F256GM48
TARGET = $(shell echo $(MCU) |  tr '[:upper:]' '[:lower:]')
UCDEV_ROOT = ../../../
BUILD_SYSTEM_LIBRARY = 1

#######################################
# source of the library
#######################################

C_INCLUDES += $(GECKO_EMLIB_INC)

C_SOURCES += $(SYSTEM)
ASM_SOURCES += $(STARTUPA)

C_SOURCES += $(GECKO_EMLIB_SRC)/em_acmp.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_adc.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_aes.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_burtc.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_can.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_cmu.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_cmu_fpga.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_core.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_cryotimer.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_crypto.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_csen.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_dac.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_dbg.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_dma.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_ebi.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_emu.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_eusart.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_gpcrc.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_gpio.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_i2c.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_iadc.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_idac.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_lcd.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_ldma.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_lesense.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_letimer.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_leuart.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_msc.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_opamp.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_pcnt.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_pdm.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_prs.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_qspi.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_rmu.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_rtc.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_rtcc.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_se.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_system.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_timer.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_usart.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_vcmp.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_vdac.c
C_SOURCES += $(GECKO_EMLIB_SRC)/em_wdog.c



include $(UCDEV_ROOT)/build/make/all.mk
