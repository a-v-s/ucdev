/*
 * dis.c
 *
 *  Created on: 11 nov. 2020
 *      Author: andre
 */


#include "ucg_spi.h"

static ucg_t m_ucg;

#include "bshal_spim.h"
#define SSD1331

int display_init(bshal_spim_t *bsspim) {
	ucg_com_bshal_set_config(bsspim);
#ifdef SSD1331
	ucg_Init(&m_ucg, ucg_dev_ssd1331_18x96x64_univision, ucg_ext_ssd1331_18, ucg_com_bshal);
#endif

	// The bigger screen works so the HAL code should be fine.
	//ucg_Init(&m_ucg, ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, ucg_com_stm32f4);

	ucg_SetFontMode(&m_ucg, UCG_FONT_MODE_TRANSPARENT);
	ucg_ClearScreen(&m_ucg);

}
void print(char* str, int line) {
	//ucg_SetFont(&m_ucg, ucg_font_5x8_tf);
	//ucg_SetFontMode(&m_ucg, UCG_FONT_MODE_TRANSPARENT);

	ucg_SetColor( &m_ucg, 0, 0xff, 0xff, 0xff);
	ucg_SetColor( &m_ucg, 1, 0x00, 0x00, 0x00);

	ucg_SetFont(&m_ucg, ucg_font_5x8_mf);
	ucg_SetFontMode(&m_ucg, UCG_FONT_MODE_SOLID);
	ucg_SetFontPosTop(&m_ucg);
	ucg_DrawString(&m_ucg, 0, line*8, 0, str);
}

void framebuffer_apply(){

}
