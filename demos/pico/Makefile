MCU = RP2040
UCDEV_ROOT = ../../
PICO_SDK_DIR = $(UCDEV_ROOT)/ext/pico-sdk
BUILD_MODE = DEBUG

TARGET=test

ASM_SOURCES += $(PICO_SDK_DIR)/src/rp2_common/pico_standard_link/crt0.S
C_SOURCES += $(PICO_SDK_DIR)/src/rp2_common/cmsis/stub/CMSIS/Device/RaspberryPi/RP2040/Source/system_RP2040.c

C_INCLUDES += .

C_INCLUDES += $(PICO_SDK_DIR)/src/rp2_common/cmsis/stub/CMSIS/Device/RaspberryPi/RP2040/Include
C_INCLUDES += $(UCDEV_ROOT)/ext/CMSIS_5/CMSIS/Core/Include

C_INCLUDES += $(PICO_SDK_DIR)//src/common/pico_base/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_adc/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_base/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_claim/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_clocks/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_divider/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_dma/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_exception/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_flash/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_gpio/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_i2c/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_interp/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_irq/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_pio/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_pll/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_pwm/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_resets/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_rtc/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_spi/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_sync/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_timer/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_uart/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_vreg/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_watchdog/include
C_INCLUDES += $(PICO_SDK_DIR)//src/rp2_common/hardware_xosc/include

C_INCLUDES += $(PICO_SDK_DIR)/src/rp2040/hardware_structs/include
C_INCLUDES += $(PICO_SDK_DIR)/src/rp2040/hardware_regs/include
                            

CFLAGS += -D__force_inline=inline


#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_adc/adc.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_claim/claim.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_clocks/clocks.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_dma/dma.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_flash/flash.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_gpio/gpio.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_i2c/i2c.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_interp/interp.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_irq/irq.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_pio/pio.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_pll/pll.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_rtc/rtc.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_spi/spi.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_sync/sync.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_timer/timer.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_uart/uart.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_vreg/vreg.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_watchdog/watchdog.c
#SRC += $(PICO_SDK_DIR)/src/rp2_common/hardware_xosc/xosc.c


include $(UCDEV_ROOT)/build/make/all.mk
