/*
 * lm75b.c
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#include <stdint.h>
#include <stdfix.h>

#include "lm75b.h"
#include "endian.h"

int lm75b_get_temperature_C_float(lm75b_t *lm75b, float *result) {
	uint8_t reg = LM75B_REG_TEMP;
	uint16_t value;

	int status;
	status = bshal_i2cm_send(lm75b->p_i2c, lm75b->addr, &reg, sizeof(reg),
			false);
	if (status)
		return status;
	status = bshal_i2cm_recv(lm75b->p_i2c, lm75b->addr, &value, sizeof(value),
			false);
	if (status)
		return status;

	// Incoming value is Big Endian
	value = be16toh(value);

	value >>= 5;
	*result = 0.125f * (float) value;
	return status;
}

int lm75b_get_temperature_C_accum(lm75b_t *lm75b, accum *result) {
	uint8_t reg = LM75B_REG_TEMP;
	uint16_t value;

	int status;
	status = bshal_i2cm_send(lm75b->p_i2c, lm75b->addr, &reg, sizeof(reg),
			false);
	if (status)
		return status;
	status = bshal_i2cm_recv(lm75b->p_i2c, lm75b->addr, &value, sizeof(value),
			false);
	if (status)
		return status;

	// Incoming value is Big Endian
	value = be16toh(value);

	value >>= 5;
	*result = 0.125k * (accum) value;
	return status;
}

