/*
 * pinout.h
 *
 *  Created on: 1 feb. 2020
 *      Author: andre
 */

#ifndef STM32F1_PINOUT_H_
#define STM32F1_PINOUT_H_



// Pinout for Black Magic Probe
#define JTAG_PORT 		GPIOA
#define TDI_PORT		JTAG_PORT
#define TMS_DIR_PORT	JTAG_PORT
#define TMS_PORT		JTAG_PORT
#define TCK_PORT		JTAG_PORT
#define TDO_PORT		JTAG_PORT
#define TMS_DIR_PIN		GPIO_PIN_1

#define TDI_PIN			GPIO_PIN_3
#define TMS_PIN			GPIO_PIN_4
#define TCK_PIN			GPIO_PIN_5
#define TDO_PIN			GPIO_PIN_6

#define SWDIO_DIR_PORT	JTAG_PORT
#define SWDIO_PORT 		JTAG_PORT
#define SWCLK_PORT 		JTAG_PORT
#define SWD_PORT		JTAG_PORT
#define SWDIO_DIR_PIN	TMS_DIR_PIN
#define SWDIO_PIN		TMS_PIN
#define SWCLK_PIN		TCK_PIN

#define TRST_PORT		GPIOB
#define TRST_PIN		GPIO_PIN_1
#define PWR_BR_PORT		GPIOB
#define PWR_BR_PIN		GPIO_PIN_1
#define SRST_PORT		GPIOA
#define SRST_PIN		GPIO_PIN_2
#define SRST_SENSE_PORT	GPIOA
#define SRST_SENSE_PIN	GPIO_PIN_7

#endif /* STM32F1_PINOUT_H_ */
