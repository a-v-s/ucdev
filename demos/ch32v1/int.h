#ifndef __INTERRUPTS_H_
#define __INTERRUPTS_H_

#include <stdint.h>

uint32_t SystemCoreClock;
extern const uint8_t AHBPrescTable[16U];
extern const uint8_t APBPrescTable[8U];

//
// /*!< Interrupt Number Definition */
//typedef enum
//{
/////******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
////  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
////  HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
////  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
////  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
////  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
////  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
////  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
////  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
////  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */
////
/////******  STM32 specific Interrupt Numbers *********************************************************/
//  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
//  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
//  TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
//  RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
//  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
//  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
//  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
//  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
//  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
//  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
//  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
//  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
//  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
//  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
//  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
//  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
//  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
//  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
//  ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
//  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
//  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
//  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
//  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
//  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
//  TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
//  TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
//  TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
//  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
//  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
//  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
//  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
//  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
//  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
//  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
//  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
//  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
//  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
//  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
//  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
//  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
//  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
//  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
//  USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
//} STM32_IRQn_Type;



#define IRQn_Type           int
#define __ECLIC_PRESENT 	1
#define __ECLIC_BASEADDR 	0xd2000000
#include "ch32/core_ch32.h"
#include "core_feature_eclic.h"


#ifndef read_csr
#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })
#endif

#define GD32_MARCHID 0x80000022
#define GD32_IRQ_OFFSET	19
#define CH32_IRQ_OFFSET 16


#define NVIC_EnableIRQ              __Compat_EnableIRQ
#define NVIC_DisableIRQ             __Compat_DisableIRQ
#define NVIC_GetPendingIRQ          __Compat_GetPendingIRQ
#define NVIC_SetPendingIRQ          __Compat_SetPendingIRQ
#define NVIC_ClearPendingIRQ        __Compat_ClearPendingIRQ
#define NVIC_SetPriority            __Compat_SetPriority

// Functions that have no obvious equivalent for any or either PFIC or ECLIC
// This will require some manual work to enable them
//#define NVIC_SetPriorityGrouping    __Compat_SetPriorityGrouping 	// -PFIC -ECLIC
//#define NVIC_GetPriorityGrouping    __Compat_GetPriorityGrouping	// -PFIC -ECLIC
//#define NVIC_GetEnableIRQ           __Compat_GetEnableIRQ 		// -PFIC +ECLIC
//#define NVIC_GetActive              __Compat_GetActive			// +PFIC -ECLIC
//#define NVIC_GetPriority            __Compat_GetPriority			// -PFIC +ECLIC
//#define NVIC_SystemReset            __Compat_SystemReset			// +PFIC -ECLIC

static inline void __Compat_EnableIRQ(int IRQn){
	if (read_csr(marchid)==GD32_MARCHID) {
		IRQn += GD32_IRQ_OFFSET;
		ECLIC_EnableIRQ(IRQn);
	} else {
		IRQn += CH32_IRQ_OFFSET;
		PFIC_EnableIRQ(IRQn);
	}
}

static inline void __Compat_DisableIRQ(int IRQn){
	if (read_csr(marchid)==GD32_MARCHID) {
		IRQn += GD32_IRQ_OFFSET;
		ECLIC_DisableIRQ(IRQn);
	} else {
		IRQn += CH32_IRQ_OFFSET;
		PFIC_DisableIRQ(IRQn);
	}
}

static inline uint32_t __Compat_GetPendingIRQ(int IRQn){
	if (read_csr(marchid)==GD32_MARCHID) {
		IRQn += GD32_IRQ_OFFSET;
		return ECLIC_GetPendingIRQ(IRQn);
	} else {
		IRQn += CH32_IRQ_OFFSET;
		return PFIC_GetPendingIRQ(IRQn);
	}
}
static inline void __Compat_SetPendingIRQ(int IRQn){
	if (read_csr(marchid)==GD32_MARCHID) {
		IRQn += GD32_IRQ_OFFSET;
		ECLIC_SetPendingIRQ(IRQn);
	} else {
		IRQn += CH32_IRQ_OFFSET;
		PFIC_SetPendingIRQ(IRQn);
	}
}

static inline void  __Compat_ClearPendingIRQ(int IRQn){
	if (read_csr(marchid)==GD32_MARCHID) {
		IRQn += GD32_IRQ_OFFSET;
		ECLIC_ClearPendingIRQ(IRQn);
	} else {
		IRQn += CH32_IRQ_OFFSET;
		PFIC_ClearPendingIRQ(IRQn);
	}
}

static inline void __Compat_SetPriority(int IRQn, uint8_t priority){
	// NB. TODO: Verify the priority parameter is compatible
	if (read_csr(marchid)==GD32_MARCHID) {
		IRQn += GD32_IRQ_OFFSET;
		ECLIC_SetPriorityIRQ(IRQn, priority);
	} else {
		IRQn += CH32_IRQ_OFFSET;
		PFIC_SetPriority(IRQn, priority);
	}
}


static inline void NVIC_SetFastIRQ(uint32_t addr, int IRQn, uint8_t num){}
static inline void NVIC_SystemReset(void){}

//static inline uint32_t NVIC_GetActive(int IRQn){}
//static inline uint32_t NVIC_GetStatusIRQ(int IRQn){}

#endif // __INTERRUPTS_H_

