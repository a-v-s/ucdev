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

int main(void) {
	btn_init();

	while (1)
		;
}

