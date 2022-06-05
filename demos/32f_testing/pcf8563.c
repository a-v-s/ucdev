/*
 * pcf8563.c
 *
 *  Created on: 29 aug. 2021
 *      Author: andre
 */



#include "pcf8563.h"



int pcf8563_get_time(pcf8563_t * pcf8563, pcf8563_time_t* time) {
	return bshal_i2cm_recv_reg(pcf8563->p_i2c, pcf8563->addr, 0x02,
			time, sizeof(pcf8563_time_t));
}

int pcf8563_set_time(pcf8563_t * pcf8563, pcf8563_time_t* time) {
	return bshal_i2cm_send_reg(pcf8563->p_i2c, pcf8563->addr, 0x02,
			time, sizeof(pcf8563_time_t));
}
