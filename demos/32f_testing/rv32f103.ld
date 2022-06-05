ENTRY( Reset_Handler )

__stack_size = 2048;

PROVIDE( _stack_size = __stack_size );


MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 64K  
/*	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K */
	RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
}

INCLUDE "ld_riscv.ld"
