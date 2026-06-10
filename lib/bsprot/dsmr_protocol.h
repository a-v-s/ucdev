/*
 * dsmr_protocol.h
 *
 *  Created on: 22 dec. 2023
 *      Author: andre
 */

#ifndef BSPROT_DSMR_PROTOCOL_H_
#define BSPROT_DSMR_PROTOCOL_H_



#pragma pack (push,1)

#define BSCP_CMD_DSMR_ENERGY (0x30)
#define BSCP_CMD_DSMR_PHASE1 (0x31)
#define BSCP_CMD_DSMR_PHASE2 (0x32)
#define BSCP_CMD_DSMR_PHASE3 (0x33)


typedef struct {
	float u_volt;
	float i_ampere;
	float e_received_kilowatt;
	float e_delivered_kilowatt;
	float p_receiving;
	float p_delivering;
} bsprot_dsmr_phase_t;

typedef struct {
	float lo_received_kilowatthour;
	float lo_delivered_kilowatthour;
	float hi_received_kilowatthour;
	float hi_delivered_kilowatthour;
} bsprot_dsmr_energy_t;

#pragma pack (pop)

#endif /* BSPROT_DSMR_PROTOCOL_H_ */
