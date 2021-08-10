#include "system.h"

#include "u8x8_spi.h"
#include "u8g2.h"
#include "bshal_spim.h"

static u8g2_t m_u8g2;



void display_init(void) {
	static bshal_spim_t spi_config_screen;
	spi_config_screen.frequency = 10000000; 
	spi_config_screen.bit_order = 0; //MSB
	spi_config_screen.mode = 0;

	spi_config_screen.hw_nr = 2; // SPI2
	spi_config_screen.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);	
	spi_config_screen.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	spi_config_screen.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	

	spi_config_screen.nss_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_8);
	spi_config_screen.nrs_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_12);
	spi_config_screen.ncd_pin = -1;
	spi_config_screen.irq_pin = -1;

	bshal_spim_init(&spi_config_screen);

	u8g2_Setup_st7920_s_128x64_f(&m_u8g2, U8G2_R0, bshal_u8x8_byte_spi, bshal_u8x8_gpio_and_delay);
	u8g2_SetUserPtr(&m_u8g2, &spi_config_screen);

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
