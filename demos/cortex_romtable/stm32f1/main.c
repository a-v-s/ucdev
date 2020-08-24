/*
 File:		main.c
 License: 	MIT

 Copyright (c) 2020 André van Schoubroeck

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "usbd_stm.h"

#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"

#include <stdint.h>

#include "arm_cpuid.h"

void usbd_reenumerate() {

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	// Let's try to distinguise Blue Pill and STM32 Board v3.x
	// https://github.com/a-v-s/pcb_stm32XxxxCx_board
	// And handle the pin states

	// Note: we need to distinguise between pullup and float
	// We can not use no pull. The internal pull down is supposed
	// to be way less then the pull up. However, on the faulty
	// Blue Pills with R10=10K in stead of R10=1K5 this might fail

	GPIO_InitStruct.Pin = (GPIO_PIN_12);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Cold boot doesn't work yet, reboot does
	// Should we delay some to make it work?
	HAL_Delay(1); // Again allow to settle.
	// Yes this solves it.

	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)) {
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
		HAL_Delay(1); // Should we wait for the pin to settle?

		// Now we're starting to probe the pin after setting it,
		// Do we need a delay to allow the pin to settle?
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)) {
			return;
		}

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_Delay(1); // Should we wait for the pin to settle?

		// We might wait to de-initialise PC13, according to earlier notes
		// "STM32F1XX CORE BOARD" has inverted PC13
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)) {
			return;
		}

		// We're on some other board,
		// de-init the PC13 and clock
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_13);
		__HAL_RCC_GPIOC_CLK_DISABLE();

		// There are some other boards to probe
		// We need to list the possible pins to try and their polarity

		// Maple Mini needs PB9 active according to
		// https://www.eevblog.com/forum/microcontrollers/stm32f103c8-diagnostic-bootable-binary-freely-available/msg2903320/#msg2903320

	}
}

void ClockSetup(void) {
	ClockSetup_HSE8_SYS72();
	//ClockSetup_HSE8_SYS48();
	//ClockSetup_HSI_SYS48();
}

char rt[128];

void parse_romtable() {

	intptr_t ROMTABLE = (intptr_t) (0xE00FF000);
	romtable_id_t *rid = (romtable_id_t*) (ROMTABLE | 0xFD0);
	romtable_pid_t romtable_pid = extract_romtable_pid(rid);

	char *prob = "Unknown";

	if (romtable_pid.jep106_used) {
		if (romtable_pid.identity_code == 32
				&& romtable_pid.continuation_code == 0) {
			prob = "STM32";
		}
		if (romtable_pid.identity_code == 81
				&& romtable_pid.continuation_code == 7) {
			prob = "GD32";
		}
		if (romtable_pid.identity_code == 59
				&& romtable_pid.continuation_code == 4) {
			// APM or CS
			cortex_m_romtable_t *rom = (romtable_id_t*) (ROMTABLE);
			if (rom->etm & 1) {
				prob = "CS32";
			} else {
				prob = "APM32";
			}
		}
	} else {
		// JEP106 not used. Legacy ASCII values are used. This should not be used
		// on new products. And this note was written in the ADI v5 specs.
		// The Only value I've been able to find is 0x41 for ARM.

		// The identity/contiuation code are not filled acoording the JEP106
		// According to speds, this is the legacy idenitification where
		// the Identity Code contains an ASCII value. On the HK32 we read
		// JEP106 = false / Identity = 0x55 / Continuation = 5
		// 0x55 corresponds with 'U'. This looks like this could be an ASCII Identifier.
		// However, if ASCII IDs are used, the expected Continuation would be 0, as
		// this field is "reserved, read as zero" when legacy ASCII IDs are used.

		// Even though these values are violating the specs, we can use
		// JEP106 = false, ID = 0x55, Cont = 5 to detect HK32.

		if (romtable_pid.identity_code == 0x55
				&& romtable_pid.continuation_code == 5) prob = "HK32";
	}


	sprintf(rt, "%s %s  V:%1d CONT:%3d ID:%3d PART: %3X REV:%3d ", prob,
			cpuid(), romtable_pid.jep106_used, romtable_pid.continuation_code,
			romtable_pid.identity_code, romtable_pid.partno,
			romtable_pid.revision);

}

int main() {
	parse_romtable();

	HAL_Init();
	ClockSetup();

	usbd_reenumerate();
	usbd_init();

	while (1)
		;;
}
