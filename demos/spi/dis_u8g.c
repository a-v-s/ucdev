/*
 * dis_u8g.c
 *
 *  Created on: 4 sep. 2021
 *      Author: andre
 */

#include "bshal_u8x8.h"

#include "u8g2.h"
#include "u8x8.h"

static bshal_u8x8_t m_bshal_st7920, m_bshal_ssd1306;
static u8g2_t m_u8g2_ssd1306, m_u8g2_st7920;

void blokje(u8g2_t * dis) {
	//static int x=0,y=0;
	static int x=6,y=14;
	static int dx=1 ,dy =1;

		u8g2_ClearBuffer(dis);
		u8g2_DrawBox(dis, x,y, 8, 8);

		u8g2_SetFont(dis, u8g2_font_5x8_tf);
		u8g2_DrawUTF8(dis, 8, 8, "1" );
		u8g2_DrawUTF8(dis, 8, 16, "2" );
		u8g2_DrawUTF8(dis, 8, 24, "3" );
		u8g2_DrawUTF8(dis, 8, 32, "4" );
		u8g2_DrawUTF8(dis, 8, 40, "5" );
		u8g2_DrawUTF8(dis, 8, 48, "6" );
		u8g2_DrawUTF8(dis, 8, 56, "7" );
		u8g2_DrawUTF8(dis, 8, 64, "8" );


		u8g2_UpdateDisplay(dis);





		//bshal_delay_ms(10);
		if (x<=0) dx=1;
		if (y<=0) dy=1;
		if (x>= ( dis->width - 8) ) dx = -1;
		if (y>= ( dis->height - 8) ) dy = -1;
		x += (dx);
		y += (dy);
		if (x < 0) x = 0;
		if (y < 0) y = 0;

}

void u8g2_test() {

	// The st7920 display works. The display is marked "12864B".
	// JP2 has been solderbridged to S. This connects PSB so no
	// external connection is required to that pin.
	// Note that contrast required 3.8 Volt on the VO pin.
	// JP3 is solderjumpered to have VR1 as contrast setting
	// Which will only work when VCC is 5 Volt (or rather >3,8V)
	// It appears to work when VCC is 5 Volt, and I/O is at 3.3V.
	// If you wish to run VCC at 3.3V,
	// desolder JP3 and use external pot to supply VO with 3.8V
	// One note: my display is many years old. It looks identical to
	// the displays marked with  "12864B V2.0",
	// but mine got no "V 2.0" on it. So no guarantees the contrast
	// thing applies to those as well.


	// The pcd8544 does not work. Keeps displaying garbage. Not
	// sure why this is the case. The screen in question has not
	// been tested before. It might be broken. You never know
	// with stuff from Ali/Bay.

	// The st7920, for some reason, does not ignore data on the
	// bus when it is not selected. Should add some logic gates
	// to prevent it from having issues

	// Note: The st7920 behavirour is documented in the datasheet
	// when the chip is not selected, clock and data are not allowed to change.
	// adding a 7408

	// Initially there was a bug in the SPI layer causing the clock line to go high
	// while the chip select was low (when re-initialisng)

	// THe problem appears to be, u8g2 re-uses the same buffer for multiple instances
	// Therefore data is bleeding over.
	// It seems to prevent this we must have U8G2_USE_DYNAMIC_ALLOC enabled.
	// I'm not fond of dynamic allocation on microcontrollers, I would rather
	// see a user-provided buffer, but ok
	// It seems I must provide a buffer anyways.... the name is misleading.
	// But I don;t see any place where it would allocate a buffer, and only
	// found a function where I could provide a buffer,,,,
	// And the size, I only know looking at where the static buffer came from.

	// This doesn't appear to solve the entire problem, the buttom 8 pixels are not being drawn
	// on either display, unless I call UpdateDisplay twice. However, the SSD1306 display is
	// no longer mirrored (which would be caused by data intended for the other display I presume)


	m_bshal_st7920.spim.instance.hw_nr = 2; // SPI2
	m_bshal_st7920.spim.instance.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	m_bshal_st7920.spim.instance.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	m_bshal_st7920.spim.instance.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);

	m_bshal_st7920.spim.instance.cs_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_0);
	m_bshal_st7920.spim.ncd_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_1);




	m_bshal_ssd1306 = m_bshal_st7920;
	m_bshal_ssd1306.spim.ncd_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_9);
	m_bshal_ssd1306.spim.instance.cs_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_8);

	u8g2_SetUserPtr(&m_u8g2_st7920, &m_bshal_st7920);
	u8g2_Setup_st7920_s_128x64_f(&m_u8g2_st7920, U8G2_R2, bshal_u8x8_byte_spi, bshal_u8x8_gpio_and_delay);
	static uint8_t st7920_buf[1024];
	m_u8g2_st7920.tile_buf_ptr=st7920_buf;
	u8g2_InitDisplay(&m_u8g2_st7920);
	u8g2_SetPowerSave(&m_u8g2_st7920, 0);

	u8g2_SetUserPtr(&m_u8g2_ssd1306, &m_bshal_ssd1306);
	u8g2_Setup_ssd1306_128x64_noname_f(&m_u8g2_ssd1306, U8G2_R2, bshal_u8x8_byte_spi, bshal_u8x8_gpio_and_delay);
	static uint8_t ssd1306_buf[1024];
	m_u8g2_ssd1306.tile_buf_ptr=ssd1306_buf;
	u8g2_InitDisplay(&m_u8g2_ssd1306);
	u8g2_SetPowerSave(&m_u8g2_ssd1306, 0);






//	u8g2_ClearBuffer(&m_u8g2_st7920);
//	u8g2_SetFont(&m_u8g2_st7920, u8g2_font_5x8_tf);
//	u8g2_DrawUTF8(&m_u8g2_st7920, 8, 8, "Hello World" );
//	u8g2_DrawUTF8(&m_u8g2_st7920, 8, 16, "Hello World" );
// 	u8g2_DrawUTF8(&m_u8g2_st7920, 8, 24, "Hello World" );
//	u8g2_DrawUTF8(&m_u8g2_st7920,  8, 32, "Hello World" );
//	u8g2_DrawUTF8(&m_u8g2_st7920,  8, 40, "Hello World" );
//	u8g2_UpdateDisplay(&m_u8g2_st7920);


//


	while (1) {

		blokje(&m_u8g2_st7920);
		blokje(&m_u8g2_ssd1306);


	}

}
