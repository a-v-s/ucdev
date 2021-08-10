/*
 * hcd1080.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#ifndef HCD1080_H_
#define HCD1080_H_


#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdfix.h>

#include "bshal_i2cm.h"

typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t addr;
} hcd1080_t;

#define HCD1080_REG_TEMPERATURE		(0x00)
#define HCD1080_REG_HUMIDITY		(0x01)
#define HCD1080_REG_CONFIGURATION	(0x02)
#define HCD1080_REG_SERIAL3			(0xFB)
#define HCD1080_REG_SERIAL2			(0xFC)
#define HCD1080_REG_SERIAL1			(0xFD)
#define HCD1080_REG_MANUFACTURER_ID	(0xFE)
#define HCD1080_REG_DEVICE_IO		(0xFF)

#define HCD1080_VAL_MANUFACTURER_ID	(0x5449)
#define HCD1080_VAL_DEVICE_IO		(0x1050)

int hcd1080_get_temperature_C_float(hcd1080_t* hcd1080, float * result);
int hcd1080_get_temperature_C_accum(hcd1080_t* hcd1080, accum * result);

int hcd1080_get_humidity_float(hcd1080_t* hcd1080, float * result);
int hcd1080_get_humidity_accum(hcd1080_t* hcd1080, accum * result);
#endif /* HCD1080_H_ */
