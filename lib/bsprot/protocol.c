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
#include <stdio.h>

static command_handler_f command_handlers[0x100];

uint32_t protocol_parse(uint8_t *data, size_t size,
		protocol_transport_t transport, void* param) {
	int offset = 0;
	bscp_protocol_header_t *header = (bscp_protocol_header_t*) (data);
	while (header->size && (header->size + offset) <= size) {
		if (command_handlers[header->cmd]) {
			uint8_t command_data[header->size];
			memcpy(command_data, header, header->size);
			command_handlers[header->cmd]((bscp_protocol_packet_t *)(command_data), transport, param);
			printf("Handled   command %02X\n", header->cmd);
		} else {
			printf("Unhandled command %02X\n", header->cmd);
		}
		offset += header->size;
		header = (bscp_protocol_header_t*) (data+offset);
	}
	return 0;
}

uint32_t protocol_register_command(command_handler_f handler, uint8_t command) {
	command_handlers[command] = handler;
	return 0;
}

uint32_t protocol_packet_merge(uint8_t* buffer, size_t buffer_size, bscp_protocol_packet_t * packet) {
	int pos = 0;
	while (buffer[pos]) {
		pos += buffer[pos];
		if (( pos + packet->head.size)  > buffer_size )
			return -1;
	}
	memcpy(buffer+pos, packet, packet->head.size);
	int end = pos+packet->head.size;
	if (end < buffer_size) buffer[end]=0;
	return 0;
}


size_t protocol_merged_packet_size(void* buffer_, size_t buffer_size) {
	int pos = 0;;
	uint8_t* buffer = (uint8_t*)buffer_;
	while (buffer[pos]) {
		pos += buffer[pos];
		if (pos >- buffer_size)
			break;
	}
	return pos;
}
