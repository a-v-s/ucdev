.weak NMI_Handler
.weak HardFault_Handler
.weak SysTick_Handler
.weak SW_handler



.section	.ch32_vector,"ax",@progbits
.global		ch32_vector_base
ch32_vector_base:
	.option norvc;  /*  Do not use compressed instructions */
/* 	CH32VF103 internal interrupts
	These are  FPIC / RISC-V3A specific interrupts 
*/

	j   Reset_Handler
	.word   0
	j   NMI_Handler                 /* NMI Handler */
	j   HardFault_Handler           /* Hard Fault Handler */
	.word   0
	.word   0
	.word   0
	.word   0
	.word   0
	.word   0
	.word   0
	.word   0
	j   SysTick_Handler            /* SysTick Handler */
	.word   0
	j   SW_handler                 /* SW Handler */
	.word   0

    /*
		Begin of External (Peripheral) interrupts 
    	For now paste the STM32F103 interrupts such we agree on the names.
    */

	j WWDG_IRQHandler
	j PVD_IRQHandler
	j TAMPER_IRQHandler
	j RTC_IRQHandler
	j FLASH_IRQHandler
	j RCC_IRQHandler
	j EXTI0_IRQHandler
	j EXTI1_IRQHandler
	j EXTI2_IRQHandler
	j EXTI3_IRQHandler
	j EXTI4_IRQHandler
	j DMA1_Channel1_IRQHandler
	j DMA1_Channel2_IRQHandler
	j DMA1_Channel3_IRQHandler
	j DMA1_Channel4_IRQHandler
	j DMA1_Channel5_IRQHandler
	j DMA1_Channel6_IRQHandler
	j DMA1_Channel7_IRQHandler
	j ADC1_2_IRQHandler
	j USB_HP_CAN1_TX_IRQHandler
	j USB_LP_CAN1_RX0_IRQHandler
	j CAN1_RX1_IRQHandler
	j CAN1_SCE_IRQHandler
	j EXTI9_5_IRQHandler
	j TIM1_BRK_IRQHandler
	j TIM1_UP_IRQHandler
	j TIM1_TRG_COM_IRQHandler
	j TIM1_CC_IRQHandler
	j TIM2_IRQHandler
	j TIM3_IRQHandler
	j TIM4_IRQHandler
	j I2C1_EV_IRQHandler
	j I2C1_ER_IRQHandler
	j I2C2_EV_IRQHandler
	j I2C2_ER_IRQHandler
	j SPI1_IRQHandler
	j SPI2_IRQHandler
	j USART1_IRQHandler
	j USART2_IRQHandler
	j USART3_IRQHandler
	j EXTI15_10_IRQHandler
	j RTC_Alarm_IRQHandler
	j USBWakeUp_IRQHandler

################################################################################
#
# CH32V103 specific initialisation
# This will configure the interrupt controller (FPIC)
# Then call main
#
###############################################################################

.section	.text,"ax",@progbits
.global init_ch32
.extern main
init_ch32:

  li t0, 0x88
  csrs mstatus, t0
	la t0, ch32_vector_base
  ori t0, t0, 1
	csrw mtvec, t0
	j main
