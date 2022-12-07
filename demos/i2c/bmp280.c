#include <stdfix.h>
#include "bmp280.h"
#include "endian.h"
#include "bshal_i2cm.h"

uint32_t be24toh(uint32_t in) {

}

#ifdef __ACCUM_FBIT__
// Based on the BMP280 datasheet Appendix 1.
// Using the floating point example rather then the fixed point
// As they use emulated fixed point, where I'll use ISO18037
// Not using the datasheet's example for fixed point as they
// use fixed point emulation rather then fixed point types.
void bmp280_compensate_a(bmp280_trimming_t *trimming,
		bmp280_measurement_t *measurement, accum *temperature, long accum *pressure) {

	int32_t adc_T = measurement->ut.raw[0]<< 12 | measurement->ut.raw[1]<< 4 | measurement->ut.raw[2] >> 4;
	int32_t adc_P = measurement->up.raw[0]<< 12 | measurement->up.raw[1]<< 4 | measurement->up.raw[2] >> 4;

	if (0x80000 == adc_P || 0x80000 == adc_T) {
		// No data available
		*temperature = 0;
		* pressure = 0;
		return;
	}

	int32_t t_fine;
	long accum var1, var2;

	var1 = (((long accum) adc_T) / 16384.0lk - ((long accum) trimming->t1)/1024.0lk)
			* ((long accum) trimming->t2);
	var2 =
			((((long accum) adc_T) / 131072.0lk - ((long accum) trimming->t1)/8192.0lk)* (((long accum)adc_T)/131072.0lk - ((long accum) trimming->t1)/8192.0lk))
			* ((long accum) trimming->t3);
	t_fine = (int32_t)(var1 + var2);
	*temperature = (var1 + var2) / 5120.0lk;

	var1 = ((long accum) t_fine / 2.0lk) - 64000.0lk;
	var2 = var1 * var1 * ((long accum) trimming->p6) / 32768.0lk;
	var2 = var2 + var1 * ((long accum) trimming->p5) * 2.0lk;
	var2 = (var2 / 4.0lk) + (((long accum) trimming->p4) * 65536.0lk);
	var1 = (((long accum) trimming->p3) * var1 * var1 / 524288.0lk
			+ ((long accum) trimming->p2) * var1) / 524288.0lk;
	var1 = (1.0lk + var1 / 32768.0lk) * ((long accum) trimming->p1);
	if (var1 == 0.0lk) {
		*pressure = 0;
		// avoid exception caused by division by zero
	} else {
		long accum p;
		p = 1048576.0lk - (long accum)adc_P;
		p = (p - (var2 / 4096.0lk)) * 6250.0lk / var1;
		var1 = ((long accum)trimming->p9) * p * p / 2147483648.0lk;
		var2 = p * ((long accum)trimming->p8) / 32768.0lk;
		p = p + (var1 + var2 + ((long accum)trimming->p7)) / 16.0lk;
		*pressure = p;
	}
}
#endif

void bmp280_compensate_f(bmp280_trimming_t *trimming,
		bmp280_measurement_t *measurement, float *temperature, float *pressure) {

	int32_t adc_T = measurement->ut.raw[0] << 12 | measurement->ut.raw[1] << 4
			| measurement->ut.raw[2] >> 4;
	int32_t adc_P = measurement->up.raw[0] << 12 | measurement->up.raw[1] << 4
			| measurement->up.raw[2] >> 4;

	int32_t t_fine;
	float var1, var2;

	var1 = (((float) adc_T) / 16384.0f - ((float) trimming->t1) / 1024.0f)
					* ((float) trimming->t2);
	var2 = ((((float) adc_T) / 131072.0f - ((float) trimming->t1) / 8192.0f)
			* (((float) adc_T) / 131072.0f - ((float) trimming->t1) / 8192.0f))
					* ((float) trimming->t3);
	t_fine = (int32_t)(var1 + var2);
	*temperature = (var1 + var2) / 5120.0f;

	var1 = ((float) t_fine / 2.0f) - 64000.0f;
	var2 = var1 * var1 * ((float) trimming->p6) / 32768.0f;
	var2 = var2 + var1 * ((float) trimming->p5) * 2.0f;
	var2 = (var2 / 4.0f) + (((float) trimming->p4) * 65536.0f);
	var1 = (((float) trimming->p3) * var1 * var1 / 524288.0f
			+ ((float) trimming->p2) * var1) / 524288.0f;
	var1 = (1.0f + var1 / 32768.0f) * ((float) trimming->p1);
	if (var1 == 0.0f) {
		*pressure = 0;
		// avoid exception caused by division by zero
	} else {
		float p;
		p = 1048576.0f - (float) adc_P;
		p = (p - (var2 / 4096.0f)) * 6250.0f / var1;
		var1 = ((float) trimming->p9) * p * p / 2147483648.0f;
		var2 = p * ((float) trimming->p8) / 32768.0f;
		p = p + (var1 + var2 + ((float) trimming->p7)) / 16.0f;
		*pressure = p;
	}
}

#ifdef __ACCUM_FBIT__
// Run the example from the datasheet (page 23)
void bmp280_test() {
	bmp280_trimming_t trimming;
	bmp280_measurement_t measurement;
	accum temperature;
	long accum
	pressure;

	trimming.t1 = 27504;
	trimming.t2 = 26435;
	trimming.t3 = -1000;
	trimming.p1 = 36477;
	trimming.p2 = -10685;
	trimming.p3 = 3024;
	trimming.p4 = 2855;
	trimming.p5 = 140;
	trimming.p6 = -7;
	trimming.p7 = 15500;
	trimming.p8 = -14600;
	trimming.p9 = 6000;

	measurement.ut.raw[0] = 0x7E;
	measurement.ut.raw[1] = 0xED;
	measurement.ut.raw[2] = 0x00;

	measurement.up.raw[0] = 0x65;
	measurement.up.raw[1] = 0x5A;
	measurement.up.raw[2] = 0xC0;



	bmp280_compensate_a(&trimming, &measurement, &temperature, &pressure);
	// convert to float so gdb shows me the value
	float t = temperature;
	float p = pressure;

	bmp280_compensate_f(&trimming, &measurement, &t, &p);
	(void) p;
}


int bmp280_measure_a(bmp280_t* bmp280, accum *temperature, long accum *pressure) {
	bmp280_trimming_t trimming;
	bmp280_measurement_t measurement;

	bshal_i2cm_recv_reg(bmp280->p_i2c, bmp280->addr, BMP280_REG_TRIM,
			&trimming, sizeof(trimming) );

	bshal_i2cm_recv_reg(bmp280->p_i2c, bmp280->addr, BMP280_REG_MEAS,
			&measurement, sizeof(measurement) );

	bmp280_compensate_a(&trimming, &measurement, temperature, pressure);
}
#endif
int bmp280_measure_f(bmp280_t *bmp280, float *temperature, float *pressure) {
	bmp280_trimming_t trimming;
	bmp280_measurement_t measurement;

	bshal_i2cm_recv_reg(bmp280->p_i2c, bmp280->addr, BMP280_REG_TRIM, &trimming,
			sizeof(trimming));

	bshal_i2cm_recv_reg(bmp280->p_i2c, bmp280->addr, BMP280_REG_MEAS,
			&measurement, sizeof(measurement));

	bmp280_compensate_f(&trimming, &measurement, temperature, pressure);
}

int bmp280_init(bmp280_t *bmp280) {
	// quick and drity, need to make this neat later
	// but this should get it in measurement mode
	uint8_t ctlr_meas = -1;
	return bshal_i2cm_send_reg(bmp280->p_i2c, bmp280->addr, 0xF4, &ctlr_meas, 1);
}
