/*
	References
	*	https://interrupt.memfault.com/blog/how-to-write-linker-scripts-for-firmware
	*	https://stackoverflow.com/questions/4756694/linker-script-for-c-program-for-lm3s8962-unhosted-using-codesourcery-lite-tool

*/

/* Entry Point */
ENTRY(Reset_Handler)

__STACK_SIZE = 0x00000400;
__HEAP_SIZE  = 0x00000C00;
__STACKSEAL_SIZE = 0;

SECTIONS
{


	/* Universal linker file to create both Cortex-M and RISC-V firmwares 
		isr_vector : Cortex-M vector table 
		ch32_vector: RISCV CH32V103 vector table
		gd32_vector: RISCV GD32VF103 vector table

		ch32 and gd32 can be combined in a single binary.
		no other RISC-V cores are supported at the moment 
	*/

	.vtor : 
	{
    . = ALIGN(4);
    	KEEP(*(.isr_vector)) 
    . = ALIGN(4);
		KEEP(*(.ch32_vector))
        . = ALIGN(0x100);
		KEEP(*(.gd32_vector))
        . = ALIGN(0x200);
		KEEP(*(.firmware_info))
	} > FLASH
	
/* Text section: this is the code of the firmware */	
	.text :
	{
		*(.text*)

		KEEP(*(.init))
		KEEP(*(.fini))

		/* .ctors */
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

		/* .dtors */
		*crtbegin.o(.dtors)
		*crtbegin?.o(.dtors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
		*(SORT(.dtors.*))
		*(.dtors)

		*(.rodata*)

		KEEP(*(.eh_frame*))
  } > FLASH


/* BSS section: Uninitialised data, will be zeroed on start */
    .bss (NOLOAD) :
    {
        PROVIDE ( _sbss = . );
        PROVIDE ( __bss_start__ = . );
        *(.bss .bss.*)
        *(COMMON)
        PROVIDE ( _ebss = . ) ;
        PROVIDE ( __bss_end__ = . );
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
		PROVIDE( __data_start__ = . );
        *(.data*);
        PROVIDE( _edata = . );
		PROVIDE( __data_end__ = . );
    } > RAM AT >FLASH

	.heap (COPY) :
	{
		. = ALIGN(8);
		__end__ = .;
		PROVIDE(end = .);
		PROVIDE( _sheap = . );
		. = . + __HEAP_SIZE;
		. = ALIGN(8);
		__HeapLimit = .;
		PROVIDE( _eheap = . );
	} > RAM

	.stack (ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE - __STACKSEAL_SIZE) (COPY) :
	{
		. = ALIGN(8);
        PROVIDE( _sstack = . );
		__StackLimit = .;
		. = . + __STACK_SIZE;
		. = ALIGN(8);
		__StackTop = .;
		PROVIDE( _estack = . );
		PROVIDE( __stack = . );
		PROVIDE( __StackTop = .);
	} > RAM
	
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


	_data_size = _edata - _sdata;
	PROVIDE ( __global_pointer$ =  _sdata + ( _data_size / 2 ) );
}


