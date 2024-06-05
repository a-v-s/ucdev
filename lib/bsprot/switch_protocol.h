/*
 * switch_protocol.h
 *
 *  Created on: 19 jan. 2024
 *      Author: andre
 */

#ifndef BSPROT_SWITCH_PROTOCOL_H_
#define BSPROT_SWITCH_PROTOCOL_H_

#include "protocol.h"

#define BSCP_CMD_SWITCH				0x20

typedef enum {
	bsprot_switch_onoff = 0,		//
	bsprot_switch_polarised = 1,	//

	bsprot_switch_pwm_u8 = 2, //
	bsprot_switch_pwm_s8 = 3, //

	bsprot_switch_pwm_u16 = 4, //
	bsprot_switch_pwm_s16 = 5,

	bsprot_switch_pwm_u32 = 6, //
	bsprot_switch_pwm_s32 = 7, //
} bsprot_switch_type_t;

#endif /* BSPROT_SWITCH_PROTOCOL_H_ */
