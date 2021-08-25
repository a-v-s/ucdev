/*
 * css811.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#ifndef CCS811_H_
#define CCS811_H_

#include "bshal_i2cm.h"

typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t addr;
} ccs811_t;

#pragma pack(push,1)
typedef struct {
	unsigned int : 1;
	unsigned int int_tresh : 1;
	unsigned int int_datardy : 1;
	unsigned int drive_mode :3;
	unsigned int : 1;
} ccs811_meas_mode_t;

typedef struct {
	unsigned int error : 1;
	unsigned int : 2;
	unsigned int data_ready : 1;
	unsigned int app_valid : 1;
	unsigned int : 2;
	unsigned int fw_mode : 1;
} ccs811_status_t;

typedef struct {
	uint16_t eCO2;
	uint16_t TVOC;
	ccs811_status_t status;
	uint8_t error_id;
	uint16_t raw_data;
} ccs811_alg_result_data_t;
#pragma pack(pop)

#define CCS811_I2C_ADDR1 				0x5A
#define CCS811_I2C_ADDR2 				0x5B

#define CCS811_REG_STATUS 				0x00
#define CCS811_REG_MEAS_MODE 			0x01
#define CCS811_REG_ALG_RESULT_DATA		0x02
#define CCS811_REG_RAW_DATA				0x03
#define CCS811_REG_ENV_DATA				0x05
#define CCS811_REG_THRESHOLDS			0x10
#define CCS811_REG_BASELINE 			0x11
#define CCS811_REG_HW_ID				0x20
#define CCS811_REG_HW_Version			0x21
#define CCS811_REG_FW_Boot_Version		0x23
#define CCS811_REG_FW_App_Version		0x24
#define CCS811_REG_Internal_State		0xA0
#define CCS811_REG_ERROR_ID				0xE0
#define CSS811_REG_APP_ERASE			0xF1
#define CSS811_REG_APP_DATA				0xF2
#define CSS811_REG_APP_VERIFY			0xF3
#define CSS811_REG_APP_START			0xF4
#define CCS811_REG_SW_RESET				0xFF


#define CCS811_VAL_HW_ID				0x81

int ccs811_init(ccs811_t *css811) ;
int css811_measure(ccs811_t *css811, uint16_t *eCO2, uint16_t *TVOC );

#endif /* CCS811_H_ */
