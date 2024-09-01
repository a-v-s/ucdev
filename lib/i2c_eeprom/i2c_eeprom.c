/*

 File: 		i2c_eeprom.c
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

#include <stdbool.h>
#include <string.h>
#include <stdfix.h>
#include <inttypes.h>

#include <system.h>
#include <bshal_i2cm.h>
#include <bshal_delay.h>
#include <bshal_i2cm.h>

#include "i2c_eeprom.h"

#include <endian.h>
#include <stdio.h>

int i2c_eeprom_program(i2c_eeprom_t *i2c_eeprom, uint32_t address, void* data, size_t size){
	// Initial implementation supports only I²C EEPROMS up to 2Kbit (256 bytes)
	// TODO: Support larger memories with word address expanding into the I²C address
	//			These are 4Kbit, 8Kbit, 16Kbit EEPROMS 
	// TODO: Support larger memories with 16-bit word address 
	//			Seen at larger memories, 32 Kbit, 64Kbit, 128Kbit

	// Code below is adopted from the SPI FLASH code
	size_t page_size = i2c_eeprom->page_size;
	size_t write_size = page_size - (address % page_size);
	if (write_size > size) write_size = size;
	int data_offset = 0;
	uint8_t addr;
	while (size) {
		addr = (address+data_offset);

		printf("Writing %3d bytes to address %02X\n",
				write_size, addr);

		int result = bshal_i2cm_send_reg(i2c_eeprom->p_i2c,i2c_eeprom->i2c_addr,addr,data + data_offset, write_size);
		if(result) return result;
		bshal_delay_ms(5); // need a delay to write multiple pages
		data_offset += write_size;
		size -= write_size;
		write_size = (size < page_size) ? size : page_size;
	}
	return 0;
}

int i2c_eeprom_read(i2c_eeprom_t *i2c_eeprom, uint32_t address, void* data, size_t size){
	// Initial implementation supports only I²C EEPROMS up to 2Kbit (256 bytes)
	// TODO: Support larger memories with word address expanding into the I²C address
	//			These are 4Kbit, 8Kbit, 16Kbit EEPROMS 
	// TODO: Support larger memories with 16-bit word address 
	//			Seen at larger memories, 32 Kbit, 64Kbit, 128Kbit
	return bshal_i2cm_recv_reg(i2c_eeprom->p_i2c,i2c_eeprom->i2c_addr,address,data,size);
}


