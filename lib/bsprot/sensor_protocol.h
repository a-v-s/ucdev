/*
 * sensor_protocol.h
 *
 *  Created on: 22 dec. 2023
 *      Author: andre
 */

#ifndef BSPROT_SENSOR_PROTOCOL_H_
#define BSPROT_SENSOR_PROTOCOL_H_

#include "protocol.h"

#define BSCP_CMD_SENSOR0_VALUE	0x10
#define BSCP_CMD_SENSOR1_VALUE	0x11
#define BSCP_CMD_SENSOR2_VALUE	0x12
#define BSCP_CMD_SENSOR3_VALUE	0x13
#define BSCP_CMD_SENSOR4_VALUE	0x14


//#include "bsfix.h"

typedef enum {
	bsprot_sensor_temperature = 0,
	bsprot_sensor_humidity = 1,
	bsprot_sensor_illuminance = 2,
	bsprot_sensor_airpressure = 3,

	bsprot_sensor_co2 = 4,
	bsprot_sensor_eco2 = 5,
	bsprot_sensor_etvoc = 6,

} bsprot_sensor_value0_type_t;

typedef enum {
	bsprot_sensor_pm005 = 0,
	bsprot_sensor_pm010 = 1,
	bsprot_sensor_pm025 = 2,
	bsprot_sensor_pm040 = 3,
	bsprot_sensor_pm100 = 4,
} bsprot_sensor_value1_type_t;

typedef enum {
	bespor_sensor_voltage = 0,
	bespor_sensor_current = 1,
	bespor_sensor_power = 2,
} bsprot_sensor_value2_type_t;



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
	bsprot_sensor_value0_type_t type : 8;
	bsprot_sensor_enviromental_value_t value;
} bsprot_sensor_enviromental_data_t;

#endif /* BSPROT_SENSOR_PROTOCOL_H_ */
