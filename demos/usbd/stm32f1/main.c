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
	//ClockSetup_HSE8_SYS72();
	ClockSetup_HSE8_SYS48();
	//ClockSetup_HSI_SYS48();
}

char rt[128];

void stm_romtable() {

	intptr_t ROMTABLE = (intptr_t) (0xE00FF000);

	// ID080813 // PAGE 202
	// So, now I understand how to interpret the ROM Table
	// The ARMv7 TRM just says, these are the values,
	// and the peripheral exists at some address
	// But the ARM Debug Interface 	Architecture Specification (ID080813)
	// Actually explains the values. Which part is the offset, and then
	// I add the offset to the address of the current table and I find another entry
	//--
	// And how I know too what the CID in the romtable id is

	/*
	 cpuid_t *cpuid = (cpuid_t*) (&SCB->CPUID);

	 intptr_t ROMTABLE = NULL;


	 // Looking at the Cortex-M TRM, it seems it should always be
	 // at 0xE00FF000, so where is the 0xF00FF000 address
	 // coming from we've seen at PSoC and nRF ?????
	 switch (cpuid->Architecture) {
	 case 0xC:
	 // ARMV6m
	 ROMTABLE = (intptr_t) (0xE00FF000);
	 // ID051917 page 282
	 break;
	 case 0xf:
	 // Other, assume ARMv7m
	 ROMTABLE = (intptr_t) (0xE00FF000);
	 // ID120114 page 741
	 break;
	 }
	 */
	/*
	 * int *pid = (int*) (0xE00FFFE0);
	 int *pid = (int *) (ROMTABLE | 0xFE0);

	 bool used = pid[2] & 8;
	 uint8_t identity_code = ((pid[1] & 0xf0) >> 4) | ((pid[2] & 0x7) << 4);
	 uint8_t continuation_code = (*(int*) (0xE00FFFD0)) & 0xF;

	 sprintf(rt, "%sRT USED:%1d CONT:%3d ID:%3d", cpuid(), used,	continuation_code, identity_code);
	 */

	// These parts have been tested before
	// stm32: id = 32, cont = 0 "STMicroelectronics"
	// gd32:  id = 81, cont = 7 "GigaDevice Semiconductor (Beijing) Inc."
	// These are the new parts
	// apm32: id = 59, cont = 4 "ARM Ltd."
	// cs32:  id = 59, cont = 4 "ARM Ltd."
	// We can read this value on stm32, cs32, (gd and apm still need to be tested)
	// So, we can determine what core we're running on. We still need to find
	// a way to tell apm32 and cs32 apart.

	romtable_id_t *rid = (romtable_id_t*) (ROMTABLE | 0xFD0);

	bool jep106_used = (rid->pid2 & (1 << 3)) == (1 << 3);
	int continuation_code = rid->pid4 & 0xF;
	int identity_code = ((rid->pid1 & 0xf0) >> 4) | ((rid->pid2 & 0x7) << 4);
	int partno = rid->pid0 | ((rid->pid1 & 0xF) << 8);
	int revision = (rid->pid3 & 0x0F) >> 4;
	int modified = (rid->pid3 & 0xF);

	int _4kcount = (rid->pid4 & 0xF0) >> 4; // always 0b0000 ?
	//https://developer.arm.com/docs/103489663/10/peripheralid-values-for-the-coresight-rom-table

	char *prob = "Unknown";
	if (identity_code == 32 && continuation_code == 0) {
		prob = "STM32";
	}
	if (identity_code == 81 && continuation_code == 7) {
		prob = "GD32";
	}
	if (identity_code == 59 && continuation_code == 4) {
		// APM or CS
		romtable_t *rom = (romtable_id_t*) (ROMTABLE);
		if (rom->etm & 1) {
			prob = "CS32";
		} else {
			prob = "APM32";
		}
	}

	sprintf(rt, "%s %s  V:%1d CONT:%3d ID:%3d PART: %3X REV:%3d ", prob,
			cpuid(), jep106_used, continuation_code, identity_code, partno,
			revision);

}

int main() {
	//cpuid();
	stm_romtable();

	HAL_Init();
	ClockSetup();

	usbd_reenumerate();
	usbd_init();

	while (1)
		;;
}
