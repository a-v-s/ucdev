// https://github.com/BillyWoods/ESP8266-I2C-example/blob/master/main.c


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "i2c.h"

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "../driver/custom_i2c_master.h"


void  i2c_init() {
    custom_i2c_master_gpio_init();
    custom_i2c_master_init();
}

int i2c_send(uint8_t i2c_addr, void* data, size_t size,  bool nostop) {
	int result = I2C_OK;
	uint8_t i2c_addr_write = (i2c_addr << 1);
	
    custom_i2c_master_start();
    custom_i2c_master_writeByte(i2c_addr_write);
	if (!custom_i2c_master_checkAck()) result = I2C_ANACK;

    for (int i = 0 ; !result && i < size ; i++ ) { 
		custom_i2c_master_writeByte(((uint8_t*)(data))[i]);
		if (!custom_i2c_master_checkAck()) result = I2C_DNACK;
	}

	if (!nostop && !result) custom_i2c_master_stop();

	return result;
}

int i2c_recv(uint8_t i2c_addr, void* data, size_t size) {
	int result = I2C_OK;    
	uint8_t i2c_addr_read = (i2c_addr << 1) + 1;

    custom_i2c_master_start();
    custom_i2c_master_writeByte(i2c_addr_read);
	if (!custom_i2c_master_checkAck()) result = I2C_ANACK;

    for(int i = 0; !result && i < size - 1; i++) {
        ((uint8_t*)(data))[i] = custom_i2c_master_readByte();
        custom_i2c_master_send_ack();
		if (!custom_i2c_master_checkAck()) result = I2C_DNACK;
    }
    // nack the final packet so that the slave releases SDA
    ((uint8_t*)(data))[size - 1] = custom_i2c_master_readByte();
	custom_i2c_master_send_nack();

	// we are nacking, so this should be nack
	//if (!custom_i2c_master_checkAck()) result = I2C_DNACK;
	custom_i2c_master_stop();
	return result;
}
