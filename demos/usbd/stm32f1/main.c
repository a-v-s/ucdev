#include "usbd_stm.h"

#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"

void usbd_reenumerate(){
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	// Let's try to distinguise Blue Pill and STM32 Board v3.x
	// https://github.com/a-v-s/pcb_stm32XxxxCx_board
	// And handle the pin states

	GPIO_InitStruct.Pin = (GPIO_PIN_12);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)) {
		// Running on Blue Pill (or other board with a hard wired pull up resistor)
		// For this, we'll configure as output and drive it low.

		GPIO_InitStruct.Pin = (GPIO_PIN_11 | GPIO_PIN_12);
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_Delay(1);
	} else {
		// We are running on a board without a hard wired pull up resistor.
		// For now I'll assume it's my own STM32 v3.x board, which has a pull up
		// resistor connected through PC13
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_InitStruct.Pin = (GPIO_PIN_13);
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);


		return;// disable test to debug gd32 issue


		// Now we're starting to probe the pin after setting it,
		// Do we need a delay to allow the pin to settle?
		if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)) {
			return;
		} else {
			// We're on some other board,
			// de-init the PC13 and clock
			HAL_GPIO_DeInit(GPIOC, GPIO_PIN_13);
			__HAL_RCC_GPIOC_CLK_DISABLE();

			// There are some other boards to probe
			// We need to list the possible pins to try and their polarity

			// We might wait to de-initialise PC13, according to earlier notes
			// "STM32F1XX CORE BOARD" has inverted PC13

			// Maple Mini needs PB9 active according to
			// https://www.eevblog.com/forum/microcontrollers/stm32f103c8-diagnostic-bootable-binary-freely-available/msg2903320/#msg2903320


		}
	}
}

void ClockSetup(void)
{
	ClockSetup_HSE8_SYS72();
	//ClockSetup_HSE8_SYS48();
	//ClockSetup_HSI_SYS48();
}

int main() {
	HAL_Init();
	ClockSetup();

	usbd_reenumerate();
	usbd_init();

	while (1)
		;;
}
