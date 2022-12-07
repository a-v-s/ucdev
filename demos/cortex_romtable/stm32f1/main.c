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


void parse_bootrom(){
	// System ROM starts at 0x1FFFF000
	// This contains some uart bootloader
	// at 0x1FFFF7E0 sits the flash size
	// at 0x1FFFF7E8 sits the UUID
	// Will calculate the CRC up to 0x1FFFF400
	// It seems some clones have copied ST's bootloader
	// That is nasty

	char *prob = "Unknown";
	 __HAL_RCC_CRC_CLK_ENABLE();
	CRC_HandleTypeDef crc_handle;
	crc_handle.Instance = CRC;
	HAL_CRC_Init(&crc_handle);
	// HAL_CRC_Accumulate length is in 32-bit words rather then 8-bit bytes
	uint32_t crc32 = HAL_CRC_Accumulate(&crc_handle, 0x1FFFF000, 0x100);
	switch (crc32) {
	case 0xda6104d0:
		prob = "STM32F103x6";
		break;
	case 0x27377129:
		prob = "STM32F103xB";
		// STM32, CS32, APM32
		if ( 0x0CF300FF==(*(int32_t*)(0x1FFFF7d0))) {
			// Seeing 0xFF 0xFF 0xFF 0xFF on STM
			// Seeing 0xFF 0x00 0xF3 0x0C on APM
			prob = "APM32";
		}
		break;
	case 0x1527d032:
		// GD32F101C6
		// GD32F103CB
		prob = "GD32F10x";
		break;
	case 0x52d42adb:
		prob = "HK32";
		break;
	case 0xdcbd2235:
		prob = "CH32";
		break;
	}

}


void parse_romtable() {

	intptr_t ROMTABLE = (intptr_t) (0xE00FF000);
	romtable_id_t *rid = (romtable_id_t*) (ROMTABLE | 0xFD0);
	romtable_pid_t romtable_pid = extract_romtable_pid(rid);

	char *prob = "Unknown";
//
//
//	uint32_t AHBENR_INIT = RCC->AHBENR;
//	uint32_t APB2ENR_INIT = RCC->APB2ENR;
//	uint32_t APB1ENR_INIT = RCC->APB1ENR;
//
//	RCC->AHBENR = -1;
//	RCC->APB2ENR = -1;
//	RCC->APB1ENR = -1;
//
//	uint32_t AHBENR_ALL = RCC->AHBENR;
//	uint32_t APB2ENR_ALL = RCC->APB2ENR;
//	uint32_t APB1ENR_ALL = RCC->APB1ENR;
//
//	RCC->AHBENR = AHBENR_INIT;
//	RCC->APB2ENR = APB2ENR_INIT;
//	RCC->APB1ENR = APB1ENR_INIT;


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

			switch((*(uint32_t*)(0x1FFFF7d0))) {
			case 0x0CF300FF:
				prob = "APM32";
				break;
			case 0xFFFFFFFF:
				switch((*(uint32_t*)(0x1FFFF000))) {
				case 0x200001fc:
					prob = "CS32";
					break;
				case 0x20000910:
					prob = "CH32";
					break;
				}
				break;
			}



			// This is the code for ARM
			// This encodes ARM Cortex-M3,
			// Thus... we don't know what we are running on

			// Now we have CH32 too, this ain't enough
//			// APM or CS
//			cortex_m_romtable_t *rom = (cortex_m_romtable_t*) (ROMTABLE);
//			if (rom->etm & 1) {
//				prob = "CS32";
//			} else {
//				prob = "APM32";
//			}

			// Thinking of detecting the presence of extra peripherals
			// We might try accessing them to see if they are present
			// We should activate their clocks before they are active
			// Setting reserved clock bits remain low, and such, trying
			// to enable them can be used to detect, if they are all unique.
			// I suppose, after enabling we should attempt to access the
			// enabled peripheral, as there might be more variants with
			// extra peripherals, or have reserved bits that do stick.
			// APM32 got an FPU peripheral
			// (RCC->AHBENR) BIT 3			0x40024000
			// CH32  got an extra USB controller "USBHD"
			// (RCC->AHBENR) BIT 12			0x40023800
			// How to identify CS32 ?? There is only some chinese datasheet
			// It seems to have no extra peripherals
			// at least, enabling all clocks gives the same results as an STM32
			// AHBENR_ALL	uint32_t	0x55 (Hex)
			// APB2ENR_ALL	uint32_t	0x5e7d (Hex)
			// APB1ENR_ALL	uint32_t	0x1ae64807 (Hex)

			// Also, more chips are coming up, we have to analyse them
			// when they arrive

//			uint32_t initial_val = RCC->AHBENR;
//			RCC->AHBENR = -1;
//			uint32_t all_on = RCC->AHBENR;
//			RCC->AHBENR = initial_val;
//
//
//			RCC->AHBENR |= (1<<3);
//			if ((1<<3)&RCC->AHBENR) {
//				// The bit sticks
//				prob = "APM32";
//			}
//			RCC->AHBENR=initial_val;
//
//
//			RCC->AHBENR |= (1<<12);
//			if ((1<<12)&RCC->AHBENR) {
//				// The bit sticks
//				prob = "CH32";
//			}
//			RCC->AHBENR=initial_val;




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

		// On the AIR103 we see the entire romtable_pid to be zeroed

		if (romtable_pid.identity_code == 0x55
				&& romtable_pid.continuation_code == 5) prob = "HK32";

		if (romtable_pid.identity_code == 0x00
				&& romtable_pid.continuation_code == 0) prob = "AIR32";
	}


	sprintf(rt, "%s %s  V:%1d CONT:%3d ID:%3d PART: %3X REV:%3d ", prob,
			cpuid(), romtable_pid.jep106_used, romtable_pid.continuation_code,
			romtable_pid.identity_code, romtable_pid.partno,
			romtable_pid.revision);

}

typedef void(*func)(void);


int main() {
	parse_romtable();
	parse_bootrom();

	HAL_Init();
	ClockSetup();

	//usbd_reenumerate();
	//usbd_init();

	while (1)
		;;
}
