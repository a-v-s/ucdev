/*
 * scd4x.h
 *
 *  Created on: 4 dec. 2022
 *      Author: andre
 */

#ifndef SCD4X_H_
#define SCD4X_H_

#include "endian.h"
#include "bshal_i2cm.h"

#define SCD4X_I2C_ADDR 0x62

typedef struct {
	bshal_i2cm_instance_t *p_i2c;
	uint8_t addr;
} scd4x_t;

#pragma pack (push,1)
typedef struct {
	int16_t co2;
	uint8_t co2_crc;
	int16_t temperature;
	uint8_t temp_crc;
	int16_t humidity;
	uint8_t humi_crc;
} scd4x_result_t;
#pragma pack (pop)

#define SCD4X_CMD_START_PERIODIC_MEASUREMENT	htobe16(0x21B1)
#define SCD4X_CMD_READ_MEASUREMENT 				htobe16(0xEC05)
#define SCD4X_CMD_STOP_PERIODIC_MEASUREMENT 	htobe16(0x3F86)

#define SCD4X_CMD_SET_TEMPERATURE_OFFSET 		htobe16(0x241D)
#define SCD4X_CMD_GET_TEMPERATURE_OFFSET 		htobe16(0x2318)
#define SCD4X_CMD_SET_SENSOR_ALTITUDE 			htobe16(0x2427)
#define SCD4X_CMD_GET_SENSOR_ALTITUDE 			htobe16(0x2322)
#define SCD4X_CMD_SET_AMBIENT_PRESSURE 			htobe16(0xE000)

#define SCD4X_CMD_PERFORM_FORCED_RECALIBRATION 	htobe16(0x362F)
#define SCD4X_CMD_SET_AUTOMATIC_SELF_CALIBRATION_ENABLED htobe16(0x2416)
#define SCD4X_CMD_GET_AUTOMATIC_SELF_CALIBRATION_ENABLED htobe16(0x2313)

#define SCD4X_CMD_START_LOW_POWER_PERIODIC_MEASUREMENT htobe16(0x21AC)
#define SCD4X_CMD_GET_DATA_READY_STATUS 		htobe16(0xE4B8)

#define SCD4X_CMD_PERSIST_SETTINGS 				htobe16(0x3615)
#define SCD4X_CMD_GET_SERIAL_NUMBER 			htobe16(0x3682)
#define SCD4X_CMD_PERFORM_SELF_TEST 			htobe16(0x3639)
#define SCD4X_CMD_PERFORM_FACTORY_RESET 		htobe16(0x3632)
#define SCD4X_CMD_REINIT 						htobe16(0x3646)

#define SCD4X_CMD_MEASURE_SINGLE_SHOT 			htobe16(0x219D)
#define SCD4X_CMD_MEASURE_SINGLE_SHOT_RHT_ONLY 	htobe16(0x2196)
#define SCD4X_CMD_POWER_DOWN 					htobe16(0x36E0)
#define SCD4X_CMD_WAKE_UP 						htobe16(0x36F6)

int scd4x_get_result_float(scd4x_t *scd4x, uint16_t *co2_ppm, float *temp_C,
		uint16_t *humidity_percent);
int scd4x_init(scd4x_t *scd4x);

#endif /* SCD4X_H_ */
