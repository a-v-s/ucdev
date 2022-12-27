#include "ir.h"

#include <stdint.h>

typedef enum {
	ir_idle, ir_presync, ir_sync,
} ir_state_t;

typedef struct {
	uint32_t raw;
	uint32_t bitcount;
	uint32_t lo_us;
	uint32_t hi_us;
} ir_data_t;

static volatile ir_data_t m_ir_data = { 0 };
static ir_state_t ir_state = ir_idle;

#define SYNC_LO 9000
//#define SYNC_HI 4500
// Getting times as low as 4469
// So we need more margin here
#define SYNC_HI 4300

#define REPEAT_HI 2000

#define BIT_LO 500
#define BIT0_HI 500
#define BIT1_HI 1500

#if !__has_builtin(__builtin_bitreverse8)
uint8_t __builtin_bitreverse8(uint8_t byte) {
	uint8_t result = 0;
	if (byte & 0b00000001) result |= 0b10000000;
	if (byte & 0b00000010) result |= 0b01000000;
	if (byte & 0b00000100) result |= 0b00100000;
	if (byte & 0b00001000) result |= 0b00010000;
	if (byte & 0b00010000) result |= 0b00001000;
	if (byte & 0b00100000) result |= 0b00000100;
	if (byte & 0b01000000) result |= 0b00000010;
	if (byte & 0b10000000) result |= 0b00000001;
	return result;
}

#endif



void ir_handler(bool pinstate) {

	if (!pinstate) {
		m_ir_data.hi_us = get_time_us();
		uint32_t hi_time = m_ir_data.hi_us - m_ir_data.lo_us;
		//printf("HI %6d\n", hi_time);

		switch (ir_state) {
		// TODO margins
		case ir_presync: {
			if (hi_time > SYNC_HI) {
				ir_state = ir_sync;
				m_ir_data.raw = 0;
				m_ir_data.bitcount = 0;
				//printf("STATE: SYNC\n");
			} else
			if (hi_time > REPEAT_HI){
				//printf("                REPEAT\n");
				ir_state = ir_idle;
			} else {
				printf("BAD SIGNAL\n");
				ir_state = ir_idle;
			}
		}
			break;
		case ir_sync: {
			bool bit;
			if (hi_time > BIT1_HI)
				bit = true;
			else
				bit = false;


			m_ir_data.raw <<= 1;
			m_ir_data.raw |= bit;
			m_ir_data.bitcount++;
			if (m_ir_data.bitcount == 32) {
				//printf("                %08X\n", m_ir_data.raw);
				printf("                %02X\n", __builtin_bitreverse8 (m_ir_data.raw&0xFF) );
				ir_state = ir_idle;
			}

		}
			break;
		}
	} else {
		m_ir_data.lo_us = get_time_us();
		uint32_t lo_time = m_ir_data.lo_us - m_ir_data.hi_us;
		//printf("LO %6d\n", lo_time);

		switch (ir_state) {
		case ir_idle: {
			// TODO margins
			if (lo_time > SYNC_LO) {
				ir_state = ir_presync;
				//printf("STATE: PRESYNC\n");
				break;
			}
		}
		}

	}
}
