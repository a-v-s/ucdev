/*
 * adxl345.c
 *
 *  Created on: 21 jan. 2022
 *      Author: andre
 */


#include "adxl345.h"


int adxl345_init(adxl345_instance_t * instance){
	if (!instance) return -1;
	switch (instance->transport_type) {
	case bshal_transport_i2c:
		instance->read = (adxl_access_register_f)(bshal_i2cm_recv_reg);
		instance->write = (adxl_access_register_f)(bshal_i2cm_send_reg);
		break;
	case bshal_transport_spi:
		instance->read = (adxl_access_register_f)(adxl345_spim_recv_reg);
		instance->write = (adxl_access_register_f)(adxl345_spim_send_reg);
		break;
	default:
		return -2;
	}


}
