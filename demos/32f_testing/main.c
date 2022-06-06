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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "system.h"

#include "bshal_spim.h"
#include "bshal_delay.h"
#include "bshal_i2cm.h"
#include "i2c.h"

#include "bh1750.h"
#include "ccs811.h"
#include "sht3x.h"

#include "uart.h" 

bshal_i2cm_instance_t *gp_i2c = NULL;

void HardFault_Handler(void) {
	while (1)
		;
}

#if defined __ARM_EABI__
void SysTick_Handler(void) {
	HAL_IncTick();
}
#endif

void SystemClock_Config(void) {
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

char* getserialstring(void) {
	static char serialstring[25];
	char *serial = (char*) (0x1FFFF7E8);
	sprintf(serialstring, "%02X%02X%02X%02X"
			"%02X%02X%02X%02X"
			"%02X%02X%02X%02X", serial[0], serial[1], serial[2], serial[3],
			serial[4], serial[5], serial[6], serial[7], serial[8], serial[9],
			serial[10], serial[11]);
	return serialstring;
}

void test_and_recover(void) {
	if (0 == bshal_i2cm_isok(gp_i2c, SSD1306_ADDR)) {
		printf("I²C BUS OK\n");
	} else {
		printf("I²C BUS Failed, re-initialisng...\n");
		gp_i2c = i2c_init();
		if (0 == bshal_i2cm_isok(gp_i2c, SSD1306_ADDR)) {
			printf("I²C BUS OK\n");
		} else {
			printf("I²C BUS Failed\n");
			printf("Bus recovery failed, aboring tests...\n");
			while (1)
				;
		}
	}
}

int main() {
#ifdef SEMI
	initialise_monitor_handles();
#endif

#ifdef UART
	initialise_uart();
#endif
	SystemClock_Config();
	SystemCoreClockUpdate();

	HAL_Init();
	bshal_delay_init();

	printf("----------------------------------------\n");
	printf(" BlaatSchaap 32F103 I2C Testing         \n");
	printf("----------------------------------------\n");
	printf(" Core         : %s\n", cpuid());
	printf(" Guessed chip : %s\n", mcuid());
	printf(" Serial number: %s\n", getserialstring());
	printf("----------------------------------------\n");

	gp_i2c = i2c_init();

	// Inventarise the I2c deives to check
	// ccs811 and hcd1080 are known issues on HK32 and GD32

	// First do the standard PIO variant.
	// Then we might add some IRQ and DMA variants

	printf("\n\nPlease note the test assumed the microcontroller under test\n");
	printf("is assumed to be placed into a BlaatSchaap PMOD Baseboard\n");
	printf("and connected to a BlaatSchaap I²C Modules board with all\n");
	printf("modules in place\n\n");


	// TODO: we need to run these tests at 100 and 400 KHz

	printf("Running I²C addressing tests...\n");

	printf("Testing SSD1306...     ");
	if (0 == bshal_i2cm_isok(gp_i2c, SSD1306_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		printf("Further testing aborted\n");
		while (1)
			;
	}

	printf("Testing ADXL345...     ");
	if (0 == bshal_i2cm_isok(gp_i2c, ADXL345_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing PCF8574T...    ");
	if (0 == bshal_i2cm_isok(gp_i2c, PCF8574T_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing BH1750...      ");
	if (0 == bshal_i2cm_isok(gp_i2c, BH1750_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

//	printf("Testing ...");
//	if (0 == bshal_i2cm_isok(gp_i2c, MFRC522_ADDR)) {
//		printf("OK\n");
//	} else {
//		printf("Failed\n");
//	}

	printf("Testing SHT3X...       ");
	if (0 == bshal_i2cm_isok(gp_i2c, SHT3X_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing LM75B...       ");
	if (0 == bshal_i2cm_isok(gp_i2c, LM75B_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing EEPROM...      ");
	if (0 == bshal_i2cm_isok(gp_i2c, EEPROM_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing LIS3DH...      ");
	if (0 == bshal_i2cm_isok(gp_i2c, LIS3DH_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

//	printf("Testing PN532_ADDR...");
//	if (0 == bshal_i2cm_isok(gp_i2c,PN532_ADDR )) {
//		printf("OK\n");
//	} else {
//		printf("Failed\n");
//	}

	printf("Testing SSD1306...     ");
	if (0 == bshal_i2cm_isok(gp_i2c, SSD1306_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing SI7021...      ");
	if (0 == bshal_i2cm_isok(gp_i2c, SI7021_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing CCS811...      ");
	if (0 == bshal_i2cm_isok(gp_i2c, CCS811_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Testing PCF8523...     ");
	if (0 == bshal_i2cm_isok(gp_i2c, PCF8523_ADDR)) {
		printf("OK\n");
	} else {
		printf("Failed\n");
		test_and_recover();
	}

	printf("Running I²C communication tests...\n");

	printf("Testing ADXL345...     ");
	printf("TODO\n");

	printf("Testing PCF8574T...    ");
	printf("TODO\n");

	printf("Testing BH1750...      ");
	if (0 == bshal_i2cm_isok(gp_i2c, BH1750_ADDR)) {
		bh1750_t bh1750;
		bh1750.addr = BH1750_ADDR;
		bh1750.p_i2c = gp_i2c;
		static int lux;
		if (0 == bh1750_measure_ambient_light(&bh1750, &lux)) {
			printf("OK:    %6d lux\n", lux);
		} else {
			printf("Failed\n");
			test_and_recover();
		}
	}

	printf("Testing SHT3X...       ");
	if (0 == bshal_i2cm_isok(gp_i2c, SHT3X_ADDR)) {
		sht3x_t sht3x;
		sht3x.addr = SHT3X_ADDR;
		sht3x.p_i2c = gp_i2c;
		float temperature_f;
		float huminity_f;
		if (0 == sht3x_get_humidity_float(&sht3x, &huminity_f)
				&& 0 == sht3x_get_temperature_C_float(&sht3x, &temperature_f)) {

			printf("OK:  %3d.%02d°C %3d.%02d%%  ", (int) temperature_f % 999,
					abs((int) (100 * temperature_f)) % 100, (int) huminity_f,
					abs((int) (100 * huminity_f)) % 100);
		} else {
			printf("Failed\n");
			test_and_recover();
		}
	}

	printf("Testing LM75B...       ");
	printf("TODO\n");
	printf("Testing EEPROM...      ");
	printf("TODO\n");
	printf("Testing LIS3DH...      ");
	printf("TODO\n");
	printf("Testing SSD1306...     ");
	printf("TODO\n");
	printf("Testing SI7021...      ");
	printf("TODO\n");
	printf("Testing CCS811...      ");

	if (0 == bshal_i2cm_isok(gp_i2c, CCS811_I2C_ADDR1)) {
		ccs811_t ccs811;
		ccs811.addr = CCS811_I2C_ADDR1;
		ccs811.p_i2c = gp_i2c;
		ccs811_init(&ccs811);

		static uint16_t TVOC = 0;
		if (0 == css811_measure(&ccs811, NULL, &TVOC)) {
			printf("OK:    %4d ppb TVOC\n", TVOC);
		} else {
			printf("Failed\n");
			test_and_recover();
		}

	}

	printf("Testing PCF8523...     ");
	printf("TODO\n");

	int c;
	while (1) {
		c = getchar();
		(void) c;
	}
}

