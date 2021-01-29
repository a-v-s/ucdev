/*

 File:       protocol.c
 Author:     André van Schoubroeck <andre@blaatschaap.be>
 License:    MIT


 MIT License

 Copyright (c) 2018, 2020 André van Schoubroeck

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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

static command_handler_f command_handlers[0x100];

uint32_t protocol_parse(uint8_t *data, size_t size,
		protocol_transport_t transport, uint32_t param) {
	int offset = 0;
	protocol_header_t *header = (protocol_header_t*) data;
	while (header->size && (header->size + offset) <= size) {
		if (command_handlers[header->cmd]) {
			uint8_t command_data[header->size];
			memcpy(command_data, header, header->size);
			command_handlers[header->cmd](command_data, transport, param);
		}
		offset += header->size;
	}
	return 0;
}

uint32_t protocol_register_command(command_handler_f handler, uint8_t command) {
	command_handlers[command] = handler;
	return 0;
}

uint32_t protocol_merge_packets(uint16_t packet_size, uint8_t *data_in,
		uint8_t count_in, uint8_t *data_out) {
	uint16_t offset = 0;
	uint8_t count = 0;
	while (count < count_in
			&& offset
					+ ((protocol_header_t*) (data_in + (count * packet_size)))->size
					<= packet_size) {
		memcpy(data_out + offset, data_in + (count * packet_size),
				((protocol_header_t*) (data_in + (count * packet_size)))->size);
		offset +=
				((protocol_header_t*) (data_in + (count * packet_size)))->size;
		count++;
	}
	return count;
}
