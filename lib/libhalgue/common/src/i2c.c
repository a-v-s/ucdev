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

#include "i2c.h"

int i2c_send(i2c_instance_t* i2c_instance, uint8_t address, uint8_t * p_data, uint8_t length, bool no_ack){
	return i2c_instance->i2c_send ? i2c_instance->i2c_send(i2c_instance->drv_specific,address, p_data, length, no_ack) : -1;
}
int i2c_recv(i2c_instance_t* i2c_instance, uint8_t address, uint8_t * p_data, uint8_t length){
	return i2c_instance->i2c_recv ? i2c_instance->i2c_recv(i2c_instance->drv_specific,address, p_data, length) : -1;
}
int i2c_present(i2c_instance_t* i2c_instance, uint8_t address){
	return i2c_instance->i2c_present ? i2c_instance->i2c_present(i2c_instance->drv_specific,address) : -1;
}


// Convinience functions
int i2c_send_reg(i2c_instance_t* i2c_instance, uint8_t address, uint8_t reg, uint8_t * p_data, uint8_t length){
    int result;
    result = i2c_send(i2c_instance, address, &reg, 1, true);
    if (result) return result;
    return i2c_send(i2c_instance, reg, p_data, length, false);
}

int i2c_recv_reg(i2c_instance_t* i2c_instance, uint8_t address, uint8_t reg, uint8_t * p_data, uint8_t length){
    int result;
    result = i2c_send(i2c_instance, address, &reg, 1, true);
    if (result) return result;
    return i2c_recv(i2c_instance, reg, p_data, length);
}
