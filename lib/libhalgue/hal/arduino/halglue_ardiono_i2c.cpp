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

#include <Wire.h>
#include "halglue_arduino_i2c.hpp"

i2c_instance_t arduino_i2c_init(TwoWire * i2c) {
    i2c_instance_t instance = {i2c,arduino_i2c_send,arduino_i2c_recv, arduino_i2c_isok};
    return instance;
}

int arduino_i2c_send(void* drv_specific, uint8_t address, uint8_t * p_data, uint8_t length, bool no_stop){
    TwoWire * i2c = (TwoWire *)drv_specific;
    Wire.beginTransmission(address);
    for (int i = 0 ; i < length; i++)
    Wire.write(p_data[i]);
    int status = Wire.endTransmission(!no_stop);
    switch (status) {
        case 0: return LIBGLUE_I2C_STATUS_OK;
        case 1: return LIBGLUE_I2C_STATUS_ERROR_BAD_PARAM;
        case 2: return LIBGLUE_I2C_STATUS_ERROR_ANACK;
        case 3: return LIBGLUE_I2C_STATUS_ERROR_DNACK;
        default: return LIBLUE_I2C_STATUS_ERROR_UNKNOWN;
    }
}
int arduino_i2c_recv(void* drv_specific, uint8_t address, uint8_t * p_data, uint8_t length){
    TwoWire * i2c = (TwoWire *)drv_specific;

    return -1; // Not implemented
}
int arduino_i2c_isok(void* drv_specific, uint8_t address){
    TwoWire * i2c = (TwoWire *)drv_specific;

    Wire.beginTransmission(address);
    int status = Wire.endTransmission();
        switch (status) {
        case 0: return LIBGLUE_I2C_STATUS_OK;
        case 1: return LIBGLUE_I2C_STATUS_ERROR_BAD_PARAM;
        case 2: return LIBGLUE_I2C_STATUS_ERROR_ANACK;
        case 3: return LIBGLUE_I2C_STATUS_ERROR_DNACK;
        default: return LIBLUE_I2C_STATUS_ERROR_UNKNOWN;
    }
}
