.weak eclic_msip_handler
.weak eclic_mtip_handler
.weak eclic_bwei_handler
.weak eclic_pmovi_handler

#include "riscv_encoding.h"

.section	.gd32_vector,"ax",@progbits
.global		gd32_vector_base
gd32_vector_base:
/* 	GD32VF103 internal interrupts
	These are ECLIC / BumbleBee specific interrupts 
*/
    j Reset_Handler
    .align    2
    .word     0
    .word     0
    .word     eclic_msip_handler
    .word     0
    .word     0
    .word  	  0
    .word  	  eclic_mtip_handler
    .word  	  0
    .word  	  0
    .word  	  0
    .word  	  0
    .word  	  0
    .word  	  0
    .word  	  0
    .word 	  0
    .word  	  0
    .word  	  eclic_bwei_handler
    .word  	  eclic_pmovi_handler

    /*
		Begin of External (Peripheral) interrupts 
    	For now paste the STM32F103 interrupts such we agree on the names.
    */

	.word WWDG_IRQHandler
	.word PVD_IRQHandler
	.word TAMPER_IRQHandler
	.word RTC_IRQHandler
	.word FLASH_IRQHandler
	.word RCC_IRQHandler
	.word EXTI0_IRQHandler
	.word EXTI1_IRQHandler
	.word EXTI2_IRQHandler
	.word EXTI3_IRQHandler
	.word EXTI4_IRQHandler
	.word DMA1_Channel1_IRQHandler
	.word DMA1_Channel2_IRQHandler
	.word DMA1_Channel3_IRQHandler
	.word DMA1_Channel4_IRQHandler
	.word DMA1_Channel5_IRQHandler
	.word DMA1_Channel6_IRQHandler
	.word DMA1_Channel7_IRQHandler
	.word ADC1_2_IRQHandler
	.word USB_HP_CAN1_TX_IRQHandler
	.word USB_LP_CAN1_RX0_IRQHandler
	.word CAN1_RX1_IRQHandler
	.word CAN1_SCE_IRQHandler
	.word EXTI9_5_IRQHandler
	.word TIM1_BRK_IRQHandler
	.word TIM1_UP_IRQHandler
	.word TIM1_TRG_COM_IRQHandler
	.word TIM1_CC_IRQHandler
	.word TIM2_IRQHandler
	.word TIM3_IRQHandler
	.word TIM4_IRQHandler
	.word I2C1_EV_IRQHandler
	.word I2C1_ER_IRQHandler
	.word I2C2_EV_IRQHandler
	.word I2C2_ER_IRQHandler
	.word SPI1_IRQHandler
	.word SPI2_IRQHandler
	.word USART1_IRQHandler
	.word USART2_IRQHandler
	.word USART3_IRQHandler
	.word EXTI15_10_IRQHandler
	.word RTC_Alarm_IRQHandler
	.word USBWakeUp_IRQHandler

################################################################################
#
# GD32VF103 specific initialisation
# This will configure the interrupt controller (ECLIC)
# Then call main
#
###############################################################################
#
.section	.text,"ax",@progbits
.extern init_gd32
.global _init_gd32
.extern gd32_exc_entry
.extern gd32_irq_entry
_init_gd32:
	/* when running init_gd32 it seems to be running in non-vectored mode */
	/* the interrupt fires through, but not processed correctly */

	/* looking how to initialise the interrupt handler */
	/* with the copy-pasted code below, nothing happens */

	//j init_gd32
/* TODO: IMPLEMENT ME! */
	csrc CSR_MSTATUS, MSTATUS_MIE
    /* Set the the NMI base to share with mtvec by setting CSR_MMISC_CTL */
    li t0, 0x200
    csrs CSR_MMISC_CTL, t0

	/* Intial the mtvt*/
    la t0, gd32_vector_base
    csrw CSR_MTVT, t0

	/* Intial the mtvt2 and enable it*/
    la t0, gd32_irq_entry
    csrw CSR_MTVT2, t0
    csrs CSR_MTVT2, 0x1

    /* Intial the CSR MTVEC for the Trap ane NMI base addr*/
    la t0, gd32_exc_entry
    csrw CSR_MTVEC, t0

	j init_gd32
