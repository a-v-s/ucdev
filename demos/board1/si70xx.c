/*
 * si70xx.c
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#include "si70xx.h"
#include "endian.h"


int si70xx_get_temperature_C_float(si70xx_t* si70xx, float * result){
	uint8_t cmd[] = {0xe3};
	int16_t value;

	int status;
	status = bshal_i2cm_send(si70xx->p_i2c, si70xx->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(si70xx->p_i2c, si70xx->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = -46.85f + 175.72f * (float)(be16toh(value)) / (float)(UINT16_MAX );
	return status;
}


int si70xx_get_temperature_C_accum(si70xx_t* si70xx, accum * result){
	uint8_t cmd[] = {0xf3};
	int16_t value;

	int status;
	status = bshal_i2cm_send(si70xx->p_i2c, si70xx->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(si70xx->p_i2c, si70xx->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = -46.85lk + 175.72lk * (long accum)(be16toh(value)) / (long accum)(UINT16_MAX);

	return status;
}

int si70xx_get_humidity_float(si70xx_t* si70xx, float * result){
	uint8_t cmd[] = {0xe5};
	int16_t value;

	int status;
	status = bshal_i2cm_send(si70xx->p_i2c, si70xx->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(si70xx->p_i2c, si70xx->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = (125.0f * (float)(be16toh(value)) / (float)(UINT16_MAX)) - 6.0f;
	return status;
}

int si70xx_get_humidity_accum(si70xx_t* si70xx, accum * result){
	uint8_t cmd[] = {0xe5};
	int16_t value;

	int status;
	status = bshal_i2cm_send(si70xx->p_i2c, si70xx->addr, &cmd, sizeof(cmd), false);
	if (status) return status;
	status = bshal_i2cm_recv(si70xx->p_i2c, si70xx->addr, &value, sizeof(value), false);
	if (status) return status;

	*result = (125.0lk * (long accum)(be16toh(value)) / (long accum)(UINT16_MAX)) - 6.0lk;

	return status;
}

int si70xx_identify(si70xx_t *hcd1080, bool *is_si70xx) {
	uint8_t cmd[] = { 0xFC, 0xc9 };
	uint8_t dev_id;
	int status;
	*is_si70xx = false;

	status = bshal_i2cm_send(hcd1080->p_i2c, hcd1080->addr, &cmd, sizeof(cmd),
			false);
	if (status)
		return status;
	status = bshal_i2cm_recv(hcd1080->p_i2c, hcd1080->addr, &dev_id,
			sizeof(dev_id), false);
	if (status)
		return status;

	*is_si70xx = dev_id == SI7013_DEV_ID || dev_id == SI7020_DEV_ID
			|| dev_id == SI7021_DEV_ID;
	return status;
}
