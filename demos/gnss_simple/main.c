/*

 File: 		main.c
 Author:	André van Schoubroeck
 License:	MIT


 MIT License

 Copyright (c) 2017-2022 André van Schoubroeck <andre@blaatschaap.be>

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

#include <stdbool.h>
#include <string.h>
#include <stdfix.h>

#include "system.h"

#include "bshal_spim.h"
#include "bshal_delay.h"
#include "bshal_i2cm.h"
#include "bshal_uart.h"
#include "bshal_gpio.h"

#include "i2c.h"

#include "minmea.h"



bshal_i2cm_instance_t *gp_i2c = NULL;

void HardFault_Handler(void) {

}

void SysTick_Handler(void) {
	HAL_IncTick();
}

void SystemClock_Config(void) {
	ClockSetup_HSE8_SYS72();
}

void uart_gnss_cb(char *data, size_t size) {

	struct minmea_sentence_rmc rmc;
	enum minmea_sentence_id sentence_id = minmea_sentence_id(data, false);
	switch (sentence_id  ) {

	case MINMEA_INVALID:
		break;
	case MINMEA_UNKNOWN:
		break;
	case MINMEA_SENTENCE_RMC:

		static int cnt = 0;
		cnt++;
		char buff[32];
		sprintf(buff,"%d",cnt);
		print(buff,5);
		bool success = minmea_parse_rmc( &rmc, data);

		if (success) {
			float latitude= minmea_tocoord(&rmc.latitude);
			float longitude= minmea_tocoord(&rmc.longitude);
			sprintf(buff, "latitude:  %10.6f", latitude);
			print(buff,1);
			sprintf(buff, "longitude: %10.6f", longitude);
			print(buff,2);
		} else {
			print("no fix", 1);
		}

		break;
	case MINMEA_SENTENCE_GGA:
		// Default V.KEL
		//
		break;
	case MINMEA_SENTENCE_GSA:
		// Default V.KEL
		break;
	case MINMEA_SENTENCE_GLL:
		// Default V.KEL
		//
		break;
	case MINMEA_SENTENCE_GST:
		// Contains RMS
		break;
	case MINMEA_SENTENCE_GSV:
		// Default V.KEL
		//
		break;
	case MINMEA_SENTENCE_VTG:
		// Default V.KEL
		//
		break;
	case MINMEA_SENTENCE_ZDA:
		break;
	}
}

void uart_init(void) {
	//static uint8_t receive_buffer[512];
	static uint8_t receive_buffer[1024];
	static bshal_uart_async_t bshal_uart_async;
	static bshal_uart_instance_t bshal_uart_instance;


	//  Configuration for the Async handler, to configure the synchronosation
	bshal_uart_async.callback = uart_gnss_cb; // Callback for the resulting NMEA string

	bshal_uart_async.receive_buffer = receive_buffer;
	bshal_uart_async.receive_buffer_len = sizeof(receive_buffer) - 128;
	bshal_uart_async.process_buffer = receive_buffer + sizeof(receive_buffer) - 128;
	bshal_uart_async.process_buffer_len = 128;


	bshal_uart_async.null_terminated_string = true; // Terminate the resulting string

	bshal_uart_async.sync_begin_data = "$";	// NMEA sentences start with $
	bshal_uart_async.sync_begin_len = 1;    //
	bshal_uart_async.sync_begin_include = true; // Include the $ in the result

	bshal_uart_async.sync_end = "\r\n";     // NMEA sentences end with \r\n
	bshal_uart_async.sync_end_len = 2;
	bshal_uart_async.sync_end_include = true; // Do include the \r\n in the result

	bshal_uart_async.max_data_len = 83; // The maximum length of an NMEA string

	bshal_uart_instance.async = & bshal_uart_async; // Asign the async handler to the uart instance



	// 9600,8,N,1
	bshal_uart_instance.bps = 9600;
	bshal_uart_instance.data_bits = 8;
	bshal_uart_instance.parity = bshal_uart_parity_none;
	bshal_uart_instance.stop_bits = 1;

	bshal_uart_instance.fc = bshal_uart_flow_control_none;

	bshal_uart_instance.hw_nr = 2;  // UASRT 2
	bshal_uart_instance.cts_pin = -1; // No flow control
	bshal_uart_instance.rts_pin = -1; // No flow control
	bshal_uart_instance.rxd_pin = bshal_gpio_encode_pin(GPIOA, 3); // PA3
	bshal_uart_instance.txd_pin = bshal_gpio_encode_pin(GPIOA, 2); // PA2

	bshal_stm32_uart_init(&bshal_uart_instance);


}

int main() {
#ifdef SEMI
	initialise_monitor_handles();
	printf("Hello world!\n");
#endif

	
	SystemClock_Config();
	SystemCoreClockUpdate();

	HAL_Init();

	bshal_delay_init();
	bshal_delay_us(10);

	gp_i2c = i2c_init();

	uart_init();

	display_init();
	draw_background();
	print("GNSS DEMO", 0);


	while (1) {
		framebuffer_apply();
		bshal_delay_ms(1000);
	}

}
