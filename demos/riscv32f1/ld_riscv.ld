/*
	References
	*	https://interrupt.memfault.com/blog/how-to-write-linker-scripts-for-firmware
	*	

*/


STACK_SIZE = 0x2000;

SECTIONS
{

/* Vector tables, in a way we can run the firmware on both
   GD32VF103 and CH32V103 chips
*/   
	.vtor : 
	{
		KEEP(*(.gd32_vector))
		. = ALIGN(0x100);
		KEEP(*(.ch32_vector))
        . = ALIGN(0x200);
		KEEP(*(.firmware_info))
	}
	
/* Text section: this is the code of the firmware */	
    .text :
    {
        *(.text.*)
        *(.rodata.*)
        PROVIDE ( _etext = . );
    } > FLASH


/* BSS section: Uninitialised data, will be zeroed on start */
    .bss (NOLOAD) :
    {
        PROVIDE ( _sbss = . );
        *(.bss .bss.*)
        *(COMMON)
        PROVIDE ( _ebss = . ) ;
    } > RAM

/* Memory alignment and provide _data_lma for the initialisation 
   The initialised data, values in flash to be copies to ram
*/

	  .lalign :
	  {
	    . = ALIGN(4);
	    PROVIDE( _data_lma = . );
	  } >FLASH AT>FLASH 

/* Memory alignment and provide _data_vma for the initialisation 
   The initialised data, where to write the data
*/	
	  .dalign :
	  {
	    . = ALIGN(4);
        PROVIDE( _data_vma = . );	    
	  } >RAM AT>FLASH 
  
  /* Data section (variables) */ 
    .data :
    {
        PROVIDE( _sdata = . );
        *(.data*);
        PROVIDE( _edata = . );
    } > RAM AT >FLASH


    /* stack section */
    .stack (NOLOAD):
    {
        . = ALIGN(8);
        PROVIDE( _sstack = . );
        . = . + STACK_SIZE;
        . = ALIGN(8);
        PROVIDE( _estack = . );
    } > RAM

	_data_size = _edata - _sdata;
	PROVIDE ( __global_pointer$ =  _sdata + ( _data_size / 2 ) );
	
	/* C++ Support */
	
	  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array*))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH
}



