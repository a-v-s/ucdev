/*
 * sht3x.c
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#include "sht3x.h"
#include "endian.h"


int sht3x_get_temperature_C_float(sht3x_t* sht3x, float * result){
	uint8_t cmd[2] = {0x2c, 0x10};
	sht3x_value_t value;

	int status;
	status = bshal_i2cm_send(sht3x->p_i2c, sht3x->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(sht3x->p_i2c, sht3x->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = -45.0f + 175.0f * (float)(be16toh(value.temperature)) / (float)(UINT16_MAX - 1);
	return status;
}

#ifdef __ACCUM_FBIT__
int sht3x_get_temperature_C_accum(sht3x_t* sht3x, accum * result){
	uint8_t cmd[2] = {0x2c, 0x10};
	sht3x_value_t value;

	int status;
	status = bshal_i2cm_send(sht3x->p_i2c, sht3x->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(sht3x->p_i2c, sht3x->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = -45.0lk + 175.0lk * (long accum)(be16toh(value.temperature)) / (long accum)(UINT16_MAX - 1);

	return status;
}
#endif

int sht3x_get_humidity_float(sht3x_t* sht3x, float * result){
	uint8_t cmd[2] = {0x2c, 0x10};
	sht3x_value_t value;

	int status;
	status = bshal_i2cm_send(sht3x->p_i2c, sht3x->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(sht3x->p_i2c, sht3x->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = 100.0f * (float)(be16toh(value.humidity)) / (float)(UINT16_MAX - 1);
	return status;
}

#ifdef __ACCUM_FBIT__
int sht3x_get_humidity_accum(sht3x_t* sht3x, accum * result){
	uint8_t cmd[2] = {0x2c, 0x10};
	sht3x_value_t value;

	int status;
	status = bshal_i2cm_send(sht3x->p_i2c, sht3x->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(sht3x->p_i2c, sht3x->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = 100.0lk * (long accum)(be16toh(value.humidity)) / (long accum)(UINT16_MAX - 1);

	return status;
}
#endif
