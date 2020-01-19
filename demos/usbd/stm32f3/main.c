#include "usbd_stm.h"



void usbd_reenumerate(){
 // TODO
}


void SystemClock_Config(void)
{
// TODO
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
