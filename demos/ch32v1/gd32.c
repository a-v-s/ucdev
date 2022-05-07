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


// I'm not getting this working yer
//extern uint32_t gd32_vector_base __attribute__ ((section(".gd32_vector")));
#include <stdint.h>
extern uint32_t gd32_vector_base[];

int main(void);

void init_gd32(void) {
	// Both GD32VF and NMSIS template do this
	// Look up what is does
	ECLIC_SetMth(0);
	// GD32CF code sets it to 0
	ECLIC_SetCfgNlbits(0);
	// From the NMSIS template... what are these bits,
	// and are there none in this chip?
    //ECLIC_SetCfgNlbits(__ECLIC_INTCTLBITS);


	// Set the vector table address
	// Hard coded now, should get changed to automatically set from the linker script
    __set_exc_entry(0x100);

    main();
}
