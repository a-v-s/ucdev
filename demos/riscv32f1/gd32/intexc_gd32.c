/*
 * initexc_gd32.c
 *
 *  Created on: 8 mei 2022
 *      Author: andre
 */

#include <stdlib.h>
#include <stdint.h>

__attribute__((weak)) void handle_nmi(){
	//TODO
}

__attribute__((weak)) uintptr_t core_exception_handler(uintptr_t mcause, uintptr_t sp)
{
  if((mcause & 0xFFF) == 0xFFF) {
      handle_nmi();
  }
  _exit(mcause);
  return 0;
}
