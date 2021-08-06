ARCH?=ARM
SUBARCH?=M3

LIBRARY = u8g2

TARGET =  $(shell echo $(LIBRARY) | tr A-Z a-z)_$(shell echo $(ARCH) | tr A-Z a-z)_$(shell echo $(SUBARCH) | tr A-Z a-z)

UCDEV_ROOT = ../../../

U8G2_DIR 	= $(UCDEV_ROOT)/ext/u8g2/csrc

MCU 		= m_$(ARCH)_$(SUBARCH)
#SERIES 		= s_$(MCU)
LIB_BLD 	= l_$(U8G2_DIR)

OUT_DIR 	= 	$(TARGET)_$(shell echo $(BUILD_MODE) | tr A-Z a-z)
BUILD_DIR 	= 	$(OUT_DIR)/build
OUT 		= 	$(OUT_DIR)/lib$(TARGET).a

include $(UCDEV_ROOT)/build/make/mcu.mk
include $(UCDEV_ROOT)/build/make/opt.mk




#######################################
# source of the library
#######################################

C_SOURCES += $(U8G2_DIR)/u8g2_bitmap.c
C_SOURCES += $(U8G2_DIR)/u8g2_box.c
C_SOURCES += $(U8G2_DIR)/u8g2_buffer.c
C_SOURCES += $(U8G2_DIR)/u8g2_circle.c
C_SOURCES += $(U8G2_DIR)/u8g2_cleardisplay.c
C_SOURCES += $(U8G2_DIR)/u8g2_d_memory.c
C_SOURCES += $(U8G2_DIR)/u8g2_d_setup.c
C_SOURCES += $(U8G2_DIR)/u8g2_font.c
C_SOURCES += $(U8G2_DIR)/u8g2_fonts.c
C_SOURCES += $(U8G2_DIR)/u8g2_hvline.c
C_SOURCES += $(U8G2_DIR)/u8g2_input_value.c
C_SOURCES += $(U8G2_DIR)/u8g2_intersection.c
C_SOURCES += $(U8G2_DIR)/u8g2_kerning.c
C_SOURCES += $(U8G2_DIR)/u8g2_line.c
C_SOURCES += $(U8G2_DIR)/u8g2_ll_hvline.c
C_SOURCES += $(U8G2_DIR)/u8g2_message.c
C_SOURCES += $(U8G2_DIR)/u8g2_polygon.c
C_SOURCES += $(U8G2_DIR)/u8g2_selection_list.c
C_SOURCES += $(U8G2_DIR)/u8g2_setup.c
C_SOURCES += $(U8G2_DIR)/u8log.c
C_SOURCES += $(U8G2_DIR)/u8log_u8g2.c
C_SOURCES += $(U8G2_DIR)/u8log_u8x8.c
C_SOURCES += $(U8G2_DIR)/u8x8_8x8.c
C_SOURCES += $(U8G2_DIR)/u8x8_byte.c
C_SOURCES += $(U8G2_DIR)/u8x8_cad.c
C_SOURCES += $(U8G2_DIR)/u8x8_capture.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_a2printer.c
C_SOURCES += $(U8G2_DIR)/u8x8_debounce.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_hd44102.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_il3820_296x128.c
C_SOURCES += $(U8G2_DIR)/u8x8_display.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ist3020.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ist7920.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ks0108.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_lc7981.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ld7032_60x32.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ls013b7dh03.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_max7219.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_pcd8544_84x48.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_pcf8812.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_pcf8814_hx1230.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_s1d15721.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_s1d15e06.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_sbn1661.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_sed1330.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_sh1106_64x32.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_sh1106_72x40.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_sh1107.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_sh1108.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_sh1122.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1305.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_128x32.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_128x64_noname.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_2040x16.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_48x64.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_64x32.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_64x48.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_72x40.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1306_96x16.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1309.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1316.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1317.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1318.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1320.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1322.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1325.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1326.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1327.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1329.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1606_172x72.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_ssd1607_200x200.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7511.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st75256.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7528.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st75320.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7565.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7567.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7571.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7586s_erc240160.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7586s_s028hn118a.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7586s_ymc240160.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7588.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_st7920.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_stdio.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_t6963.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1601.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1604.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1608.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1610.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1611.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1617.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1638.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1701_dogs102.c
C_SOURCES += $(U8G2_DIR)/u8x8_d_uc1701_mini12864.c
C_SOURCES += $(U8G2_DIR)/u8x8_fonts.c
C_SOURCES += $(U8G2_DIR)/u8x8_gpio.c
C_SOURCES += $(U8G2_DIR)/u8x8_input_value.c
C_SOURCES += $(U8G2_DIR)/u8x8_message.c
C_SOURCES += $(U8G2_DIR)/u8x8_selection_list.c
C_SOURCES += $(U8G2_DIR)/u8x8_setup.c
C_SOURCES += $(U8G2_DIR)/u8x8_string.c
C_SOURCES += $(U8G2_DIR)/u8x8_u16toa.c
C_SOURCES += $(U8G2_DIR)/u8x8_u8toa.c


all: $(ASM_SOURCES) $(C_SOURCES) $(OUT_DIR) $(OUT)


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
	git submodule init $(U8G2_DIR)
	git submodule update $(U8G2_DIR)

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

