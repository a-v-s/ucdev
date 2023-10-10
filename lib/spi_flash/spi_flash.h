/*

 File: 		spi_flash.h
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

#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include <stdint.h>

#pragma pack (push,1)
typedef struct {
	uint8_t signature[4];
	struct {
		uint8_t minor;
		uint8_t major;
	} revision;
	uint8_t nph;
	uint8_t ap;
} sfdp_header_t;

typedef struct {
	uint8_t lsb;
	struct {
		uint8_t minor;
		uint8_t major;
	} revision;
	uint8_t length; // in double words, their word size is 16, thus 32 bit
	union {
		unsigned int ptp_be :24; // parameter table pointer, 24 bit big endian
		uint8_t ptp_as_uint8[3];
	};
	uint8_t msb;
} sfdp_parameter_header_t;

typedef union {
	uint32_t words[23];
	struct {
		union {
			struct {
				unsigned int block_sector_erase_sizes :2;
				unsigned int write_granularity :1;
				unsigned int volatile_status_register_block_protest_bits :1;
			};
			uint32_t word1;
		};
		union {
			uint32_t flash_memory_density_le;
		};
	};

} basic_flash_parameters_t;

typedef struct {
	uint8_t manufacturer_id;
	uint8_t memory_type;
	uint8_t memory_density;
} spi_flash_rdid_t;

typedef struct {
	uint8_t electronic_id
} spi_flash_res_t;

typedef struct {
	uint8_t manufacturer_id;
	uint8_t device_id;
} spi_flash_rems_t;

typedef struct {
	unsigned int busy : 1;
	unsigned int wel : 1;
	unsigned int bp : 3;
	unsigned int tb : 1;
	unsigned int sec : 1;
	unsigned int srp0 : 1;
} spi_flash_sr1_t;

typedef struct {
	unsigned int srp1 : 1;
	unsigned int qe : 1;
	unsigned int lb : 4;
	unsigned int cmp : 1;
	unsigned int sus : 1;
} spi_flash_sr2_t;

typedef struct {
	unsigned int lc : 4;
	unsigned int hfm : 1;
	unsigned int srv : 2;
	unsigned int hrsw : 1;
} spi_flash_sr3_t;


//---------------------------------------------------------------------------
// SPI COMMANDS
//---------------------------------------------------------------------------

 // Read
#define SPI_FLASH_CMD_READ	0x03
#define SPI_FLASH_CMD_FREAD	0x0B

// Program and Erase
#define SPI_FLASH_CMD_PE	0x81
#define SPI_FLASH_CMD_SE	0x20
#define SPI_FLASH_CMD_BE32	0x52
#define SPI_FLASH_CMD_BE64	0xD8
#define SPI_FLASH_CMD_CE	0x60
#define SPI_FLASH_CMD_CE_ALT  0xC7
#define SPI_FLASH_CMD_PP	0x02
#define SPI_FLASH_CMD_2PP	0xA2
#define SPI_FLASH_CMD_PES	0x75
#define SPI_FLASH_CMD_PES_ALT	0xB0
#define SPI_FLASH_CMD_PER	0x7A
#define SPI_FLASH_CMD_PER_ALT	0x30

// Protection
#define SPI_FLASH_CMD_WREN	0x06
#define SPI_FLASH_CMD_WRDI	0x04
#define SPI_FLASH_CMD_VWREN	0x50

// Security
#define SPI_FLASH_CMD_ERSCUR	0x44
#define SPI_FLASH_CMD_PRSCUR	0x42
#define SPI_FLASH_CMD_RDSCUR	0x48

// Status Register
#define SPI_FLASH_CMD_RDSR1	0x05
#define SPI_FLASH_CMD_RDSR2	0x35
#define SPI_FLASH_CMD_RDSR3	0x15
#define SPI_FLASH_CMD_ASI	0x25
#define SPI_FLASH_CMD_WRSR1	0x01
#define SPI_FLASH_CMD_WRSR2	0x31
#define SPI_FLASH_CMD_WRSR3	0x11

// Other Commands
#define SPI_FLASH_CMD_RSTEN	0x66
#define SPI_FLASH_CMD_RST	0x99
#define SPI_FLASH_CMD_RDID	0x9F
#define SPI_FLASH_CMD_REMS	0x90
#define SPI_FLASH_CMD_DP	0xB9
#define SPI_FLASH_CMD_RDP	0xAB
#define SPI_FLASH_CMD_RES	0xAB
#define SPI_FLASH_CMD_RDSFDP	0x5A
#define SPI_FLASH_CMD_RRE	0xFF
#define SPI_FLASH_CMD_RUID	0x4B
#define SPI_FLASH_CMD_NOP	0x00

//---------------------------------------------------------------------------
// DSPI, QSPI commands
//---------------------------------------------------------------------------

// Clock address in 1 wire mode, data in 2,4 wire mode
#define SPI_FLASH_CMD_DFREAD	0x3B
#define SPI_FLASH_CMD_DREMS	0x92
#define SPI_FLASH_CMD_QFREAD	0x6B
#define SPI_FLASH_CMD_QREMS	0x94

// Clock address in 2, 4 wire mode, , data in 2,4 wire mode
#define SPI_FLASH_CMD_2FREAD	0xBB
#define SPI_FLASH_CMD_4FREAD	0xEB


//---------------------------------------------------------------------------
// Number of Dummy bytes for each command
//---------------------------------------------------------------------------

// Read
#define SPI_FLASH_DMY_READ	0
#define SPI_FLASH_DMY_FREAD	1

// Program and Erase
#define SPI_FLASH_DMY_PE	0
#define SPI_FLASH_DMY_SE	0
#define SPI_FLASH_DMY_BE32	0
#define SPI_FLASH_DMY_BE64	0
#define SPI_FLASH_DMY_CE	0
#define SPI_FLASH_DMY_CE_ALT  0
#define SPI_FLASH_DMY_PP	0
#define SPI_FLASH_DMY_2PP	0
#define SPI_FLASH_DMY_PES	0
#define SPI_FLASH_DMY_PES_ALT	0
#define SPI_FLASH_DMY_PER	0
#define SPI_FLASH_DMY_PER_ALT	0

// Protection
#define SPI_FLASH_DMY_WREN	0
#define SPI_FLASH_DMY_WRDI	0
#define SPI_FLASH_DMY_VWREN	0

// Security
#define SPI_FLASH_DMY_ERSCUR	0
#define SPI_FLASH_DMY_PRSCUR	0
#define SPI_FLASH_DMY_RDSCUR	1

// Status Register
#define SPI_FLASH_DMY_RDSR1	0
#define SPI_FLASH_DMY_RDSR2	0
#define SPI_FLASH_DMY_RDSR3	0
#define SPI_FLASH_DMY_ASI	1
#define SPI_FLASH_DMY_WRSR1	0
#define SPI_FLASH_DMY_WRSR2	0
#define SPI_FLASH_DMY_WRSR3	0

// Other Commands
#define SPI_FLASH_DMY_RSTEN	0
#define SPI_FLASH_DMY_RST	0
#define SPI_FLASH_DMY_RDID	0
#define SPI_FLASH_DMY_REMS	3
#define SPI_FLASH_DMY_DP	0
#define SPI_FLASH_DMY_RDP	3
#define SPI_FLASH_DMY_RES	3
#define SPI_FLASH_DMY_RDSFDP	1
#define SPI_FLASH_DMY_RRE	?
#define SPI_FLASH_DMY_RUID	4
#define SPI_FLASH_DMY_NOP	0



#pragma pack (pop)



uint64_t spi_flash_get_serial(bshal_spim_instance_t *spim);
#endif // __SPI_FLASH_H
