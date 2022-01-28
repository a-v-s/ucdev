/*
 * adxl345.h
 *
 *  Created on: 21 jan. 2022
 *      Author: andre
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#define ADXL_I2C_ADDR1	(0x1D)
#define ADXL_I2C_ADDR0	(0x3B)

#define ADXL_SPI_MODE 	(3)
#define ADXL_SPI_SPEED 	(5000000)

typedef int (*adxl_access_register_f)(void* transport_instance, uint8_t address, uint8_t reg, uint8_t * p_data, uint8_t length);

typedef struct {
	bshal_transport_t transport_type;
	bshal_transport_instance_t transport_instance;
	uint8_t i2c_address; // Only applicable if transport is i2c
	adxl_access_register_f read;
	adxl_access_register_f write;
} adxl345_instance_t;


int adxl345_init(adxl345_instance_t * instance);

// For I²C communication we will the ADXL345 uses "standard i2c" register access, as implemented in
// bshal_i2cm_send_reg() and bshal_i2cm_recv_reg()
// SPI devices mimicking register access are not all that standard, so write an implementation for our device
// However, keeping the function signature as similar possible to keep the implementation simple.
// Therefore we have an ignored 2nd parameter, where the I²C address would go. But keeping it there
// leaves the function parameters (other then pointer type for the transport instance) the same
int adxl345_spim_send_reg(bshal_spim_instance_t* spim_instance, uint8_t ignored, uint8_t reg, uint8_t * p_data, uint8_t length);
int adxl345_spim_recv_reg(bshal_spim_instance_t* spim_instance, uint8_t ignored, uint8_t reg, uint8_t * p_data, uint8_t length);



#endif /* ADXL345_H_ */
