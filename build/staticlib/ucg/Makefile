ARCH?=ARM
SUBARCH?=M3

TARGET = ucg
#TARGET =  $(shell echo $(LIBRARY) | tr A-Z a-z)_$(shell echo $(ARCH) | tr A-Z a-z)_$(shell echo $(SUBARCH) | tr A-Z a-z)

UCDEV_ROOT = ../../../

U8G2_DIR 	= $(UCDEV_ROOT)/ext/ucglib/csrc

#  library compile time configuration

CFLAGS += -DU8X8_WITH_USER_POINTER

#  source of the library

C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_bitmap.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_box.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_ccs.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_circle.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_clip.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_com_msg_api.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_default_cb.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_hx8352c.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ili9163.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ili9325.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ili9325_spi.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ili9341.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ili9486.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ld50t6160.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_pcf8833.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_seps225.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ssd1289.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ssd1331.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_ssd1351.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_ic_st7735.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_msg_api.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_oled_128x128_ft.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_oled_128x128_ilsoft.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_oled_128x128_univision.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_oled_160x128_samsung.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_oled_96x64_univision.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_128x128_ili9163.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_128x160_st7735.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_132x132_pcf8833.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_240x320_ili9325_spi.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_240x320_ili9341.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_240x320_itdb02.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_240x320_ssd1289.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_240x400_hx8352c.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_dev_tft_320x480_ili9486.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_font.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_init.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_line.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_pixel.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_pixel_font_data.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_polygon.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_rotate.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_scale.c
C_SOURCES += $(UCDEV_ROOT)/ext/ucglib/csrc/ucg_vector_font_data.c


BUILD_LIBRARY = 1

include $(UCDEV_ROOT)/build/make/arch.mk
include $(UCDEV_ROOT)/build/make/opt.mk
include $(UCDEV_ROOT)/build/make/bld.mk


