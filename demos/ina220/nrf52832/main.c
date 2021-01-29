/*

 File: 		main.c
 Author:	André van Schoubroeck
 License:	MIT


 MIT License

 Copyright (c) 2020 André van Schoubroeck  <andre@blaatschaap.be>

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

/*
 A quick test whether the ina220 chip is working
 I will turn it into a proper library later
 */

#define INA220_ADDR 	(0b1001111)
#define SDA_PIN			(24)
#define SCL_PIN			(23)

#include <stdint.h>
#include "nrfx_systick.h"

#define INA220_REG_CONFIGURATION (0)
#define INA220_REG_SHUNT_VOLTAGE (1)
#define INA220_REG_BUS_VOLTAGE   (2)
#define INA220_REG_POWER         (3)
#define INA220_REG_CURRENT       (4)
#define INA220_REG_CALIBRATION   (5)

// Note: using nrfx twim directly. I'll have to look up the state of my i2c
//	abstraction layer, so the driver this will turn into is platform independant
#include "nrfx_twim.h"

void delay_ms(uint32_t ms) {
	nrfx_systick_delay_ms(ms);
}

volatile m_twi_busy = false;
void twim_evt_handler(nrfx_twim_evt_t const *p_event, void *p_context) {
	m_twi_busy = false;
}

int main() {

	nrfx_twim_config_t twim_config = { .scl = SCL_PIN, .sda = SDA_PIN,
			.frequency = NRF_TWIM_FREQ_100K, .interrupt_priority = 4,
			.hold_bus_uninit = true };

	/*
	 nrfx_err_t nrfx_twim_init(nrfx_twim_t const *        p_instance,
	 nrfx_twim_config_t const * p_config,
	 nrfx_twim_evt_handler_t    event_handler,
	 void *                     p_context);
	 */
	nrfx_twim_t twim = NRFX_TWIM_INSTANCE(0);

	int status = nrfx_twim_init(&twim, &twim_config, NULL, NULL);
	nrfx_twim_enable(&twim);
	nrfx_twim_xfer_desc_t xfer;
	uint8_t reg;
	uint16_t config;
	uint16_t bus_voltage;
	int16_t shunt_voltage;
	xfer.type = NRFX_TWIM_XFER_TXRX;
	xfer.address = INA220_ADDR;
	xfer.primary_length = 1;
	xfer.secondary_length = 2;
	xfer.p_primary_buf = &reg;

	int voltage = 0;
	int current = 0;


	while (1) {
		reg = INA220_REG_CONFIGURATION;
		xfer.p_secondary_buf = &config;

		m_twi_busy = true;
		status = nrfx_twim_xfer(&twim, &xfer, 0);
		// expected value 0x399F


		reg = INA220_REG_SHUNT_VOLTAGE;
		xfer.p_secondary_buf = &shunt_voltage;
		status = nrfx_twim_xfer(&twim, &xfer, 0);
		current = (int16_t)__builtin_bswap16(shunt_voltage);


		reg = INA220_REG_BUS_VOLTAGE;
		xfer.p_secondary_buf = &bus_voltage;
		status = nrfx_twim_xfer(&twim, &xfer, 0);

		// The INA220 chip presents its data in BIG ENDIAN format
		voltage = ( __builtin_bswap16(bus_voltage) & ~0b11 ) >> 1;
	}

	while (1)
		;;
}
