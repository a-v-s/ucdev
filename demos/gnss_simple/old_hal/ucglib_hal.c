/*
 * ucglib_hal.c
 *
 *  Created on: 21 okt. 2020
 *      Author: andre
 */

#include "ucglib_hal.h"

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"

static SPI_HandleTypeDef m_spi_handle;

//#define CS_PIN 		GPIO_PIN_2
//#define CD_PIN 		GPIO_PIN_1
//#define RESET_PIN 	GPIO_PIN_0

#define CS_PIN 		GPIO_PIN_4

#define CD_PIN GPIO_PIN_0

#define RESET_PIN GPIO_PIN_1

int16_t ucg_com_stm32f1(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data) {

	switch (msg) {
	case UCG_COM_MSG_POWER_UP:
		/* "data" is a pointer to ucg_com_info_t structure with the following information: */
		/*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
		/*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
		/* "arg" is not used */

		/* This message is sent once at the uC startup and for power up. */
		/* setup i/o or do any other setup */

		if (((ucg_com_info_t*) data)->serial_clk_speed) {

			__HAL_RCC_SPI1_CLK_ENABLE();
			__HAL_RCC_GPIOA_CLK_ENABLE();
			__HAL_RCC_GPIOB_CLK_ENABLE();

			m_spi_handle.Init.Mode = SPI_MODE_MASTER;
			m_spi_handle.Init.Direction = SPI_DIRECTION_1LINE;
			//m_spi_handle.Init.Direction = SPI_DIRECTION_2LINES;
			m_spi_handle.Init.DataSize = SPI_DATASIZE_8BIT;

			// I assume mode 0
			m_spi_handle.Init.CLKPolarity = SPI_POLARITY_LOW;
			m_spi_handle.Init.CLKPhase = SPI_PHASE_1EDGE;

			// The ucglib controls the line itself
			m_spi_handle.Init.NSS = SPI_NSS_SOFT;

			// We'll need to do speed calculations later
			//m_spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
			m_spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;

			// What is the default?
			m_spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;

			m_spi_handle.Init.TIMode = SPI_TIMODE_DISABLE;

			m_spi_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;

			m_spi_handle.Init.CRCPolynomial = 0;

			m_spi_handle.Instance = SPI1;

			int res = HAL_SPI_Init(&m_spi_handle);
			if (res)
				__BKPT(0);

			GPIO_InitTypeDef GPIO_InitStruct;

			// Common configuration for all channels
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

			// Configure the SPI pins
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_5;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

			GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
			GPIO_InitStruct.Pin = GPIO_PIN_6;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

			// Configure the output pins controlled by the lib
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pin = CS_PIN;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

			GPIO_InitStruct.Pin = RESET_PIN | CD_PIN;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		} else if (((ucg_com_info_t*) data)->parallel_clk_speed) {
			// We have some parallel connection
		}
		break;

	case UCG_COM_MSG_POWER_DOWN:
		/* "data" and "arg" are not used*/
		/* This message is sent for a power down request */

		// TODO
		break;
	case UCG_COM_MSG_DELAY:
		/* "data" is not used */
		/* "arg" contains the number of microseconds for the delay */
		/* By receiving this message, the following code should delay by */
		/* "arg" microseconds. One microsecond is 0.000001 second */

		// DONE
		if (arg > 999)
			HAL_Delay(arg / 1000); // unit of HAL_Delay????

		else
			for (int i = 0; i < arg * 72; i++)
				__NOP();

		break;
	case UCG_COM_MSG_CHANGE_RESET_LINE:
		/* "data" is not used */
		/* "arg" = 1: set the reset output line to 1 */
		/* "arg" = 0: set the reset output line to 0 */

		HAL_GPIO_WritePin(GPIOB, RESET_PIN, arg);

		break;
	case UCG_COM_MSG_CHANGE_CD_LINE:
		/* "ucg->com_status"  bit 0 contains the old level for the CD line */
		/* "data" is not used */
		/* "arg" = 1: set the command/data (a0) output line to 1 */
		/* "arg" = 0: set the command/data (a0) output line to 0 */

		HAL_GPIO_WritePin(GPIOB, CD_PIN, arg);

		break;
	case UCG_COM_MSG_CHANGE_CS_LINE:
		/* "ucg->com_status"  bit 1 contains the old level for the CS line */
		/* "data" is not used */
		/* "arg" = 1: set the chipselect output line to 1 */
		/* "arg" = 0: set the chipselect output line to 0 */

		HAL_GPIO_WritePin(GPIOA, CS_PIN, arg);
		break;
	case UCG_COM_MSG_SEND_BYTE:
		/* "data" is not used */
		/* "arg" contains one byte, which should be sent to the display */
		/* The current status of the CD line is available */
		/* in bit 0 of u8g->com_status */
	{
		int res = HAL_SPI_Transmit(&m_spi_handle, &arg, 1, 1000);
		if (res)
			__BKPT(0);
	}
		break;
	case UCG_COM_MSG_REPEAT_1_BYTE:
		/* "data[0]" contains one byte */
		/* repeat sending the byte in data[0] "arg" times */
		/* The current status of the CD line is available */
		/* in bit 0 of u8g->com_status */
		arg++;

		{
			uint8_t buff[arg + 1];
			memset(buff, data[0], arg);
			int res = HAL_SPI_Transmit(&m_spi_handle, buff, arg, 1000);
			if (res)
				__BKPT(0);
		}

		break;
	case UCG_COM_MSG_REPEAT_2_BYTES:

		/* "data[0]" contains first byte */
		/* "data[1]" contains second byte */
		/* repeat sending the two bytes "arg" times */
		/* The current status of the CD line is available */
		/* in bit 0 of u8g->com_status */

		//if (!arg) arg=1;//break; // we can get requests of 0 repeats?!?
		arg++;

		{
			uint8_t buff[2 * arg];
			for (int i = 0; i < arg; i++) {
				buff[2 * i + 0] = data[0];
				buff[2 * i + 1] = data[1];
			}

			int res = HAL_SPI_Transmit(&m_spi_handle, buff, 2 * arg, 1000);
			if (res)
				__BKPT(0);
		}

		break;
	case UCG_COM_MSG_REPEAT_3_BYTES:
		/* "data[0]" contains first byte */
		/* "data[1]" contains second byte */
		/* "data[2]" contains third byte */
		/* repeat sending the three bytes "arg" times */
		/* The current status of the CD line is available */
		/* in bit 0 of u8g->com_status */
		//if (!arg) arg=1;//break; // we can get a request for zero times ?!?!?
		arg++;
		{
			uint8_t buff[3 * arg];
			for (int i = 0; i < arg; i++) {
				buff[3 * i + 0] = data[0];
				buff[3 * i + 1] = data[1];
				buff[3 * i + 2] = data[2];
			}

			int res = HAL_SPI_Transmit(&m_spi_handle, buff, 3 * arg, 1000);
			//if (res) __BKPT(0);
		}

		break;
	case UCG_COM_MSG_SEND_STR:
		/* "data" is an array with "arg" bytes */
		/* send "arg" bytes to the display */
	{
		int res = HAL_SPI_Transmit(&m_spi_handle, data, arg, 1000);
		if (res)
			__BKPT(0);
	}
		break;
	case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
		/* "data" is a pointer to two bytes, which contain the cd line */
		/* status and display data */
		/* "arg" contains the number of these two byte tuples which need to */
		/* be analysed and sent. Bellow is a example sequence */
		/* The content of bit 0 in u8g->com_status is undefined for this message */

		while (arg > 0) {
			if (*data != 0) {
				if (*data == 1) {
					/* set CD (=D/C=A0) line to low */
					HAL_GPIO_WritePin(GPIOB, CD_PIN, 0);
				} else {
					/* set CD (=D/C=A0) line to high */
					HAL_GPIO_WritePin(GPIOB, CD_PIN, 1);
				}
			}
			data++;
			/* send *data to the display */
			data++;
			arg--;
		}
		break;
	}
	return 1;
}
