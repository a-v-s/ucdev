#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include <ch32v10x_gpio.h>
#include <ch32v10x_rcc.h>
#include <debug.h>



#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })


int unidelay(uint32_t delay) {
	int blaat = read_csr(mcycle);
	blaat += delay * (SystemCoreClock / 1000);
	while (read_csr(mcycle) < blaat);
	return read_csr(mcycle);
}

int main(void) {
	Delay_Init();

    int marchid = read_csr(marchid);
    int mvendorid = read_csr(mvendorid);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef init_pin = { .GPIO_Pin = GPIO_Pin_0, .GPIO_Speed =
			GPIO_Speed_2MHz, .GPIO_Mode = GPIO_Mode_Out_PP, };

	GPIO_Init(GPIOA, &init_pin);

	int i = 0;
	while (1) {
		i++;
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, i%2);
		if (0x31e== mvendorid)
			unidelay(333);
		else
			Delay_Ms(333);

	}
}
