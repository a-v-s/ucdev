/*
 * pair.h
 *
 *  Created on: 21 sep. 2024
 *      Author: andre
 */

#ifndef PAIR_H_
#define PAIR_H_

#include <stdint.h>
#pragma pack (push,1)
typedef struct {
	uint32_t network_id;
	uint8_t node_id;
} pairing_t;
#pragma pack (pop)

#define BSCP_CMD_PAIR 0xB0



#endif /* PAIR_H_ */
