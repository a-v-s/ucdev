/*
    MIT License

    Copyright (c) 2018, 2019 André van Schoubroeck

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

#include "halglue_nrfx_i2c.h"


int32_t halgue_nrfx_i2c_recover(int scl_pin) {
	// Recover from "error 3" -- SDA line stuck low
	// http://www.utasker.com/forum/index.php?topic=990.0
	nrf_gpio_cfg_output(scl_pin);
	for (int i = 0 ; i < 16; i++) {
		nrfx_coredep_delay_us(10);
		nrf_gpio_pin_clear(scl_pin);
		nrfx_coredep_delay_us(10);
		nrf_gpio_pin_set(scl_pin);
	}
}

int32_t halgue_nrfx_i2c_init(nrfx_twi_t* twi_instance, int scl_pin, int sda_pin, i2c_instance_t *i2c_instance){
	if (!twi_instance) return -1;
	nrfx_twi_uninit(twi_instance);
	halgue_nrfx_i2c_recover(scl_pin);
	nrfx_twi_config_t i2c_config = NRFX_TWI_DEFAULT_CONFIG;
	i2c_config.scl = scl_pin;
	i2c_config.sda = sda_pin;
	i2c_config.frequency = NRF_TWI_FREQ_400K;
	i2c_config.hold_bus_uninit = true;


	int res = nrfx_twi_init(twi_instance, &i2c_config, NULL, NULL);
	if (res) return res;
	nrfx_twi_enable(twi_instance);
	i2c_instance->drv_specific=twi_instance;
	i2c_instance->i2c_recv = (i2c_recv_f)halgue_nrfx_i2c_recv;
	i2c_instance->i2c_send = (i2c_send_f)halgue_nrfx_i2c_send;
	i2c_instance->i2c_present = (i2c_present_f)halgue_nrfx_i2c_present;

	return 0;
}

int32_t halgue_nrfx_i2c_send(nrfx_twi_t* twi_instance, uint8_t address, uint8_t * p_data, uint8_t length, bool no_ack){
	if (!twi_instance) return -1;
	return nrfx_twi_tx(twi_instance, address, p_data, length, no_ack);
}

int32_t halgue_nrfx_i2c_recv(nrfx_twi_t* twi_instance, uint8_t address, uint8_t * p_data, uint8_t length){
	if (!twi_instance) return -1;
	return nrfx_twi_rx(twi_instance, address, p_data, length);
}

int32_t halgue_nrfx_i2c_present(nrfx_twi_t* twi_instance, uint8_t address) {
	if (!twi_instance) return -1;
	return -1;
}
