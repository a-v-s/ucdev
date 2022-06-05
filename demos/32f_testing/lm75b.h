/*
 * lm75b.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#ifndef LM75B_H_
#define LM75B_H_

#include "bshal_i2cm.h"

#define LM75B_REG_TEMP	(0x00)
#define LM75B_REG_CONF	(0x01)
#define LM75B_REG_THYST	(0x02)
#define LM75B_REG_TOS	(0x03)


typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t addr;
} lm75b_t;

int lm75b_get_temperature_C_float(lm75b_t* lm75b, float*);
#ifdef __ACCUM_FBIT__
int lm75b_get_temperature_C_accum(lm75b_t* lm75b, accum*);
#endif
#endif /* LM75B_H_ */
