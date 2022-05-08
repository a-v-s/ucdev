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


#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) ({ \
  if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
    asm volatile ("csrw " #reg ", %0" :: "i"(val)); \
  else \
    asm volatile ("csrw " #reg ", %0" :: "r"(val)); })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })



// I'm not getting this working yer
//extern uint32_t gd32_vector_base __attribute__ ((section(".gd32_vector")));
#include <stdint.h>
extern uint32_t gd32_vector_base[];

int main(void);

void test(void) {
	while(1);
}

void init_gd32(void) {

	clear_csr(mstatus, MSTATUS_MIE);


	// Both GD32VF and NMSIS template do this
	// Look up what is does
	ECLIC_SetMth(0);
	// GD32CF code sets it to 0
	//ECLIC_SetCfgNlbits(0);
	// From the NMSIS template... what are these bits,
	// and are there none in this chip?
    //ECLIC_SetCfgNlbits(__ECLIC_INTCTLBITS);
	//ECLIC_SetCfgNlbits(8);
	ECLIC->CFG = 0;


	// Set the vector table address
	// Hard coded now, should get changed to automatically set from the linker script
    //__set_exc_entry(0x100); // well... what do we do here
    // as the mode bits are set to 0b11, it enabled ECLIC, then what does the
    // address in there do as it should go to mtvt instead (or too)?


//	// Set ECLIC vector table
//	write_csr(mtvt, 0x000);
//	// Set ECLIC mode

	uint32_t mtvec_val = read_csr(mtvec);
	mtvec_val |= 3;
	set_csr(mtvec, mtvec_val);
	// enable interrupts

	for (int i  = 0; i < 100 ; i++ ) {
		ECLIC_SetShvIRQ(i, 1);
	}

	set_csr(mstatus, MSTATUS_MIE);

    main();
}
