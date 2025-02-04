/*

 File: 		i2c_eeprom.h
 Author:	André van Schoubroeck
 License:	MIT


 MIT License

 Copyright (c) 2023 André van Schoubroeck <andre@blaatschaap.be>

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

#ifndef __I2C_EEPROM_H
#define __I2C_EEPROM_H

#include <stdint.h>
#include <bshal_i2cm.h>

typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t i2c_addr;
	uint16_t page_count;
	uint8_t page_size;
	uint8_t page_address_size;
} i2c_eeprom_t;

int i2c_eeprom_program(i2c_eeprom_t *i2c_eeprom, uint32_t address, void* data, size_t size);
int i2c_eeprom_read(i2c_eeprom_t *i2c_eeprom, uint32_t address, void* data, size_t size);

#endif // __I2C_EEPROM_H
