#include <stdint.h>
#include <stdbool.h>

#include <system.h>
#include "timer.h"
#include "ir.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	ir_handler (HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_11));
}

void EXTI15_10_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
}

void ir_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_11;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}


