/*
 * sensor_protocol.h
 *
 *  Created on: 22 dec. 2023
 *      Author: andre
 */

#ifndef BSPROT_SENSOR_PROTOCOL_H_
#define BSPROT_SENSOR_PROTOCOL_H_

#include "protocol.h"

#define BSCP_CMD_SENSOR_ENVIOREMENTAL_VALUE	0x10


#include "bsfix.h"

typedef enum {
	bsprot_sensor_enviromental_temperature = 0,
	bsprot_sensor_enviromental_humidity = 1,
	bsprot_sensor_enviromental_illuminance = 2,
	bsprot_sensor_enviromental_airpressure = 3,

	bsprot_sensor_enviromental_co2 = 4,
	bsprot_sensor_enviromental_eco2 = 5,
	bsprot_sensor_enviromental_etvoc = 6,
	bsprot_sensor_enviromental_pm25 = 7,
} bsprot_sensor_enviromental_type_t;

typedef struct {
	union {
		int16_t temperature_centi_celcius;
		uint16_t humidify_relative_promille;
		uint16_t illuminance_lux;
		uint16_t air_pressure_deci_pascal;

		uint16_t co2_ppm;
		uint16_t eco2_ppm;
		uint16_t etvoc_ppb;
		uint16_t pm25_ugm3;
	};
} bsprot_sensor_enviromental_value_t;

typedef struct {
	uint8_t id;
	bsprot_sensor_enviromental_type_t type : 8;
	bsprot_sensor_enviromental_value_t value;
} bsprot_sensor_enviromental_data_t;

#endif /* BSPROT_SENSOR_PROTOCOL_H_ */
