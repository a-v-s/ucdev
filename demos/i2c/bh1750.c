/*
 * bh1750.c
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */


#include "bh1750.h"
#include "endian.h"

int bh1750_measure_ambient_light(bh1750_t * bh1750, int *lux) {
	uint8_t cmd[] = {BH1750_INSTR_ONE_H};
	uint16_t value;

	int result;
	result = bshal_i2cm_send(bh1750->p_i2c, bh1750->addr, &cmd, sizeof(cmd), false);
	if (result) return result;
	result = bshal_i2cm_recv(bh1750->p_i2c, bh1750->addr, &value, sizeof(value), false);
	if (result) return result;

	//long accum value_in_lux = be16toh(value) / 1.2k;
	int value_in_lux = ( 10 * (int) be16toh(value) ) / 12;
	*lux = value_in_lux;
	return result;
}
