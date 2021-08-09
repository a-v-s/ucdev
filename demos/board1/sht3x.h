/*
 * sht3x.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */


#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdfix.h>

#include "bshal_i2cm.h"

typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t addr;
} sht3x_t;


#pragma pack (push,1)
typedef struct {
	int16_t temperature;
	uint8_t temp_crc;
	int16_t humidity;
	uint8_t humi_crc;
} sht3x_value_t;
#pragma pack (pop)


int sht3x_get_temperature_C_float(sht3x_t* sht3x, float * result);
int sht3x_get_temperature_C_accum(sht3x_t* sht3x, accum * result);

int sht3x_get_humidity_float(sht3x_t* sht3x, float * result);
int sht3x_get_humidity_accum(sht3x_t* sht3x, accum * result);

accum sht3x_get_temperature_C_accum_ret(sht3x_t* sht3x );
