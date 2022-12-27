#include "system.h"

#include "u8x8_i2c.h"
#include "u8g2.h"
#include "bshal_i2cm.h"

static u8g2_t m_u8g2;
extern bshal_i2cm_instance_t *gp_i2c;

void display_init(void) {

//#ifdef U8X8_WITH_USER_PTR
	u8g2_SetUserPtr(&m_u8g2,gp_i2c);
//#else
//	bshal_u8x8_i2c_init(&m_u8g2, gp_i2c);
//#endif

	// Screen with either ssd1306 or sh1106 are shipped by AliBay sellers
	// They are mostly compatible, but the display content will be shifted 2 pixels
	// if the wrong driver is used.

	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&m_u8g2, U8G2_R0, bshal_u8x8_byte_i2c, bshal_u8x8_gpio_and_delay);

	// What is the difference between these? (noname, vcomh0, winstar) ?
	//u8g2_Setup_sh1106_i2c_128x64_noname_f(&m_u8g2, U8G2_R0, bshal_u8x8_byte_i2c, bshal_u8x8_gpio_and_delay);



	u8g2_InitDisplay(&m_u8g2);
	u8g2_SetPowerSave(&m_u8g2, 0);



	char buff[16];

	u8g2_ClearBuffer(&m_u8g2);

}

void print(char* str, int line) {
//	ucg_SetFont(&m_ucg, ucg_font_5x8_tf);
//	ucg_SetFontMode(&m_ucg, UCG_FONT_MODE_TRANSPARENT);
//	ucg_SetFontPosTop(&m_ucg);


	//u8g2_SetFont(&m_u8g2, u8g2_font_t0_15b_tf);
	u8g2_SetFont(&m_u8g2, u8g2_font_5x8_tf);
	//u8g2_SetFont(&m_u8g2, u8g2_font_5x7_tf);
	//u8g2_DrawStr(&m_u8g2, 0, (line+1) * 8, str);
	u8g2_DrawUTF8(&m_u8g2, 0, (line+1) * 8, str);

}

void framebuffer_apply() {
	u8g2_UpdateDisplay(&m_u8g2);
}

void draw_background(){
	u8g2_ClearBuffer(&m_u8g2);
}
void draw_plain_background(){
	u8g2_ClearBuffer(&m_u8g2);
}
void set_565(){}
