#include "usbd_stm.h"

void usbd_reenumerate() {

	//USB_DevDisconnect( USB_OTG_FS );
	//USB_DevConnect( USB_OTG_FS );

}

void Error_Handler() {
	__BKPT(0);
}

// HSE using 25 MHz XTAL
// SYS running at 84 MHZ
void SystemClock_HSE25_OUT84_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	__HAL_RCC_PWR_CLK_ENABLE();

	// Scale 3 <= 60 MHz
	// Scale 2 >  60 Mhz
	// We're about to configure 84 MHz, so we need scale 2 here.
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	// M = (Input Clock / PLMM) = 1 MHz (Using 25 MHz XTAL)
	// I'm keeping this one at 1 MHz, so the rest can be kept the same
	// N = M * 336 = 336 MHz
	// P = N / 4 = 84 MHz (=SYS Clock, Max 84 MHz)
	// Q = N / 7 = 48 MHz (=USB Clock, MUST be 48 MHz)
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	// See STM32F401 Reference Manual (RM0368) Page 95
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;  // 84/1=84 (Max 84 MHz)
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;	// 84/2=42 (Max 42 MHz)
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;	// 84/1=84 (Max 84 MHz)

	// See STM32F401 Reference Manual (RM0368) Page 46
	// Running at 84 Mhz at 3.3 volt gives us 2 Wait States
	// Be aware running at lower voltages required more wait states!
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}

	// Enable the Clock Security System. Please note when using external clock source
	// This can only be enabled once the oscillator is stable. Hence it is on the end.
	HAL_RCC_EnableCSS();
}


// HSI (running at 16 MHz)
// SYS running at 84 MHZ
void SystemClock_HSI_OUT84_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	__HAL_RCC_PWR_CLK_ENABLE();

	// Scale 3 <= 60 MHz
	// Scale 2 >  60 Mhz
	// We're about to configure 84 MHz, so we need scale 2 here.
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);


	// M = (Input Clock / PLMM) = 1 MHz  (Using 16 MHz HSI)
	// I'm keeping this one at 1 MHz, so the rest can be kept the same
	// N = M * 336 = 336 MHz
	// P = N / 4 = 84 MHz (=SYS Clock, Max 84 MHz)
	// Q = N / 7 = 48 MHz (=USB Clock, MUST be 48 MHz)
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	// See STM32F401 Reference Manual (RM0368) Page 95
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;  // 84/1=84 (Max 84 MHz)
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;	// 84/2=42 (Max 42 MHz)
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;	// 84/1=84 (Max 84 MHz)

	// See STM32F401 Reference Manual (RM0368) Page 46
	// Running at 84 Mhz at 3.3 volt gives us 2 Wait States
	// Be aware running at lower voltages required more wait states!
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}

	// Enable the Clock Security System. Not sure if this is effective on HSI though.
	HAL_RCC_EnableCSS();
}

void SystemClock_Config() {
	SystemClock_HSE25_OUT84_Config();
	//SystemClock_HSI_OUT84_Config();
}
int main() {
	HAL_Init();
	SystemClock_Config();
	SystemCoreClockUpdate();

	usbd_reenumerate();
	usbd_init();

	while (1)
		;;
}
