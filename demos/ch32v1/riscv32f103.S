.equ GD32_MARCHID,    0x80000022		# Identifiers for GD32VF103
.equ GD32_MVENDORID,  0x0000031E		# Identifiers for GD32VF103

.equ CH32_MARCHID,    0x00000000		# Identifiers for CH32V103
.equ CH32_MVENDORID,  0x01020304		# Identifiers for CH32V103

.extern init_gd32
.extern init_ch32

.section	.text.handle_reset,"ax",@progbits
#.globl _start
#.type _start,@function

.globl handle_reset
.type handle_reset,@function


/*	We are running on GD32VF103 or CH32V103. 
 *  These designs alias either flash or ram to 0x0 depending on the
 *  BOOT pins. This start routine will detect the boot mode and jump
 *  to the real address space rather then the aliassed address space at 0x0
 */

/*  It seems the CH32V103 implementation required the use of 0x0 as the
 *  base rather then the real 0x8000000 address. Fortunately the GD32VF103
 *  allows flashing with the aliassed address.
 */

 /*
handle_reset:
	//csrc CSR_MSTATUS, MSTATUS_MIE 	# Disable interrupts

    la		a0,	handle_reset				# a0 = address of _start
    li		a1,	1					# a1 = 1
	slli	a1,	a1, 29				# a1 <<= 29
									# a1 is now 0x20000000
									# This is where RAM begins
									# We will jump to __start if we are
    bleu	a1, a0, _start0800		# booting from RAM
    srli	a1,	a1, 2				# Othwerwise, we set a1 to 0x8000000
    bleu	a1, a0, _start0800      # And jump if we are booting from flash
    la		a0,	_start0800			# Otherwise, we've booted from 0x0
    add		a0, a0, a1				# then we add 0x8000000 to _start0800
	jr      a0						# and jump there

//---------------------------------------------------------------------------
_start0800:
									# Jump here at the real address
*/

handle_reset:
identify_chip:
	csrr    a0, marchid				
	csrr    a1, mvendorid

try_gd32:							# Check if we are runnng on a GD32VF103
	li      a2, GD32_MARCHID		# If the marchid != GD32_MARCHID
	bne     a0, a2, try_ch32		# We go check if it is a CH32V103
	li		a2, GD32_MVENDORID
	bne     a1, a2, chip_not_supported
	j	init_gd32					# GD32VF103 identified,

try_ch32:							# Check if we are runnng on a CH32V103
	li      a2, CH32_MARCHID
	bne     a0, a2, chip_not_supported
	li		a2, CH32_MVENDORID
	bne     a1, a2, chip_not_supported
	j	init_ch32					# CH32VF103 identified,

init_ch32:
init_gd32:
chip_not_supported:
	j chip_not_supported			# Endless loop for unknown chip






