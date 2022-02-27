/*
 * sdmmc.h
 *
 *  Created on: 12 aug. 2021
 *      Author: andre
 */

#ifndef SDMMC_H_
#define SDMMC_H_

#include <stdint.h>
#include <assert.h>

#pragma pack(push,1)

typedef union {
	struct {
		unsigned int idle :1;
		unsigned int erase_reset :1;
		unsigned int error_cmd :1;
		unsigned int error_crc :1;
		unsigned int error_seq :1;
		unsigned int error_addr :1;
		unsigned int error_param :1;
		unsigned int raz :1;
		unsigned int not_busy :24;
	};
	uint8_t raw;
} sdmmc_card_status_t;


typedef struct {
	unsigned int : 16;
	unsigned int vhs : 4;
	unsigned int : 4;
	uint8_t check_pattern;
 } sdmmc_vhs_parameter;

// The specs list the bits in reverse, right?
// 179
typedef struct {
	unsigned int :15; // reserved
	unsigned int _2V7_2V8 :1;
	unsigned int _2V8_2V9 :1;
	unsigned int _2V9_3V0 :1;
	unsigned int _3V0_3V1 :1;
	unsigned int _3V1_3V2 :1;
	unsigned int _3V2_3V3 :1;
	unsigned int _3V3_3V4 :1;
	unsigned int _3V4_3V5 :1;
	unsigned int _3V5_3V6 :1;
	unsigned int S18A :1;
	unsigned int :4; // reserved
	unsigned int UHS_II :1;
	unsigned int CCS :1;
	unsigned int busy :1;
} sdmmc_ocr_t;
static_assert(sizeof(sdmmc_ocr_t) == 4 , "OCR should be 4 bytes (32bit)");

typedef struct {
	uint8_t MID :8;
	uint8_t OID[2];
	uint8_t PNM[5];
	uint8_t PRV :8;
	uint32_t PSN;
	unsigned int :4; // reserved ///
	unsigned int MDT :12;			 ///
} sdmmc_cid_t;
static_assert(sizeof(sdmmc_cid_t) == 15 , "CID should be 15 bytes ");

typedef struct {
	// We have to verify this structure
	// The order is probably wrong (MSB vs LSB)
	// Per byte... and if so... how to handle
	// fields with lengths not byte divisible ( 14 bit fields etc)

	unsigned int TAAC :8;

	unsigned int NSAC :8;

	unsigned int TRAN_SPEED :8;

	unsigned int CCC :12; //~~
	unsigned int READ_BL_LEN :4;

	unsigned int READ_BL_PARTIAL :1;
	unsigned int WRITE_BLK_MISALIGN :1;
	unsigned int READ_BLK_MISALIGN :1;
	unsigned int DSR_IMP :1;
	unsigned int C_SIZE :12; ///~~

	unsigned int VDD_R_CURR_MIN :3;
	unsigned int VDD_R_CURR_MAX :3;
	unsigned int VDD_W_CURR_MIN :3; //~~
	unsigned int VDD_W_CURR_MAX :3;
	unsigned int C_SIZE_MULT :3;
	unsigned int ERASE_BLK_EN :1;

	unsigned int SECTOR_SIZE :7;
	unsigned int WP_GRP_SIZE :7; //~
	unsigned int WP_GRP_ENABLE :1;
	unsigned int :2;
	unsigned int R2W_FACTOR :3;
	unsigned int WRITE_BL_LEN :4;  //~~
	unsigned int WRITE_BL_PARTIAL :1;
	unsigned int :5;

	// Might have to flip order???
	unsigned int FILE_FORMAT_GRP :1;
	unsigned int COPY :1;
	unsigned int PERM_WRITE_PROTECT :1;
	unsigned int TMP_WRITE_PROTECT :1;
	unsigned int FILE_FORMAT :2;
	unsigned int :2; // reserved
} sdmmc_csd1_t;

typedef struct {
	// TODO
} sdmmc_csd2_t;

// Do I have a known good parser for this structure?

typedef struct {
	unsigned int reserved :6;
	unsigned int CSD_STRUCTURE :2;
	union {
		sdmmc_csd1_t csd1;
		sdmmc_csd2_t csd2;
	}

} sdmmc_csd_t;
static_assert(sizeof(sdmmc_csd_t) == 15 , "CSD should be 15 bytes ");


typedef struct {

} sdmmc_acmd55_t;

// This encodes a request and 48 bit  reponses
// Reponse 1,3,6 , 7
// Note: we are in Most Significant Bit mode, right
// thus reverser the order
typedef union {
	struct {
		unsigned int command :6;
		unsigned int transmission_bit :1; // direction: 0 = card->host, 1 = host->card,
		unsigned int start_bit :1;	// set to 0
		union {
			uint32_t argument;
			sdmmc_card_status_t card_status;
			sdmmc_ocr_t ocr;
			sdmmc_vhs_parameter vhs;
		};
		unsigned int end_bit :1; // set to 1
		unsigned int crc7 :7;
	};
	uint8_t raw[6];
} ssdmmc_resq_t;

#define SDMMC_REQ_CMD_INIT {.start_bit = 0, 	.transmission_bit=1, .command = 0, .end_bit=1, .crc7= 0x4A, }
#define SDMMC_REQ_CMD_GETCID {.start_bit = 0, 	.transmission_bit=1, .command = 10, .end_bit=1, .crc7= -1, }

#define SDMMC_REQ_CMD8_VHS {.start_bit = 0, 	.transmission_bit=1, .command = 8, .vhs.vhs=1, .vhs.check_pattern=0xAA, .end_bit=1, .crc7= 0x43, }

#define SDMMC_REQ_CMD_ACMD {.start_bit = 0, 	.transmission_bit=1, .command = 55, .end_bit=1, .crc7= -1, }

// Note: we should give it some parameters, at least say SDHC capable
// Page 241 suggest only setting CSS, but page ... suggest a voltage must be set?
#define SDMMC_REQ_ACMD41 {.start_bit = 0, 	.transmission_bit=1, .command = 51,.ocr.CCS = 1, .ocr._3V3_3V4=0,  .end_bit=1, .crc7= -1, }
#define SDMMC_REQ_CMD1 {.start_bit = 0, 	.transmission_bit=1, .command = 1, .end_bit=1, .crc7= -1, }

typedef struct {
	uint8_t raw;
} sdmmc_spi_data_resp_token;
typedef union {
	struct {
		sdmmc_cid_t cid;
		unsigned int end_bit :1; // set to 1
		unsigned int crc7 :7;
		uint16_t crc16;
	};
	uint8_t raw[18];
} sdmmc_spi_resp_cid_t;

// Or wait do we get r1 in here?
typedef struct {
	unsigned int command :6;
	unsigned int start_bit :1;	// set to 0
	unsigned int transmission_bit :1;// direction: 0 = card->host, 1 = host->card,
	union {
		// These should be 15 bytes long
		sdmmc_cid_t cid;
		sdmmc_csd_t csd;
	};
	unsigned int end_bit :1; // set to 1
	unsigned int crc7 :7;
} sdmmc_resp2_t; // response 2

typedef struct {
	unsigned int card_is_locked :1;	// 0
	unsigned int lock_cmd_failed :1;	// 1
	unsigned int error :1;				// 2
	unsigned int error_cc :1;			// 3
	unsigned int error_ecc :1;			// 4
	unsigned int error_wp :1;			// 5
	unsigned int erase_param :1;
	unsigned int error_out_of_range :1;

	unsigned int :1;
	unsigned int :1;
	unsigned int :1;
	unsigned int :1;
	unsigned int :1;
	unsigned int :1;
	unsigned int :1;
	unsigned int :1;

} sdmmc_resp_r2_t;

#pragma pack(pop)

#endif /* SDMMC_H_ */
