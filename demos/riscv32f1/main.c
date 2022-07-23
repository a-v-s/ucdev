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

void __attribute__ ((weak)) _exit(int i){
	while(1);
}


void NMI_Handler(void){}
void HardFault_Handler(void){}
void SysTick_Handler(void){}
void SW_handler(){}

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


#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) ({ \
  if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
    asm volatile ("csrw " #reg ", %0" :: "i"(val)); \
  else \
    asm volatile ("csrw " #reg ", %0" :: "r"(val)); })

#define swap_csr(reg, val) ({ unsigned long __tmp; \
  if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
    asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "i"(val)); \
  else \
    asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "r"(val)); \
  __tmp; })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)




#define UART
#ifdef UART

// I guess we need nosys, but with it, riscv won't call _write
// without it, we need to implement a bunch of stuff, including _sbrk
// to make malloc work... but still no call to _write


//#include "uart.h"
#include "stm32f1xx_hal_uart.h"
#include <stdio.h>
#include <stdlib.h>
UART_HandleTypeDef huart1;
void initialise_uart(){
    __HAL_RCC_USART1_CLK_ENABLE();


    /**
     * USART1 GPIO Configuration
     * PB6     ------> USART1_TX
     * PB7     ------> USART1_RX
     */
    /* Peripheral clock enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin =  GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	GPIO_InitStruct.Pin =  GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);
}

__attribute__((used)) int _write  (int fd, char * ptr, int len) {
  HAL_UART_Transmit(&huart1, (uint8_t *) ptr, len, HAL_MAX_DELAY);
  return len;
}


int _read(int fd, char* ptr, int len) {
    HAL_StatusTypeDef hstatus;

	hstatus = HAL_UART_Receive(&huart1, (uint8_t *) ptr, 1, HAL_MAX_DELAY);
	if (hstatus == HAL_OK)
		return 1;
	else
		//return EIO;
		return 0;

}



#endif


int main(void) {
	initialise_uart();
	int t = rdtime();
	while (1) {
		printf("Blaat blaat blaat!");
	}
}

int _sbrk(){return 0;}

