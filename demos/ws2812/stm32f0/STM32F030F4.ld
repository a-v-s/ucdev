/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 16K
RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 4K
}


/* Using the common linker script (from nrfx) as it's license is free
   Where as the license from the stm examples is non-free */
INCLUDE "ld_common.ld"




