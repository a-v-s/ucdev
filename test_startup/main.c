#include <stdio.h>

int irq_count();

#define __NVIC_PRIO_BITS           4U       /*!< STM32 uses 4 Bits for the Priority Levels    */
typedef int IRQn_Type;
#define SysTick_IRQn -1
#define IRQ_COUNT 64

#include "core_cm3.h"

void __attribute__((interrupt)) EXTI0_IRQHandler(void) {

}

void Interrupt6_Handler(void) __attribute__ ((alias("EXTI0_IRQHandler")));

int main() {
	int count = irq_count();
	//printf("This MCU supports %d interrupts\n", count);

	NVIC_SetPendingIRQ(5);
	NVIC_EnableIRQ(5);

	while (1)
		;
}
