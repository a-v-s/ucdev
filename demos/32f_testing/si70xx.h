/*
 * si70xx.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#ifndef si70xx_H_
#define si70xx_H_


#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdfix.h>

#include "bshal_i2cm.h"

typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t addr;
} si70xx_t;

#define SI7013_DEV_ID 0x0D
#define SI7020_DEV_ID 0x14
#define SI7021_DEV_ID 0x15

int si70xx_get_temperature_C_float(si70xx_t* si70xx, float * result);
int si70xx_get_humidity_float(si70xx_t* si70xx, float * result);

#ifdef __ACCUM_FBIT__
int si70xx_get_temperature_C_accum(si70xx_t* si70xx, accum * result);
int si70xx_get_humidity_accum(si70xx_t* si70xx, accum * result);
#endif


#endif /* si70xx_H_ */
