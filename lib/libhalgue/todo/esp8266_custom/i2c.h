#ifndef __I2C_H_
#define __I2C_H_


#define I2C_OK		0
#define I2C_ANACK 	-1	// Address Nack
#define I2C_DNACK 	-2  // Data Nack

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


void  i2c_init();
int i2c_send(uint8_t i2c_addr, void* data, size_t size,  bool nostop);
int i2c_recv(uint8_t i2c_addr, void* data, size_t size);

#endif //__I2C_H_
