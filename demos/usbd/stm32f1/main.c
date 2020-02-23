#include "usbd_stm.h"

#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"

void usbd_reenumerate(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	// Configure USB DM/DP pins
	GPIO_InitStruct.Pin = (GPIO_PIN_11 | GPIO_PIN_12);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void ClockSetup(void)
{
	//ClockSetup_HSE8_SYS72();
	//ClockSetup_HSE8_SYS48();
	ClockSetup_HSI_SYS48();
}

int main() {
	HAL_Init();
	ClockSetup();

	usbd_reenumerate();
	usbd_init();

	while (1)
		;;
}
