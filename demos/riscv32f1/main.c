#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

//#include "int.h"

volatile int blaat[] = { 1, 2, 3, 4 };
#include "stm32f1xx_hal.h"

#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"

void __attribute__ ((interrupt)) EXTI9_5_IRQHandler(void) {

	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_All);
}

void __attribute__ ((interrupt)) EXTI15_10_IRQHandler(void) {

	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_All);
}

int btn_init(void) {

	// Enable GPIO Port A Clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Enable GPIO Port B Clock
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	// Common configuration for all channels
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	return 0;
}


#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) ({ \
  if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
    asm volatile ("csrw " #reg ", %0" :: "i"(val)); \
  else \
    asm volatile ("csrw " #reg ", %0" :: "r"(val)); })

#define swap_csr(reg, val) ({ unsigned long __tmp; \
  if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
    asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "i"(val)); \
  else \
    asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "r"(val)); \
  __tmp; })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)




int main(void) {
	btn_init();
	int t = rdtime();
	while (1) {

	}
}

