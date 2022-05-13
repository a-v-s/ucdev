/*
 * gd32.c
 *
 *  Created on: 7 mei 2022
 *      Author: andre
 */

#define IRQn_Type           int
#define __ECLIC_PRESENT 	1
#define __ECLIC_BASEADDR 	0xd2000000

#include "core_feature_eclic.h"
#include "riscv_encoding.h"

void init_gd32(void) {
	ECLIC_SetMth(0);
	ECLIC_SetCfgNlbits(4);
	for (int i = 0; i < 86 ; i++ ) {
		ECLIC_SetShvIRQ(i, 1);
	}
	__enable_irq();
    main();
}
