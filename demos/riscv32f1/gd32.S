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

	la t0, gd32_vector_base // Load address for
	csrw CSR_MTVT, t0       // the vector table

	la t0, gd32_irq_entry // Load address for
	csrw CSR_MTVT2, t0    // Unvectored interrutps
	csrs CSR_MTVT2, 0x1   // and enable them

	la t0, gd32_exc_entry // Load address for
	csrw CSR_MTVEC, t0    // exceptions
	csrs CSR_MTVEC, 0x03  // enable   CLIC mode

	j init_gd32
