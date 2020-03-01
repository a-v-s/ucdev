/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 128K
/*RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 20K*/
RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 16K
}


/* Using the common linker script (from nrfx) as it's license is free
   Where as the license from the stm examples is non-free */
INCLUDE "ld_common.ld"



/* Some patching around to make it work with the STM32 startup code */
_estack     = __StackTop;
_sidata     = LOADADDR(.data);
_sdata      = __data_start__;
_edata      = __data_end__;
_sbss       = __bss_start__;
_ebss       = __bss_end__;
