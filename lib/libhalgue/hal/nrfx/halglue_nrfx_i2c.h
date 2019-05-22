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


#ifndef _LIBHALGUE_NRFX_I2C_
#define _LIBHALGUE_NRFX_I2C_

#include "i2c.h"

#include "nrfx_twi.h"
#include "nrf_gpio.h

int32_t halgue_nrfx_i2c_init(nrfx_twi_t* twi_instance, int scl_pin, int sda_pin, i2c_instance_t *i2c_instance);
int32_t halgue_nrfx_i2c_send(nrfx_twi_t* twi_instance, uint8_t address, uint8_t * p_data, uint8_t length);
int32_t halgue_nrfx_i2c_recv(nrfx_twi_t* twi_instance, uint8_t address, uint8_t * p_data, uint8_t length);
int32_t halgue_nrfx_i2c_isok(nrfx_twi_t* twi_instance, uint8_t address);


#endif // _LIBHALGUE_NRFX_I2C_
