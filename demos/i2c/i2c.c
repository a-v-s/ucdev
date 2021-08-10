/*
 * i2c.c
 *
 *  Created on: 8 aug. 2021
 *      Author: andre
 */

#include "system.h"
#include "bshal_i2cm.h"

static bshal_i2cm_instance_t m_i2c;

bshal_i2cm_instance_t * i2c_init(void) {
	m_i2c.sda_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_11);
	m_i2c.scl_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_10);
	m_i2c.hw_nr = 2;
	bshal_stm32_i2cm_init(&m_i2c);
	return &m_i2c;
}
