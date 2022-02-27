/*
 * pcf8563.h
 *
 *  Created on: 29 aug. 2021
 *      Author: andre
 */

#ifndef PCF8563_H_
#define PCF8563_H_

#include <stdint.h>
#include <stdbool.h>
#include "bshal_i2cm.h"

#pragma pack(push,1)
#define PCF8563_I2C_ADDR	(0x51)

typedef union {
	struct {
		unsigned int unit :4;
		unsigned int tens :4;
	};
	unsigned int bcd :8;

} pcf8563_bcd_t;

typedef union {
	struct {
		unsigned int unit :4;
		unsigned int tens :3;
	};
	struct {
		unsigned int bcd :7;
		bool valid :1;
	};

} pcf8563_seconds_valid_t;

typedef union {
	struct {
		unsigned int unit :4;
		unsigned int tens :1;
	};
	struct {
		unsigned int bcd :5;
		unsigned int :2;
		unsigned int century :1;
	}
} pcf8563_months_century_t;

typedef struct {
	pcf8563_seconds_valid_t seconds;
	pcf8563_bcd_t minutes;
	pcf8563_bcd_t hours;
	pcf8563_bcd_t days;
	uint8_t weekdays;
	pcf8563_months_century_t months;
	pcf8563_bcd_t years;
} pcf8563_time_t;

typedef struct {
	bshal_i2cm_instance_t *p_i2c;
	uint8_t addr;
} pcf8563_t;

#pragma pack(pop)

#endif /* PCF8563_H_ */
