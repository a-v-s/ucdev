/*
 * hf.asm
 *
 *  Created on: 26 mrt. 2022
 *      Author: andre
 */

  .syntax unified
  .cpu cortex-m3
  .fpu softvfp
  .thumb

.global HardFault_Handler
.section .text.HardFault_Handler,"ax",%progbits
HardFault_Handler:
tst lr, #4
ite eq
mrseq r0, msp
mrsne r0, psp
ldr r1, [r0, #24]
ldr r2, handler2_address_const
bx r2
handler2_address_const: .word prvGetRegistersFromStack
.size  HardFault_Handler, .-HardFault_Handler
