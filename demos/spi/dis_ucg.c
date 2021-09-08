/*
 * dis.c
 *
 *  Created on: 11 nov. 2020
 *      Author: andre
 */


#include "ucg_spi.h"

#include "u8g2.h"

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

//	ucg_SetColor(&m_ucg, 0, 0xFF,0,0);
//	ucg_SetColor(&m_ucg, 1 , 0,0, 0xFF);
//	ucg_SetColor(&m_ucg, 2 , 0, 0xFF, 0 );
//	ucg_SetColor(&m_ucg, 3 , 0, 0, 0 );

	//ucg_DrawGradientBox(&m_ucg, 0, 0, m_ucg.dimension.w, m_ucg.dimension.h);


	{
		// "Set master current attenuation factor"
		// Default value is 0x0F
		// Setting this to a lower value such as 0x04 solves the flicker
		uint8_t cmd[] = { 0x87, 0x02 };

		ucg_com_SetCSLineStatus(&m_ucg, 0);
		ucg_com_SetCDLineStatus(&m_ucg, 0);
		ucg_com_SendString(&m_ucg, sizeof(cmd), cmd);
		ucg_com_SetCSLineStatus(&m_ucg, 1);

	}


}
void print(char* str, int line) {
	ucg_SetColor(&m_ucg, 0, 0xFF,0xFF,0xFF);
	ucg_SetFont(&m_ucg, u8g2_font_5x8_tf);
	ucg_SetFont(&m_ucg, ucg_font_5x8_tf);
	ucg_SetFontMode(&m_ucg, UCG_FONT_MODE_TRANSPARENT);
	//ucg_SetFont(&m_ucg, ucg_font_5x8_mf);

	//ucg_SetFontMode(&m_ucg, UCG_FONT_MODE_SOLID);

	//ucg_SetFont(&m_ucg, ucg_font_profont11_mf);
	ucg_SetFontPosTop(&m_ucg);
	ucg_DrawString(&m_ucg, 0, line*8, 0, str);
}

void framebuffer_apply(){
	//ucg_SetColor(&m_ucg, 0,0,0 ,0x3F);
	//ucg_DrawBox(&m_ucg, m_ucg.dimension.w/4, m_ucg.dimension.h/4, m_ucg.dimension.w/2, m_ucg.dimension.h/2);

	ucg_SetColor(&m_ucg, 0, 0xFF,0,0);
	ucg_SetColor(&m_ucg, 1 , 0,0, 0xFF);
	ucg_SetColor(&m_ucg, 2 , 0, 0xFF, 0 );
	ucg_SetColor(&m_ucg, 3 , 0xFF, 0xFF, 0xFF );

	// SO they should over lap
	ucg_Draw90Line(&m_ucg, 16, 26, 8, 0, 0);
	ucg_Draw90Line(&m_ucg, 16+7, 25, 8, 2, 2);

	// SO they should over lap
	ucg_Draw90Line(&m_ucg, 26, 16, 8, 1, 1);
	ucg_Draw90Line(&m_ucg, 25, 16+7, 8, 3, 3);
}
