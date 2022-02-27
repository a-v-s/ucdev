#ifndef __BMP_280_H__
#define __BMP_280_H__
#include "bshal_i2cm.h"

#include <stdint.h>

#pragma pack (push,1)

typedef struct {
	uint16_t t1;
	int16_t	t2;
	int16_t t3;
	uint16_t p1;
	int16_t p2;
	int16_t p3;
	int16_t p4;
	int16_t p5;
	int16_t p6;
	int16_t p7;
	int16_t p8;
	int16_t p9;
} bmp280_trimming_t;

typedef struct {
	union {
		unsigned int be :24;
		uint8_t raw[3];
	} up;
	union {
		unsigned int be :24;
		uint8_t raw[3];
	} ut;
} bmp280_measurement_t;

typedef struct {
	bshal_i2cm_instance_t * p_i2c;
	uint8_t addr;
} bmp280_t;

#pragma pack(pop)

#define BMP280_REG_TRIM	(0x88)
#define BMP280_REG_MEAS	(0xF7)

#define BMP280_I2C_ADDR1 (0x76)
#define BMP280_I2C_ADDR2 (0x77)
#define BMP280_I2C_ADDR BMP280_I2C_ADDR1

#endif // __BMP_280_H__
