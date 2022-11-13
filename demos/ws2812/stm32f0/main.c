/*

 File: 		main.c
 Author:	André van Schoubroeck
 License:	MIT


 MIT License

 Copyright (c) 2017, 2018, 2019, 2020, 2022 André van Schoubroeck <andre@blaatschaap.be>

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

#include <system.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

uint8_t ws2812_data[2432];
volatile bool buffer_state[3];
volatile bool timer_state[3];

void ClockSetup_HSE8_SYS48(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	// Configure HSE Oscillator for use with 8 MHz Xtal
	// PLL Freq 48 MHz	( 6 * 8 = 48 )
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

	// Enable Power Controller clock
	__HAL_RCC_PWR_CLK_ENABLE();
}

void ws2812_tim3_init() {

	GPIO_InitTypeDef GPIO_InitStruct;

	// Common configuration for all channels
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Alternate = 1;

	// Enable Timer 3 Clock
	__HAL_RCC_TIM3_CLK_ENABLE();

	// Enable GPIO Port A Clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Pins for timer 3

	GPIO_InitStruct.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void ws2812_init2(DMA_Channel_TypeDef *dma, TIM_TypeDef *tim) {
	dma->CPAR = (uint32_t) & (tim->DMAR); // Link DMA channel to timer

	dma->CCR = 0x00;
	dma->CCR |= (0x01 << DMA_CCR_PSIZE_Pos); // Peripheral size 16 bit
	dma->CCR |= (0x00 << DMA_CCR_MSIZE_Pos); // Memory size 8 bit
	dma->CCR |= (0x1 << DMA_CCR_DIR_Pos);   // Memory to Peripheral
	dma->CCR |= (0x1 << DMA_CCR_MINC_Pos);   // Memory increasement
	dma->CCR |= (0x0 << DMA_CCR_PINC_Pos);  // Peripheral increasement
	dma->CCR |= (0x0 << DMA_CCR_CIRC_Pos);   // Circular mode
	dma->CCR |= DMA_CCR_TCIE; // Enable transfer complete interrupt

	dma->CCR |= DMA_CCR_TEIE; // Enable transfer error interrupt

	// I have used these values in the old code. However, I can't derive them
	// 72 MHz / (9+1) = 7.2 MHz
	// 7.2 MHz / 8 = 900 kHz.
	// We should have 800 kHz, shouldn't we? So why did this work?
	//tim->PSC = 9; // Prescaler. 
	//tim->ARR = 8; // Reload Value

	// We need to generate a signal on 800 kHz
	//tim->PSC = 8; // Prescaler: 72 MHZ / (8+1) = 8 MHz

	// Calculate the prescaler by reading the current core speed rather then
	// assuming its configured to 72 MHz
	tim->PSC = (SystemCoreClock / 8000000) - 1;
	tim->ARR = 10 - 1; // Reload Value 8 MHz / 10 = 800 kHz

	// DMA will be configured when we initiate a transfer. At this point,
	// clear all DMA related settings

	// Disable DMA.
	tim->DIER = 0;
	// Clear DMA settings.
	tim->DCR = 0;

	// Configure each channel for PWM
	tim->CCMR1 = 0;
	tim->CCMR1 |= (0b110 << TIM_CCMR1_OC1M_Pos); // pwm mode 1
	tim->CCMR1 |= (0b110 << TIM_CCMR1_OC2M_Pos); // pwm mode 1

	tim->CCMR2 = 0;
	tim->CCMR2 |= (0b110 << TIM_CCMR2_OC3M_Pos); // pwm mode 1
	tim->CCMR2 |= (0b110 << TIM_CCMR2_OC4M_Pos); // pwm mode 1

	tim->CCMR1 |= TIM_CCMR1_OC1PE; // output compare preload enable
	tim->CCMR1 |= TIM_CCMR1_OC2PE; // output compare preload enable

	tim->CCMR2 |= TIM_CCMR2_OC3PE; // output compare preload enable
	tim->CCMR2 |= TIM_CCMR2_OC4PE; // output compare preload enable

	// Set Output Enable for all Channels
	tim->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;

	tim->CR1 |= 1 << 7; // auto reload enable
	tim->CR1 &= ~(0b1110000); // Edge aglined, upcounting
	tim->CR1 |= 0b100; // Event source, only over/underflow
}

void DMA1_Channel2_3_IRQHandler(void) {
	DMA1->IFCR = DMA1->ISR;
	DMA1_Channel3->CCR &= ~1; // Disable DMA

	// Resetting channel state
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;

	TIM3->RCR = 32; // Keep reset time for 32 bits 
	TIM3->DIER = TIM_DIER_UIE; // Update Interrupt Enable

	__disable_irq();
	buffer_state[0] = false;
	__enable_irq();

}

void TIM3_IRQHandler(void) {
	timer_state[1] = false;
	TIM3->DIER = 0;
}

void ws2812_apply(size_t size) {
	//memset(ws2812_data+ (size*8),0,32); // extra reset
	ws2812_start_dma_transer2(ws2812_data, 32 + (size * 8), DMA1_Channel3,
			TIM3);
}

void ws2812_apply_channel(size_t size, int channel) {
	DMA_Channel_TypeDef *dma;
	TIM_TypeDef *tim;

	dma = DMA1_Channel3;
	tim = TIM3;

	ws2812_set_xchannels(tim, channel % 4, 1);
	memset(ws2812_data + (size * 8), 0, 32); // extra reset
	ws2812_start_dma_transer2(ws2812_data, 32 + (size * 8), dma, tim);

}

void ws2812_set_xchannels(TIM_TypeDef *tim, int firstChannel, int nrChannels) {
	if (firstChannel + nrChannels <= 4) {
		tim->CR1 &= ~0x0001; // disable
		__DSB();
		tim->DCR &= ~TIM_DCR_DBA_Msk;
		tim->DCR |= ((13 + firstChannel) << TIM_DCR_DBA_Pos); // DMA Transfer Base address CCR1 + channel (0-3)
		tim->DCR &= ~TIM_DCR_DBL_Msk;
		tim->DCR |= ((nrChannels - 1) << TIM_DCR_DBL_Pos); // nr of transfers a time (CCR1 to CCR4)
		tim->CR1 |= 0x0001; // enable
		__DSB();
	}
}

void ws2812_start_dma_transer2(void *memory, size_t size,
		DMA_Channel_TypeDef *dma, TIM_TypeDef *tim) {

	__disable_irq();
	buffer_state[0] = true;
	__enable_irq();

	tim->DIER = TIM_DIER_UDE; // Update DMA Request Enable
	dma->CNDTR = size;
	dma->CMAR = (uint32_t) memory;
	tim->CCMR1 |= 1; // enable timer
	dma->CCR |= 1; // Enable DMA
	tim->EGR = TIM_EGR_UG; // Trigger update event, starting the transfer
}

#pragma pack(push,1)
typedef struct {
	uint8_t g;
	uint8_t r;
	uint8_t b;
} rgb_t;
#pragma pack(pop)

// https://blog.adafruit.com/2012/03/14/constant-brightness-hsb-to-rgb-algorithm/
void hsb2rgbAN2(uint16_t index, uint8_t sat, uint8_t bright, rgb_t *color) {
	uint8_t temp[5], n = (index >> 8) % 3;
// %3 not needed if input is constrained, but may be useful for color cycling and/or if modulo constant is fast
	uint8_t x = ((((index & 255) * sat) >> 8) * bright) >> 8;
// shifts may be added for added speed and precision at the end if fast 32 bit calculation is available
	uint8_t s = ((256 - sat) * bright) >> 8;
	temp[0] = temp[3] = s;
	temp[1] = temp[4] = x + s;
	temp[2] = bright - x;
	color->r = temp[n + 2];
	color->g = temp[n + 1];
	color->b = temp[n];
}

void SysTick_Handler() {
	HAL_IncTick();
}

int main() {
	ClockSetup_HSE8_SYS48();
	SystemCoreClockUpdate();

	RCC->AHBENR |= RCC_AHBENR_DMA1EN; // enable dma1 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // enable timer3 clock

	ws2812_tim3_init();
	ws2812_init2(DMA1_Channel3, TIM3);

	NVIC_ClearPendingIRQ(DMA1_Channel2_3_IRQn);
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

	NVIC_ClearPendingIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);

	ws2812_set_xchannels(TIM3, 0, 1);

	rgb_t leds[100];
	for (int i = 0; i < 100; i++) {
		hsb2rgbAN2(7 * i, 255, 4, leds + i);
	}

//		memset(leds, 0x04, sizeof(leds));
//
//		for (int i = 0; i < 97; i+=3) {
//			leds[i].r=leds[i].g=leds[i].b=3;
//			leds[i].r= 0;
//
//			leds[i+1].r=leds[i+1].g=leds[i+1].b=3;
//			leds[i+1].b= 0;
//
//			leds[i+2].r=leds[i+2].g=leds[i+2].b=3;
//			leds[i+2].g= 0;
//		}

	ws2812_fill_buffer_decompress(0, sizeof(leds), leds);
	ws2812_apply(sizeof(leds));

	while (1) {
		ws2812_fill_buffer_decompress(0, sizeof(leds), leds);
		ws2812_apply(sizeof(leds));
		rgb_t temp = leds[0];
		for (int i = 0; i < 99; i++) {
			leds[i] = leds[i + 1];
		}
		leds[99] = temp;
		//bshal_delay_ms(25);

	}

}
