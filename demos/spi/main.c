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

#include "sdmmc.h"

rc52x_t g_rc52x;

void HardFault_Handler(void) {

}

void SysTick_Handler(void) {

}

void SystemClock_Config(void) {
	ClockSetup_HSE8_SYS72();
}

uint8_t test_adxl_spi_read_id() {

	static bshal_spim_t adxl_spi_config;
	adxl_spi_config.frequency = 1000000;
	adxl_spi_config.bit_order = 0; //MSB
	adxl_spi_config.mode = 0;

	adxl_spi_config.hw_nr = 2; // SPI2
	adxl_spi_config.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	adxl_spi_config.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	adxl_spi_config.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);

	adxl_spi_config.nss_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_10);
	adxl_spi_config.nrs_pin = -1;
	adxl_spi_config.ncd_pin = -1;
	adxl_spi_config.irq_pin = -1;

	bshal_spim_init(&adxl_spi_config);

	uint8_t result = -1;

	// device id is register 0 // Read us 0x80
	uint8_t get_id = 0x00 | 0x80;
	bshal_spim_transmit(&adxl_spi_config, &get_id, 1, true);

	// expected o345 // 0xe5
	bshal_spim_receive(&adxl_spi_config, &get_id, 1, false);

	//return result;
	return get_id;
}

uint32_t test_sdmmc_spi_read_id() {
	static bshal_spim_t flash_sdmmc_config;
	flash_sdmmc_config.frequency = 1000000;
	flash_sdmmc_config.bit_order = 0; //MSB
	flash_sdmmc_config.mode = 0;

	flash_sdmmc_config.hw_nr = 2; // SPI2
	flash_sdmmc_config.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	flash_sdmmc_config.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	flash_sdmmc_config.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);

	flash_sdmmc_config.nss_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_8);
	flash_sdmmc_config.nrs_pin = -1;
	flash_sdmmc_config.ncd_pin = -1;
	flash_sdmmc_config.irq_pin = -1;

	bshal_spim_init(&flash_sdmmc_config);

	// We should toggle the clock without being selected
	// But as other devices have been read at this point
	// That would be the case by now
	// So for now skip such

	ssdmmc_resq_t init = SDMMC_REQ_CMD_INIT_SD;

	bshal_spim_transmit(&flash_sdmmc_config, &init, sizeof(init), true);
	bshal_spim_receive(&flash_sdmmc_config, &init, sizeof(init), false);
	// This returns us all zeros. We are expecting some bits to be set.

	uint8_t result = -1;

	uint32_t device_id = 0;
}

uint32_t test_flash_spi_read_id() {

	static bshal_spim_t flash_spi_config;
	flash_spi_config.frequency = 1000000;
	flash_spi_config.bit_order = 0; //MSB
	flash_spi_config.mode = 0;

	flash_spi_config.hw_nr = 2; // SPI2
	flash_spi_config.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	flash_spi_config.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	flash_spi_config.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);

	flash_spi_config.nss_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_12);
	flash_spi_config.nrs_pin = -1;
	flash_spi_config.ncd_pin = -1;
	flash_spi_config.irq_pin = -1;

	bshal_spim_init(&flash_spi_config);

	uint8_t result = -1;

	uint32_t device_id = 0;

	// So we are getting values from the flash chip, but not the expected values
	// The values we are getting are consistent, also, they are coming from the
	// flash chip, as when we move the chip select to a different pin we get 0.
	// So, this means, the data comes from the chip... but something else is off...
	// The same results by another flash chip so it wasn't a bad chip.

	{
		uint8_t get_id = 0x9F;
		bshal_spim_transmit(&flash_spi_config, &get_id, 1, true);
		bshal_spim_receive(&flash_spi_config, &device_id, 2, false);
		//W25Q32JV: 0xEE  expect 4016
		//GD25Q32C: 0xC0  expect 4016
	}
	{
		uint8_t get_id[4] = { 0xAB, 0x00, 0x00, 0x00 };
		bshal_spim_transmit(&flash_spi_config, get_id, 4, true);
		bshal_spim_receive(&flash_spi_config, &device_id, 1, false);
		//W25Q32JV: got 0x00  expect 15
		//GD25Q32C: got 0x15  expect 0x15 : OK
	}
	{
		uint8_t get_id[4] = { 0x90, 0x00, 0x00, 0x00 };
		bshal_spim_transmit(&flash_spi_config, get_id, 4, true);
		bshal_spim_receive(&flash_spi_config, &device_id, 2, false);
		//W25Q32JV: got 0x0eee // expect ef
		//GD25Q32C: got 0xcc0 // expect 15 c8
	}

	// Expected values for W25Q32JV :

	// ID7 - ID0 = 15h			// answer to ABh, 90h, 92h, 94h
	// answer to 90		//							MF7 - MF0 = EFh
	// answer to 9F 	//	ID15 - ID0 = 4016h


	// Values for GD25Q32C (page 15)
	// ANSWER to 90		//					ID7-ID0:	15	MID = 0xc8
	// ANSWER to 9F		//	ID15-ID8: 40	ID7-ID0: 	16
	// ANSWER TO AB		//					ID7-ID0:	15


	return device_id;
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

	screen_spi_config.ncd_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_9);
	screen_spi_config.nrs_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_8);
	screen_spi_config.nss_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_7);

	screen_spi_config.irq_pin = -1; //

	bshal_spim_init(&screen_spi_config);

	bshal_gpio_write_pin(screen_spi_config.nrs_pin, 0);
	bshal_delay_ms(1);
	bshal_gpio_write_pin(screen_spi_config.nrs_pin, 1);

	display_init(&screen_spi_config);

	// Thinking about we would need some SPI manager
}

void rfid5_init(rc52x_t *rc52x) {
	static bshal_spim_t rfid_spi_config;
	rfid_spi_config.frequency = 10000000; // SPI speed for MFRC522 = 10 MHz
	rfid_spi_config.bit_order = 0; //MSB
	rfid_spi_config.mode = 0;

	rfid_spi_config.hw_nr = 2; // SPI2
	rfid_spi_config.miso_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_14);
	rfid_spi_config.mosi_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_15);
	rfid_spi_config.sck_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_13);

	rfid_spi_config.nss_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_6);
	rfid_spi_config.nrs_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_5);
	rfid_spi_config.irq_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_3);

	rfid_spi_config.ncd_pin = -1;

	bshal_spim_init(&rfid_spi_config);
	rc52x->transport = mfrc_transport_spi;
	rc52x->transport_config = &rfid_spi_config;
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

	print("Hello World!", 3);

	rfid5_init(&g_rc52x);

	char str[32];
	uint8_t version = -1;
	rc52x_get_chip_version(&g_rc52x, &version);
	sprintf(str, "MFRC522 %02X", version);
	print(str, 4);

	version = test_adxl_spi_read_id();
	sprintf(str, "ADXL ID  %03o", version);
	print(str, 5);

	uint32_t flash_id = test_flash_spi_read_id();

	test_sdmmc_spi_read_id();

	while (1) {

	}
}
