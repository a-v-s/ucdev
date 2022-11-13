#include "timer.h"
#include <system.h>

TIM_HandleTypeDef TimHandle;

volatile static uint16_t m_overflows = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { m_overflows++; }

void TIM4_IRQHandler(void) { HAL_TIM_IRQHandler(&TimHandle); }

void timer_init(void) {
  __HAL_RCC_TIM4_CLK_ENABLE();

  uint32_t prescaler_value = (uint32_t)(SystemCoreClock / 1000000) - 1;

  TimHandle.Instance = TIM4;

  TimHandle.Init.Period = 0xFFFF;
  TimHandle.Init.Prescaler = prescaler_value;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TimHandle.Init.RepetitionCounter = 0;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  HAL_TIM_Base_Init(&TimHandle);
  HAL_TIM_Base_Start_IT(&TimHandle);

  NVIC_EnableIRQ(TIM4_IRQn);
}

uint32_t get_time_us(void) { return (TIM4->CNT) | (m_overflows << 16); }
