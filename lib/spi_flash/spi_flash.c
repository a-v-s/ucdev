/*

 File: 		spi_flash.c
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
#include <stdio.h>

#include <system.h>
#include <bshal_spim.h>
#include <bshal_delay.h>
#include <bshal_i2cm.h>

#include "spi_flash.h"

#include "endian.h"

int spi_flash_cmd(bshal_spim_instance_t *spim, uint8_t cmd, void *request,
		uint16_t request_size, uint8_t dummy_count, void *response,
		uint16_t reponse_size) {
	// We must transmit 0xFF while receiving
	memset(response, 0xFF, reponse_size);
	int result;
	result = bshal_spim_transmit(spim, &cmd, 1, true);
	if (result)
		goto error;
	if (request && request_size) {
		result = bshal_spim_transmit(spim, request, request_size, true);
		if (result)
			goto error;
	}
	if (dummy_count) {
		uint8_t dummies[dummy_count] = { };
		result = bshal_spim_transmit(spim, dummies, dummy_count, true);
		if (result)
			goto error;
	}

	result = bshal_spim_transceive(spim, response, reponse_size, false);
	if (result) {
		goto error;
	}

	return 0;
	error:

	// TODO deselct
	return result;
}
bool spi_flash_busy(bshal_spim_instance_t *spim) {
	spi_flash_sr1_t sr1;
	spi_flash_cmd(spim, SPI_FLASH_CMD_RDSR1, NULL, 0, SPI_FLASH_DMY_RDSR1, &sr1, sizeof(sr1));
	return sr1.busy;
}

bool spi_flash_wel(bshal_spim_instance_t *spim) {
	spi_flash_sr1_t sr1;
	spi_flash_cmd(spim, SPI_FLASH_CMD_RDSR1, NULL, 0, SPI_FLASH_DMY_RDSR1, &sr1, sizeof(sr1));
	return sr1.wel;
}


int spi_flash_write_enable(bshal_spim_instance_t *spim){
	puts("Sending Write Enable Command");
	spi_flash_cmd(spim, SPI_FLASH_CMD_WREN, NULL, 0, SPI_FLASH_DMY_WREN, NULL, 0);
	if (!spi_flash_wel(spim)) {
		puts("Failed to enable write. Is the Write Protect enabled?");
		return -1;
	}
	return 0;
}

int spi_flash_erase_page_256(bshal_spim_instance_t *spim, uint32_t address){
	// Note: Not all flash chips implement page erase
	// So far I've only seen this on PUYA flash
	size_t page_size = 256; (void)page_size;
	if (spi_flash_write_enable(spim)) return -1;
	uint8_t addr[3] = {};
	addr[2] = address;
	addr[1] = address>> 8;
	addr[0] = address>> 16;
	spi_flash_cmd(spim, SPI_FLASH_CMD_PE, addr, sizeof(addr), SPI_FLASH_DMY_PE, NULL, 0);
	while (spi_flash_busy(spim));
	return 0;
}

int spi_flash_erase_sector_4k(bshal_spim_instance_t *spim, uint32_t address){
	size_t sector_size = 4096; (void)sector_size;
	if (spi_flash_write_enable(spim)) return -1;
	uint8_t addr[3] = {};
	addr[2] = address;
	addr[1] = address>> 8;
	addr[0] = address>> 16;
	spi_flash_cmd(spim, SPI_FLASH_CMD_SE, addr, sizeof(addr), SPI_FLASH_DMY_SE, NULL, 0);
	while (spi_flash_busy(spim));
	return 0;
}


int spi_flash_erase_block_32k(bshal_spim_instance_t *spim, uint32_t address){
	size_t block_size = 32768; (void)block_size;
	if (spi_flash_write_enable(spim)) return -1;
	uint8_t addr[3] = {};
	addr[2] = address;
	addr[1] = address>> 8;
	addr[0] = address>> 16;
	spi_flash_cmd(spim, SPI_FLASH_CMD_BE32, addr, sizeof(addr), SPI_FLASH_DMY_BE32, NULL, 0);
	while (spi_flash_busy(spim));
	return 0;
}

int spi_flash_erase_block_64k(bshal_spim_instance_t *spim, uint32_t address){
	size_t block_size = 65536; (void)block_size;
	if (spi_flash_write_enable(spim)) return -1;
	uint8_t addr[3] = {};
	addr[2] = address;
	addr[1] = address>> 8;
	addr[0] = address>> 16;
	spi_flash_cmd(spim, SPI_FLASH_CMD_BE64, addr, sizeof(addr), SPI_FLASH_DMY_BE64, NULL, 0);
	while (spi_flash_busy(spim));
	return 0;
}

int spi_flash_erase_chip(bshal_spim_instance_t *spim){
	size_t block_size = 65536; (void)block_size;
	if (spi_flash_write_enable(spim)) return -1;
	spi_flash_cmd(spim, SPI_FLASH_CMD_CE, NULL, 0, SPI_FLASH_DMY_CE, NULL, 0);
	while (spi_flash_busy(spim));
	return 0;
}


void spi_flash_program(bshal_spim_instance_t *spim, uint32_t address, void* data, size_t size) {
	size_t page_size = 256;
	uint8_t addr[3] = {};
	size_t write_size = page_size - (address % page_size);
	if (write_size > size) write_size = size;
	int data_offset = 0;

	while (size) {
		const uint8_t cmd[] = {SPI_FLASH_CMD_PP};

		// Write Enable iIs reset after every write
		spi_flash_write_enable(spim);

		addr[2] = (address+data_offset);
		addr[1] = (address+data_offset)>> 8;
		addr[0] = (address+data_offset)>> 16;

		printf("Writing %3d bytes to address %02X%02X%02X\n",
				write_size, addr[0], addr[1], addr[2]);


		bshal_spim_transmit(spim, cmd, sizeof(cmd), true);
		bshal_spim_transmit(spim, addr, sizeof(addr), true);
		bshal_spim_transmit(spim,  data + data_offset, write_size, false);

		puts("Waiting while flash is busy");
		while (spi_flash_busy(spim));
		puts("Write finished");

		data_offset += write_size;
		size -= write_size;
		write_size = (size < page_size) ? size : page_size;
	}

	// Write Disable
	puts("Sending Write Disable Command");
	spi_flash_cmd(spim, SPI_FLASH_CMD_WRDI, NULL, 0, SPI_FLASH_DMY_WRDI, NULL, 0);
}

int spi_flash_read(bshal_spim_instance_t *spim, uint32_t address, void* data, size_t size) {
	uint8_t addr[3] = {};
	addr[2] = address;
	addr[1] = address>> 8;
	addr[0] = address>> 16;
	return spi_flash_cmd(spim, SPI_FLASH_CMD_READ, addr, sizeof(addr), SPI_FLASH_DMY_READ, data, size);
}

uint32_t spi_flash_get_id(bshal_spim_instance_t *spim) {
	uint32_t device_id = -1;
	uint8_t* bytes = (uint8_t*)&device_id;

	spi_flash_cmd(spim, SPI_FLASH_CMD_RDID, NULL, 0, SPI_FLASH_DMY_RDID, bytes, 3);

	spi_flash_cmd(spim, SPI_FLASH_CMD_RES, NULL, 0, SPI_FLASH_DMY_RES, bytes+3,1);
	return device_id;
}

uint64_t spi_flash_get_serial(bshal_spim_instance_t *spim) {
	uint64_t serial = -1;
	spi_flash_cmd(spim, SPI_FLASH_CMD_RUID, NULL, 0, SPI_FLASH_DMY_RUID, &serial,sizeof(serial));
	return serial;
}
