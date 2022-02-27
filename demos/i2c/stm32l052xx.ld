/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH =  8K
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 64K
}


/* Using the common linker script (from nrfx) as it's license is free
   Where as the license from the stm examples is non-free */
INCLUDE "ld_common.ld"




