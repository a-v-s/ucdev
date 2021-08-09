/*
 * css811.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#ifndef CCS811_H_
#define CCS811_H_

#define CCS811_REG_STATUS 				0x00
#define CCS811_REG_MEAS_MODE 			0x01
#define CCS811_REG_ALG_RESULT_DATA		0x02
#define CCS811_REG_RAW_DATA				0x03
#define CCS811_REG_ENV_DATA				0x05
#define CCS811_REG_THRESHOLDS			0x10
#define CCS811_REG_BASELINE 			0x11
#define CCS811_REG_HW_ID				0x20
#define CCS811_REG_HW Version			0x21
#define CCS811_REG_FW_Boot_Version		0x23
#define CCS811_REG_FW_App_Version		0x24
#define CCS811_REG_Internal_State		0xA0
#define CCS811_REG_ERROR_ID				0xE0
#define CCS811_REG_SW_RESET				0xFF


#endif /* CCS811_H_ */
