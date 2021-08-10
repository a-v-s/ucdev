/*
 * hcd1080.c
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#include "hcd1080.h"
#include "endian.h"

int hcd1080_get_temperature_C_float(hcd1080_t *hcd1080, float *result) {
	uint8_t cmd = HCD1080_REG_TEMPERATURE;
	int16_t value;

	int status;
	status = bshal_i2cm_send(hcd1080->p_i2c, hcd1080->addr, &cmd, sizeof(cmd),
			false);
	if (status)
		return status;
	for (int i = 0; i < 3; i++) {
		status = bshal_i2cm_recv(hcd1080->p_i2c, hcd1080->addr, &value,
				sizeof(value), false);
		if (!status)
			break;
		bshal_delay_ms(10);
	}
	if (status)
		return status;

	*result = -40.0f + 165.0f * (float) (be16toh(value)) / (float) (UINT16_MAX);
	return status;
}

int hcd1080_get_temperature_C_accum(hcd1080_t *hcd1080, accum *result) {
	uint8_t cmd = HCD1080_REG_TEMPERATURE;
	uint16_t value;

	int status;
	status = bshal_i2cm_send(hcd1080->p_i2c, hcd1080->addr, &cmd, sizeof(cmd),
			false);
	if (status)
		return status;
	for (int i = 0; i < 3; i++) {
		status = bshal_i2cm_recv(hcd1080->p_i2c, hcd1080->addr, &value,
				sizeof(value), false);
		if (!status)
			break;
		bshal_delay_ms(10);
	}
	if (status)
		return status;

	*result = -40.0 + 165.0 * (long accum)(be16toh(value)) / (long accum)(UINT16_MAX);

	return status;
}

int hcd1080_get_humidity_float(hcd1080_t *hcd1080, float *result) {
	uint8_t cmd = HCD1080_REG_HUMIDITY;
	int16_t value;

	int status;
	status = bshal_i2cm_send(hcd1080->p_i2c, hcd1080->addr, &cmd, sizeof(cmd),
			false);
	if (status)
		return status;
	for (int i = 0; i < 3; i++) {
		status = bshal_i2cm_recv(hcd1080->p_i2c, hcd1080->addr, &value,
				sizeof(value), false);
		if (!status)
			break;
		bshal_delay_ms(10);
	}
	if (status)
		return status;

	*result = (100.0f * (float) (be16toh(value)) / (float) (UINT16_MAX));
	return status;
}

int hcd1080_get_humidity_accum(hcd1080_t *hcd1080, accum *result) {
	uint8_t cmd = HCD1080_REG_HUMIDITY;
	uint16_t value;

	int status;
	status = bshal_i2cm_send(hcd1080->p_i2c, hcd1080->addr, &cmd, sizeof(cmd),
			false);
	if (status)
		return status;
	for (int i = 0; i < 3; i++) {
		status = bshal_i2cm_recv(hcd1080->p_i2c, hcd1080->addr, &value,
				sizeof(value), false);
		if (!status)
			break;
		bshal_delay_ms(10);
	}
	if (status)
		return status;

	*result = (100.0lk * (long accum)(be16toh(value)) / (long accum)(UINT16_MAX));

	return status;
}

int hcd1080_identify(hcd1080_t *hcd1080, bool *is_hcd1080) {
	uint8_t cmd = HCD1080_REG_MANUFACTURER_ID;
	uint16_t manuf, device;
	int status;
	*is_hcd1080 = false;

	status = bshal_i2cm_send(hcd1080->p_i2c, hcd1080->addr, &cmd, sizeof(cmd),
			false);
	if (status)
		return status;
	bshal_delay_ms(1);
	status = bshal_i2cm_recv(hcd1080->p_i2c, hcd1080->addr, &manuf,
			sizeof(manuf), false);
	if (status)
		return status;

	cmd = HCD1080_REG_DEVICE_IO;
	status = bshal_i2cm_send(hcd1080->p_i2c, hcd1080->addr, &cmd, sizeof(cmd),
			false);
	if (status)
		return status;
	status = bshal_i2cm_recv(hcd1080->p_i2c, hcd1080->addr, &device,
			sizeof(device), false);
	if (status)
		return status;

	*is_hcd1080 = be16toh(device) == HCD1080_VAL_DEVICE_IO
			&& be16toh(manuf) == HCD1080_VAL_MANUFACTURER_ID;
	return status;
}
