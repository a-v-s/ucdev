/*
 * pcf8574.c
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#include "bshal_i2cm.h"

extern bshal_i2cm_instance_t * gp_i2c;

const char pcf8574_keymap[] = {	'1', '2' ,'3' ,'A',
								'4', '5' ,'6' ,'B',
								'7', '8' ,'9' ,'C',
								'*', '0' ,'#' ,'D', };

uint8_t read_keypad() {
	uint8_t buff[] = {0x0f, 0xf0};

	bshal_i2cm_send(gp_i2c, 0x20, buff + 0, 1, false);
	bshal_i2cm_recv(gp_i2c, 0x20, buff + 0, 1, false);

	bshal_i2cm_send(gp_i2c, 0x20, buff + 1, 1, false);
	bshal_i2cm_recv(gp_i2c, 0x20, buff + 1, 1, false);

	return ~ (buff[0]|buff[1]);
}

uint8_t get_key() {
	uint8_t scan_code = read_keypad();
	uint8_t r,c;
	r = scan_code & 0x0F;
	c = (scan_code & 0xF0) >> 4;

	// __builtin_popcount returns the number of 1-bits in x.
	if (__builtin_popcount(c) && __builtin_popcount(r)) {
		// If there are exactly 1 bit set in c and r
		// __builtin_ctz returns the number of trailing 0-bits in x
		int index = __builtin_ctz(r)<<2 | __builtin_ctz(c);
		index = 15 - index; // rotate
		return pcf8574_keymap[index];
	} else {
		return 0;
	}
}
