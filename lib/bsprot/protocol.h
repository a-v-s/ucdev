/*

 File:       protocol.h
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

#ifndef ANY_INC_PROTOCOL_H_
#define ANY_INC_PROTOCOL_H_


#include <stdint.h>
#include <stdlib.h> // size_t


// Basic Commands
#define ITPH_CMD_NOP      0x00
#define ITPH_CMD_PING     0x01
#define ITPH_CMD_INFO     0x02

// Basic Subcommands
#define ITPH_SUB_QGET 0x10 // reQuest GET
#define ITPH_SUB_QSET 0x11 // reQuest SET
#define ITPH_SUB_SDAT 0x20 // reSponse DATa
#define ITPH_SUB_SSTA 0x21 // reSponse STAtus


typedef struct {
    uint8_t size;
    uint8_t  cmd;
    uint8_t  sub;
    uint8_t  res;
} protocol_header_t;

typedef struct {
    uint8_t transport;
    uint8_t target;
    uint8_t data[];
} itph_protocol_forward_t;

typedef struct {
    protocol_header_t head;
    uint8_t data[];
} itph_protocol_packet_t;


typedef enum {
    PROTOCOL_TRANSPORT_UNKNOWN = 0x00,

    PROTOCOL_TRANSPORT_USB = 0x10,

    PROTOCOL_TRANSPORT_SPI = 0x20,
    PROTOCOL_TRANSPORT_I2C = 0x21,
    PROTOCOL_TRANSPORT_UART = 0x22,

    PROTOCOL_TRANSPORT_ESB = 0x40,
    PROTOCOL_TRANSPORT_RF = 0x41,
	PROTOCOL_TRANSPORT_BLE = 0x42,
} protocol_transport_t;

typedef enum {
    ITPH_HANDLER_STATUS_OK      = 0,
    ITPH_HANDLER_STATUS_OK_FW   = 1,
    ITPH_HANDLER_STATUS_SKIPPED = 2,
    ITPH_HANDLER_STATUS_BADSIZE = 3,
    ITPH_HANDLER_STATUS_BADCMD  = 4,
    ITPH_HANDLER_STATUS_BADSUB  = 5,
    ITPH_HANDLER_STATUS_BADDATA = 6,
    ITPH_HANDLER_STATUS_ERROR  = 0xF0,
} itph_handler_status_t ;

typedef itph_handler_status_t (*command_handler_f)(itph_protocol_packet_t *data, protocol_transport_t transport, uint32_t param);

uint32_t protocol_parse(uint8_t *data, size_t size, protocol_transport_t transport, uint32_t param);
uint32_t protocol_register_command(command_handler_f handler, uint8_t command);

uint32_t protocol_packet_merge(uint8_t* buffer, size_t buffer_size, itph_protocol_packet_t * packet);
size_t protocol_merged_packet_size(void* buffer, size_t buffer_size);

#endif /* ANY_INC_PROTOCOL_H_ */
