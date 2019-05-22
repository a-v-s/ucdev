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

#ifndef _LIBHALGUE_I2C_
#define _LIBHALGUE_I2C_

#include <stdint.h>
#include <stdbool.h>

typedef int32_t (*i2c_send_f)(void* drv_specific, uint8_t address, uint8_t * p_data, uint8_t length, bool no_ack);
typedef int32_t (*i2c_recv_f)(void* drv_specific, uint8_t address, uint8_t * p_data, uint8_t length);
typedef int32_t (*i2c_isok_f)(void* drv_specific, uint8_t address);

#define LIBGLUE_I2C_STATUS_OK            0
#define LIBGLUE_I2C_STATUS_BAD_PARAM    -1
#define LIBGLUE_I2C_STATUS_ANACK        -10
#define LIBGLUE_I2C_STATUS_DNACK        -11

typedef struct i2c_instance_t{
	void* drv_specific;
	i2c_send_f i2c_send;
	i2c_recv_f i2c_recv;
	i2c_isok_f i2c_present;
} i2c_instance_t;


int i2c_send(i2c_instance_t* i2c_instance, uint8_t address, uint8_t * p_data, uint8_t length, bool no_ack);
int i2c_recv(i2c_instance_t* i2c_instance, uint8_t address, uint8_t * p_data, uint8_t length);
int i2c_present(i2c_instance_t* i2c_instance, uint8_t address);

int i2c_send_reg(i2c_instance_t* i2c_instance, uint8_t address, uint8_t reg, uint8_t * p_data, uint8_t length);
int i2c_recv_reg(i2c_instance_t* i2c_instance, uint8_t address, uint8_t reg, uint8_t * p_data, uint8_t length);


#endif // _LIBHALGUE_I2C_
