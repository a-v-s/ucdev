/*
 * radio_test.c
 *
 *  Created on: 4 okt. 2022
 *      Author: andre
 */

#include "bshal_spim.h"
#include "bshal_i2cm.h"
#include "bshal_delay.h"

#include "system.h"
#include <endian.h>

static bshal_spim_instance_t radio_spi_config;

#pragma pack(push,1)
typedef struct {
	unsigned int fb :5;
	unsigned int hbsel :1;
	unsigned int sbsel :1;
	unsigned int :1;
} si443x_reg_75_t;
#pragma pack(pop)

int si443x_set_frequency(uint32_t kHz) {
	int fb, fc, hbsel;

	if (kHz < 240000) {
		// Out of range
		return -1;
	}
	if (kHz > 960000) {
		// Out of range
		return -1;
	}

	if (kHz < 480000) {
		// Low Band
		fb = (kHz - 240000) / 10000;
		fc = (float) (kHz % 10000) / 0.15625f;
		hbsel = 0;
	} else {
		// High Band
		fb = (kHz - 480000) / 20000;
		fc = (float) (kHz % 20000) / 0.3125f;
		hbsel = 1;
	}

	// fcarrier = (fb+24+(fc+fo)/64000) x 10000 x (hbsel+1) + (fhch x fhs x 10) [kHz],
	//float calc_freq = (((fb + 24.0f) + (fc / 64000.0f)) * 10000.0f ) * (hbsel + 1.0f);
	//printf("Requested frequency: %9d KHz Band %04X fc %02X High %d Actual Freq %9f KHz\n", kHz, fb, fc, hbsel, calc_freq);

	si443x_reg_75_t r75 = { 0 };
	r75.fb = fb;
	r75.hbsel = hbsel;
	r75.sbsel = 1;

	uint8_t reg = 0x75 | 0x80;
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
	bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
	bshal_spim_transmit(&radio_spi_config, &r75, 1, true);
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);

	uint16_t r76 = htobe16(fc);
	reg = 0x76 | 0x80;
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
	bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
	bshal_spim_transmit(&radio_spi_config, &r76, 2, true);
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);

	return 0;
}

void radio_spi_init(void) {

	radio_spi_config.frequency = 10000000; // MAX SPI speed for Si443x = 10 MHz
	//radio_spi_config.frequency = 1000000;
	radio_spi_config.bit_order = 0; //MSB
	radio_spi_config.mode = 0;

	radio_spi_config.hw_nr = 1;
	radio_spi_config.sck_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_5);
	radio_spi_config.miso_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_6);
	radio_spi_config.mosi_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_7);

	radio_spi_config.cs_pin = bshal_gpio_encode_pin(GPIOA, GPIO_PIN_4);
	radio_spi_config.rs_pin = bshal_gpio_encode_pin(GPIOB, GPIO_PIN_10);
	radio_spi_config.rs_pol = 1;

	bshal_spim_init(&radio_spi_config);

}

void test_recv() {
	uint8_t reg;
	uint8_t val;
	uint8_t buffer[255];

	while (1) {

		// Clear fifo
		reg = 0x08 | 0x80;
		val = 0x02;
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		//bshal_delay_ms(1);
		reg = 0x08 | 0x80;
		val = 0x00;
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		//bshal_delay_ms(1);


		// start reception
		reg = 0x07 | 0x80 ;
		val = 0x04;
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		//bshal_delay_ms(1);

		// read interrupt, should read transmission done
		val = 0x00;
		reg = 0x03;
		while (!(val & 0b10)) {
			bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
			bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
			bshal_spim_receive(&radio_spi_config, &val, 1, true);
			bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		}
		// packet received


		val = 0x00;
		reg = 0x4B; // received packet size
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_receive(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);

		memset(buffer,0,sizeof(buffer));
		reg = 0x7F; // fifo
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_receive(&radio_spi_config, buffer, val, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);

	}

}

void test_send() {
	uint8_t reg;
	uint8_t val;
	uint8_t data[64];
	int tx_count = 0;
	while (1) {

		// Clear fifo
		reg = 0x08 | 0x80;
		val = 0x01;
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		//bshal_delay_ms(1);
		reg = 0x08 | 0x80;
		val = 0x01;
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		//bshal_delay_ms(1);


		sprintf(data, "Tx %5d", tx_count++);
		reg = 0x3e | 0x80;
		val = strlen(data);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
//		//bshal_delay_ms(1);

		reg = 0x7F | 0x80; // Fifo Data

		// write
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, data, val, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);





		//bshal_delay_ms(1);

		// start transmission
		reg = 4 | 0x80 ;
		val = 0x08 ;
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
		bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
		bshal_spim_transmit(&radio_spi_config, &val, 1, true);
		bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		//bshal_delay_ms(1);

		// read interrupt, should read transmission done
		val = 0x00;
		reg = 0x03;
		while (!(val & 0b100)) {
			bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
			bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
			bshal_spim_receive(&radio_spi_config, &val, 1, true);
			bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
		}

		static int delay = 1000;
		bshal_delay_ms(delay);
	}
}
void test_radio() {
	uint8_t reg;
	uint8_t val;

	bshal_gpio_write_pin(radio_spi_config.rs_pin, 1);
	bshal_delay_ms(5);
	bshal_gpio_write_pin(radio_spi_config.rs_pin, 0);
	bshal_delay_ms(20);

	// Test for device
	reg = 0x00;
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
	bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
	bshal_spim_receive(&radio_spi_config, &val, 1, true);
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
	//bshal_delay_ms(1);

	reg = 0x01;
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
	bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
	bshal_spim_receive(&radio_spi_config, &val, 1, true);
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
	//bshal_delay_ms(1);

	reg = 0x71 | 0x80;
	val = 0b00100011; //GFSK, FIFO

	// write
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
	bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
	bshal_spim_transmit(&radio_spi_config, &val, 1, true);
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
	//bshal_delay_ms(1);

// Default value is not defined in the datasheet???
//	reg = 0x32 | 0x80;
//	val = 0b0;
//	// write
//	bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
//	bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
//	bshal_spim_transmit(&radio_spi_config, &val, 1, true);
//	bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);
//	//bshal_delay_ms(1);



	reg = 0x05 | 0x80;
	val = 0x06; //Enable Interrupts

	// write
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 0);
	bshal_spim_transmit(&radio_spi_config, &reg, 1, true);
	bshal_spim_transmit(&radio_spi_config, &val, 1, true);
	bshal_gpio_write_pin(radio_spi_config.cs_pin, 1);


	//si443x_set_frequency(868000);
	si443x_set_frequency(434000);


}

void main(void) {
	bshal_delay_init();
	radio_spi_init();
	test_radio();

	bool dir = false;
	;

	if (dir)
		test_send();
	else
		test_recv();

}
