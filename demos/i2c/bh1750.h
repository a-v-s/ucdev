/*
 * bh1750.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#ifndef BH1750_H_
#define BH1750_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdfix.h>

#include "bshal_i2cm.h"


typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t addr;
} bh1750_t;

#define BH1750_INSTR_POWER_DOWN	0b00000000
#define BH1750_INSTR_POWER_ON	0b00000001
#define BH1750_INSTR_RESET		0b00000111

#define BH1750_INSTR_CONT_H		0b00010000
#define BH1750_INSTR_CONT_H2	0b00010001
#define BH1750_INSTR_CONT_L		0b00010011

#define BH1750_INSTR_ONE_H		0b00100000
#define BH1750_INSTR_ONE_H2		0b00100001
#define BH1750_INSTR_ONE_L		0b00100011

int bh1750_measure_ambient_light(bh1750_t * bh1750, int *lux);

#endif /* BH1750_H_ */
