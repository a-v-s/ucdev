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



#include "system.h"

// NB. On STM32F0, stdfix conflicts with
// STM32CubeF0/Drivers/CMSIS/Core/Include/cmsis_gcc.h
// It should be included after STM32 includes stm32f0xx.h (included by system.h)
#include <stdfix.h>
// Might need to verify this also holds for latest CMSIS, and switch to upstream

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
#include "pcf8563.h"
#include "pcf8574.h"
#include "bmp280.h"

#include "rc52x_transport.h"
#include "rc52x.h"



bshal_i2cm_instance_t *gp_i2c = NULL;

void HardFault_Handler(void) {
	while(1);
}

#if defined __ARM_EABI__
void SysTick_Handler(void) {
	HAL_IncTick();
}
#endif

void SystemClock_Config(void) {
	HAL_InitTick(0);
	ClockSetup_HSE8_SYS72();
	//ClockSetup_HSI_SYS48();




#ifdef STM32F0
	ClockSetup_HSE8_SYS48();
#endif

#ifdef STM32F1
	ClockSetup_HSE8_SYS72();
#endif

#ifdef STM32F3
	ClockSetup_HSE8_SYS72();
#endif

#ifdef STM32F4
	SystemClock_HSE25_SYS84();
#endif

#ifdef STM32L0
	SystemClock_HSE8_SYS32();
#endif

#ifdef STM32L1
	SystemClock_HSE8_SYS48();
#endif
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

void rfid5_spi_init(rc52x_t *rc52x) {

	rc52x->transport_type = bshal_transport_i2c;
	rc52x->transport_instance.i2cm = gp_i2c;
	rc52x->delay_ms = bshal_delay_ms;
	rc52x_init(rc52x);
}

int main() {
#ifdef SEMI
	initialise_monitor_handles();
	printf("Hello world!\n");
#endif
	char str[32];
//	bmp280_test();

	SystemClock_Config();
	SystemCoreClockUpdate();

	HAL_Init();
	HAL_Delay(1);

	bshal_delay_init();
	bshal_delay_us(10);

	gp_i2c = i2c_init();

	display_init();
	draw_background();
	print("   I²C DEMO", 1);

//	sprintf(str,"REVID %04X",HAL_GetREVID());
//	print(str, 3);
//	sprintf(str,"DEVID %04X",HAL_GetDEVID());
//	print(str, 4);
	print(mcuid(), 6);
	print(cpuid(), 5);


	framebuffer_apply();

	int test_start = HAL_GetTick();
	bshal_delay_ms(1000);
	int test_stop = HAL_GetTick();
	int test = test_stop - test_start;

	pcf8563_t pcf8563 = { 0 };
	bh1750_t bh1750 = { 0 };
	ccs811_t ccs811 = { 0 };

	// For these 3/6/9-dof motion sensors
	// They support multiple protocols, so we need defintions for that
	// I have already written such abstraction for RFID readers

	//adxl345
	//mpu92
	//lis3dsh

	bmp280_t bmp280 = { 0 };
	sht3x_t sht3x = { 0 };
	lm75b_t lm75b = { 0 };
	si70xx_t si70xx = { 0 };
	hcd1080_t hcd1080 = { 0 };
	//i2c_eeprom




	if (0 == bshal_i2cm_isok(gp_i2c, BMP280_I2C_ADDR)) {
		bmp280.addr = BMP280_I2C_ADDR;
		bmp280.p_i2c = gp_i2c;

		bmp280_init(&bmp280);
	}

	if (0 == bshal_i2cm_isok(gp_i2c, PCF8563_I2C_ADDR)) {
		pcf8563.addr = PCF8563_I2C_ADDR;
		pcf8563.p_i2c = gp_i2c;
	}

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


	uint8_t rc52x_version;
/*
	///
	rc52x_t rc52x;
	rfid5_spi_init(&rc52x);
	rc52x_version = 0;
	rc52x_get_chip_version(&rc52x, &rc52x_version);
*/
	if (ccs811.addr) {

		ccs811_init(&ccs811);

	}

	int count = 0;
	char buff[64];

	//int state ='*';
	int state =2;

	while (1) {
		int line = 0;
		draw_plain_background();
		char key_pressed = get_key();

		switch (state) {
		case 3:

			if (pcf8563.addr) {
				pcf8563_time_t time = { 0 };
				pcf8563_get_time(&pcf8563, &time);
				buff[0] = buff[1] = buff[2] = ' ';
				buff[3 + 0] = '2';
				buff[3 + 1] = '0' + time.months.century;
				buff[3 + 2] = '0' + time.years.tens;
				buff[3 + 3] = '0' + time.years.unit;
				buff[3 + 4] = '-';
				buff[3 + 5] = '0' + time.months.tens;
				buff[3 + 6] = '0' + time.months.unit;
				buff[3 + 7] = '-';
				buff[3 + 8] = '0' + time.days.tens;
				buff[3 + 9] = '0' + time.days.unit;
				buff[3 + 10] = ' ';
				buff[3 + 11] = '0' + time.hours.tens;
				buff[3 + 12] = '0' + time.hours.unit;
				buff[3 + 13] = ':';
				buff[3 + 14] = '0' + time.minutes.tens;
				buff[3 + 15] = '0' + time.minutes.unit;
				buff[3 + 16] = ':';
				buff[3 + 17] = '0' + time.seconds.tens;
				buff[3 + 18] = '0' + time.seconds.unit;
				buff[3 + 19] = 0;
				print(buff, line);
				line++;
			}

			if (lm75b.addr) {
//				accum temperature_a;
//				lm75b_get_temperature_C_accum(&lm75b, &temperature_a);
//				sprintf(buff, "LM75B:  %3d.%02d°C  ", (int) temperature_a,
//						(int) (100 * temperature_a) % 100);
				float temperature_f;
				lm75b_get_temperature_C_float(&lm75b, &temperature_f);
				sprintf(buff, "LM75B:  %3d.%02d°C  ", (int) temperature_f,
						(int) (100 * temperature_f) % 100);				print(buff, line);
				print(buff, line);
				line++;
			}

			if (hcd1080.addr) {
//				accum temperature_a = -99.99;
//				accum huminity_a = -1;
//				hcd1080_get_humidity_accum(&hcd1080, &huminity_a);
//
//				hcd1080_get_temperature_C_accum(&hcd1080, &temperature_a);
//
//				sprintf(buff, "HCD1080:%3d.%02d°C %3d.%02d%%  ",
//						(int) temperature_a % 999,
//						abs((int) (100 * temperature_a)) % 100,
//						(int) huminity_a, abs((int) (100 * huminity_a)) % 100);

				float temperature_f = -99.99;
				float huminity_f = -1;
				hcd1080_get_humidity_float(&hcd1080, &huminity_f);

				hcd1080_get_temperature_C_float(&hcd1080, &temperature_f);

				sprintf(buff, "HCD1080:%3d.%02d°C %3d.%02d%%  ",
						(int) temperature_f % 999,
						abs((int) (100 * temperature_f)) % 100,
						(int) huminity_f, abs((int) (100 * huminity_f)) % 100);

				print(buff, line);
				line++;
			}
			if (si70xx.addr) {
//				accum temperature_a;
//				si70xx_get_temperature_C_accum(&si70xx, &temperature_a);
//				accum huminity_a;
//				si70xx_get_humidity_accum(&si70xx, &huminity_a);
//
//				sprintf(buff, "SI70XX: %3d.%02d°C %3d.%02d%%  ",
//						(int) temperature_a %999,
//						abs((int) (100 * temperature_a)) % 100,
//						(int) huminity_a, abs((int) (100 * huminity_a)) % 100);


				float temperature_f;
				si70xx_get_temperature_C_float(&si70xx, &temperature_f);
				float huminity_f;
				si70xx_get_humidity_float(&si70xx, &huminity_f);

				sprintf(buff, "SI70XX: %3d.%02d°C %3d.%02d%%  ",
						(int) temperature_f %999,
						abs((int) (100 * temperature_f)) % 100,
						(int) huminity_f, abs((int) (100 * huminity_f)) % 100);

				print(buff, line);
				line++;

			}

			if (sht3x.addr) {
//				accum temperature_a;
//				accum huminity_a;
//				sht3x_get_humidity_accum(&sht3x, &huminity_a);
//				sht3x_get_temperature_C_accum(&sht3x, &temperature_a);
//
//				sprintf(buff, "SHT3X:  %3d.%02d°C %3d.%02d%%  ",
//						(int) temperature_a %999,
//						abs((int) (100 * temperature_a)) % 100,
//						(int) huminity_a, abs((int) (100 * huminity_a)) % 100);

				float temperature_f;
				float huminity_f;
				sht3x_get_humidity_float(&sht3x, &huminity_f);
				sht3x_get_temperature_C_float(&sht3x, &temperature_f);

				sprintf(buff, "SHT3X:  %3d.%02d°C %3d.%02d%%  ",
						(int) temperature_f %999,
						abs((int) (100 * temperature_f)) % 100,
						(int) huminity_f, abs((int) (100 * huminity_f)) % 100);

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
				sprintf(buff, "BH1750:    %6d lux", lux);
				print(buff, line);
				line++;
			}
			if (ccs811.addr) {
				//			static uint16_t TVOC = 0;
				//			static uint16_t eCO2 = 0;
				//			css811_measure(&ccs811, &eCO2, &TVOC);
				//			sprintf(buff, "CCS811:  TVOC %4d eCO2 %4d", TVOC, eCO2);

				static uint16_t TVOC = 0;
				css811_measure(&ccs811, NULL, &TVOC);
				sprintf(buff, "CCS811:    %4d ppb TVOC", TVOC);
				print(buff, line);
				line++;
			}

			if (bmp280.addr) {
//				accum temperature_a;
//				long accum pressure_la;
//				bmp280_measure_a(&bmp280, &temperature_a, &pressure_la);
//
//
//				sprintf(buff, "BMP280: %3d.%02d°C %d hPa  ",
//						(int) temperature_a % 999,
//						abs((int) (100 * temperature_a)) % 100,
//						(int) pressure_la / 100);

				float temperature_f;
				float pressure_f;
				bmp280_measure_f(&bmp280, &temperature_f, &pressure_f);


				sprintf(buff, "BMP280: %3d.%02d°C %d hPa  ",
						(int) temperature_f % 999,
						abs((int) (100 * temperature_f)) % 100,
						(int) pressure_f / 100);

				print(buff, line);
				line++;

			}
/*
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
*/

			break;
		case '*':
			print("MENU", line++);
			print("1: SET TIME", line++);
			print("2: SCAN BUS", line++);
			print("3: SENSOR DATA", line++);

			switch (key_pressed) {
			case '1':
				count = 0;
				state = 1;
				break;
			case '2':
				state = 2;
				break;
			case '3':
				state = 3;
				break;
			}
			break;
			case 1:
				print("1: SET TIME", line++);
				static char datetimestring[20];
				int cpos;
				cpos = count + 2;
				if (count > 1) cpos++;
				if (count > 3) cpos++;
				if (count > 5) cpos++;
				if (count > 7) cpos++;
				if (count > 9) cpos++;

				for (int i = 0 ; i < 20 ; i++)
					buff[i] = cpos == i ? '^' : ' ';
				buff[20] = 0;

				if (!count) strcpy(datetimestring, "20yy-mm-dd HH:MM:SS");
				if (key_pressed) {

					// We've got the millenium bug here.
					// Don't blaim me, it's a hardware problem.
					// The DS1307 only supports a 2 digit year
					// However, the PCF8563 got a century bit.
					// This needs some investigation what its influence is\
					// on the leap year. 2000 was a leap year, 2100 will not be.
					// So... unless the century bit toggles this, for which I
					// have not (yet) found any clues in the datasheet, we
					// can only support this century out of the box.

					if (key_pressed == 'D') {
						count--;
					}

					switch (count) {
					case 0:
						if (key_pressed >= '0' && key_pressed <= '9') {
							datetimestring[cpos] = key_pressed;
							count++;
						}
						break;
					case 1:
						if (key_pressed >= '0' && key_pressed <= '9') {
							datetimestring[cpos] = key_pressed;
							count++;
						}
						break;
					case 2:
						if (key_pressed >= '0' && key_pressed <= '1') {
							datetimestring[cpos] = key_pressed;
							count++;
						}
						break;
					case 3:
						if ((datetimestring[5] == '1' && key_pressed >= '0'
								&& key_pressed <= '2')
								|| (datetimestring[5] == '0' && key_pressed >= '1'
										&& key_pressed <= '9')) {
							datetimestring[cpos] = key_pressed;
							count++;
						}
						break;
					case 4:
						if ((key_pressed != '3' || !
								(datetimestring[5] == '0' && datetimestring[6] == '2')
								 )
								&& (key_pressed >= '0' && key_pressed <= '3'))
						 {
							datetimestring[cpos] = key_pressed;
							count++;
						}
						break;
					case 5:
						// TODO got to check the number of days in the month

						if (key_pressed >= '0' && key_pressed <= '9') {
							{
								datetimestring[cpos] = key_pressed;
								count++;
							}
							break;

						}
						break;
					}
				}
				print(datetimestring, 3);
				print(buff, 4);
				break;
			case 2:
				print("I²C BUS SCAN",0);
				scan_i2c();
				break;

		}
		sprintf(buff, "Keypad:  ");
		buff[8] = key_pressed;

		switch (key_pressed) {
		case '*':
			state = '*';
			break;
		}

		print(buff, 8);
		line++;
		framebuffer_apply();
		if (key_pressed)
			while (read_keypad())
				__NOP();

	}

}

