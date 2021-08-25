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

#include "i2c.h"
#include "lm75b.h"
#include "sht3x.h"
#include "bh1750.h"
#include "hcd1080.h"
#include "si70xx.h"
#include "ccs811.h"

#include "rc52x_transport.h"
#include "rc52x.h"

bshal_i2cm_instance_t *gp_i2c = NULL;

void HardFault_Handler(void) {

}

void SysTick_Handler(void) {
	HAL_IncTick();
}

void SystemClock_Config(void) {
	ClockSetup_HSE8_SYS72();
}

void scan_i2c(void) {
	char line[32] = { 0 };
	int row = 2;
	int column = 0;
	for (int i = 0x08; i < 0x78; i++) {
		int ready = bshal_i2cm_isok(gp_i2c, i);
		if (!ready) {
			sprintf(line + column, "%02X ", i);
			column += 3;
			if (column >= 24) {
				column = 0;
				print(line, row);
				row++;
				line[0] = 0;
			}
		}
	}
	print(line, row);
}

void rfid5_init(rc52x_t *rc52x) {

	rc52x->transport = mfrc_transport_i2c;
	rc52x->transport_config = gp_i2c;
	rc52x->delay_ms = bshal_delay_ms;
	RC52X_Init(rc52x);
}

int main() {
#ifdef SEMI
	initialise_monitor_handles();
	printf("Hello world!\n");
#endif

	SystemClock_Config();
	SystemCoreClockUpdate();

	HAL_Init();

	bshal_delay_init();
	bshal_delay_us(10);

	gp_i2c = i2c_init();

	lm75b_t lm75b = { 0 };
	sht3x_t sht3x = { 0 };
	bh1750_t bh1750 = { 0 };
	si70xx_t si70xx = { 0 };
	hcd1080_t hcd1080 = { 0 };
	ccs811_t ccs811 = { 0 };

	if (0 == bshal_i2cm_isok(gp_i2c, CCS811_I2C_ADDR1)) {
		ccs811.addr = CCS811_I2C_ADDR1;
		ccs811.p_i2c = gp_i2c;
	}

	if (0 == bshal_i2cm_isok(gp_i2c, LM75B_ADDR)) {
		lm75b.addr = LM75B_ADDR;
		lm75b.p_i2c = gp_i2c;
	}

	if (0 == bshal_i2cm_isok(gp_i2c, SHT3X_ADDR)) {
		sht3x.addr = SHT3X_ADDR;
		sht3x.p_i2c = gp_i2c;
	}

	if (0 == bshal_i2cm_isok(gp_i2c, BH1750_ADDR)) {
		bh1750.addr = BH1750_ADDR;
		bh1750.p_i2c = gp_i2c;
	}

	if (0 == bshal_i2cm_isok(gp_i2c, SI7021_ADDR)) {
		// either si7021 or hcd1080
		bool identify;
		si70xx.addr = SI7021_ADDR;
		si70xx.p_i2c = gp_i2c;
		si70xx_identify(&si70xx, &identify);
		if (!identify) {
			si70xx.addr = 0;
		}

		hcd1080.addr = SI7021_ADDR;
		hcd1080.p_i2c = gp_i2c;
		hcd1080_identify(&hcd1080, &identify);
		if (!identify) {
			hcd1080.addr = 0;
		}
	}

	display_init();
	draw_background();

	char str[32];
	uint8_t rc52x_version;

	///
	rc52x_t rc52x;
	rfid5_init(&rc52x);
	rc52x_version = 0;
	rc52x_get_chip_version(&rc52x, &rc52x_version);

	if (ccs811.addr) {
		__BKPT(0);
		ccs811_init(&ccs811);
		while (1) {
				css811_measure(&ccs811);
			}
	}


	print("I²C DEMO", 0);
	framebuffer_apply();

	int count = 0;
	char buff[64];


	while (1) {
		draw_plain_background();

		int line = 0;

		if (lm75b.addr) {
			//float temperature_f = lm75b_get_temperature_C_float(&lm75b);
			//sprintf(buff, "Temperature:  %6.2f °C  ", temperature_f);

			accum temperature_a;
			lm75b_get_temperature_C_accum(&lm75b, &temperature_a);
			sprintf(buff, "LM75B:   %3d.%02d°C  ", (int) temperature_a,
					(int) (100 * temperature_a) % 100);
			print(buff, line);
			line++;
		}

		//?? stoort met rc522
		if (hcd1080.addr) {
			accum temperature_a = -99.99;
			accum huminity_a = -1;
			hcd1080_get_humidity_accum(&hcd1080, &huminity_a);

			hcd1080_get_temperature_C_accum(&hcd1080, &temperature_a);

			sprintf(buff, "HCD1080: %3d.%02d°C %3d.%02d%%  ",
					(int) temperature_a, abs((int) (100 * temperature_a)) % 100,
					(int) huminity_a, abs((int) (100 * huminity_a)) % 100);
			print(buff, line);
			line++;
		}
		if (si70xx.addr) {
			accum temperature_a;
			si70xx_get_temperature_C_accum(&si70xx, &temperature_a);
			accum huminity_a;
			si70xx_get_humidity_accum(&si70xx, &huminity_a);

			sprintf(buff, "SI70XX:  %3d.%02d°C %3d.%02d%%  ",
					(int) temperature_a, abs((int) (100 * temperature_a)) % 100,
					(int) huminity_a, abs((int) (100 * huminity_a)) % 100);
			print(buff, line);
			line++;

		}

		//?? stoort met rc522
		if (sht3x.addr) {
			accum temperature_a;
			accum huminity_a;
			sht3x_get_humidity_accum(&sht3x, &huminity_a);
			sht3x_get_temperature_C_accum(&sht3x, &temperature_a);

			sprintf(buff, "SHT3X:   %3d.%02d°C %3d.%02d%%  ",
					(int) temperature_a, abs((int) (100 * temperature_a)) % 100,
					(int) huminity_a, abs((int) (100 * huminity_a)) % 100);
			print(buff, line);

			print(buff, line);
			line++;

		}

		if (bh1750.addr) {
			static int lux;

			// Reading it too fast stops it from updating
			// Therefore only reading it every 10 rounds
			static int swipswap;
			if (!(swipswap % 10))
				bh1750_measure_ambient_light(&bh1750, &lux);
			swipswap++;
			sprintf(buff, "BH1750:  %6d lux", lux);
			print(buff, line);
			line++;

			if (rc52x_version) {
				// When either SHT3x or HCD1080 are being read,
				// The mfrc522 stops reading cards
				// This will need more investigation
				{

					picc_t picc = { 0 };

					rc52x_result_t status = 0;
					status = PICC_RequestA(&rc52x, &picc);

					if (status) {
						status = PICC_RequestA(&rc52x, &picc);
					}

					if (!status) {
						sprintf(str, "ATQA %04X", picc.atqa.as_uint16);
						//print(str, 0);
						status = PICC_Select(&rc52x, &picc, 0);
					}
					if (!status) {

						sprintf(str, "UID  ");
						for (int i = 0; i < picc.size; i++)
							sprintf(str + strlen(str), "%02X", picc.uidByte[i]);
						print(str, line);
						//sprintf(str, "SAK  %02X", picc.sak.as_uint8);
						//print(str, 1);
					} else {
						print("No Card found", line);
					}
					line++;
				}
			}

			sprintf(buff, "Keypad:  ");
			buff[8] = get_key();

			print(buff, line);
			line++;

			framebuffer_apply();

		}
	}
}
