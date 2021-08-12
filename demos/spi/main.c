/*

 File: 		main.c
 Author:	André van Schoubroeck
 License:	MIT


 MIT License

 Copyright (c) 2017, 2018, 2019, 2020 André van Schoubroeck <andre@blaatschaap.be>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 */

#include <stdbool.h>
#include <string.h>
#include <stdfix.h>

#include "system.h"

#include "bshal_spim.h"
#include "bshal_delay.h"
#include "bshal_i2cm.h"

#include "ucg.h"

#include "rc52x_transport.h"
#include "rc52x.h"

rc52x_t g_rc52x;

void HardFault_Handler(void) {

}

void SysTick_Handler(void) {

}

void SystemClock_Config(void) {
	ClockSetup_HSE8_SYS72();
}




void screen_init() {
	static bshal_spim_t screen_spi_config;
	screen_spi_config.frequency = 6666666; // SPI speed for SSD1331 = 6.66 MHz (150 ns clock cycle time)
	screen_spi_config.bit_order = 0; //MSB
	screen_spi_config.mode = 0;

	screen_spi_config.hw_nr = 2; // SPI2
	screen_spi_config.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	screen_spi_config.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	screen_spi_config.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);

	screen_spi_config.nss_pin = bshal_gpio_encode_pin(GPIOA,GPIO_PIN_2);
	screen_spi_config.nrs_pin = bshal_gpio_encode_pin(GPIOA,GPIO_PIN_1);
	screen_spi_config.ncd_pin = bshal_gpio_encode_pin(GPIOA,GPIO_PIN_0);
	screen_spi_config.irq_pin = -1;//

	bshal_spim_init(&screen_spi_config);

	bshal_gpio_write_pin(screen_spi_config.nrs_pin, 0);
	bshal_delay_ms(1);
	bshal_gpio_write_pin(screen_spi_config.nrs_pin, 1);

	display_init(&screen_spi_config);

	// Thinking about we would need some SPI manager
}

void rfid5_init(rc52x_t *rc52x){
	static bshal_spim_t rfid_spi_config;
	rfid_spi_config.frequency = 10000000; // SPI speed for MFRC522 = 10 MHz
	rfid_spi_config.bit_order = 0; //MSB
	rfid_spi_config.mode = 0;

	rfid_spi_config.hw_nr = 2; // SPI2
	rfid_spi_config.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	rfid_spi_config.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	rfid_spi_config.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);

	rfid_spi_config.nss_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_5);
	rfid_spi_config.nrs_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_4);
	rfid_spi_config.ncd_pin = -1;
	rfid_spi_config.irq_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_3);

	bshal_spim_init(&rfid_spi_config);
	rc52x->transport = mfrc_transport_spi;
	rc52x->transport_config=&rfid_spi_config;
	rc52x->delay_ms = bshal_delay_ms;
}

int main() {
#ifdef SEMI
	initialise_monitor_handles();
	printf("Hello world!\n");
#endif

	SystemClock_Config();
	SystemCoreClockUpdate();

	bshal_delay_init();
	bshal_delay_us(10);
	screen_init();

	print("Hello World!",3);

	rfid5_init(&g_rc52x);


	char str[32];
	uint8_t version = -1;
	rc52x_get_chip_version(&g_rc52x, &version);
	sprintf(str, "VERSION %02X", version);
	print(str, 4);


	while (1) {

	}
}
