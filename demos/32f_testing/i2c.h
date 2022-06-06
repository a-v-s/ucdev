/*
 * i2c.h
 *
 *  Created on: 9 aug. 2021
 *      Author: andre
 */

#ifndef I2C_H_
#define I2C_H_

//#define ADXL345_ADDR		0x1D	// Accelerometer
#define ADXL345_ADDR		0x53	// Accelerometer
#define	PCF8574T_ADDR		0x20	// I/O Expander
#define BH1750_ADDR			0x23	// Light Sensor
#define MFRC522_ADDR 		0x28	// RFID
#define SSD1306_ADDR		0x3C	// Displau
#define SHT3X_ADDR 			0x44	// Temp + Humidity
#define	LM75B_ADDR			0x48	// Temp TODO fix address
#define EEPROM_ADDR			0x50


#define LIS3DH_ADDR			0x18	// Accelerometer
#define PN532_ADDR			0x24	// RFID
//#define SSD1306_ADDR		0x3C	// Displau
#define SI7021_ADDR			0x40	//
//#define EEPROM_ADDR		0x50	// EEPROM ON RTC BOARD
#define CCS811_ADDR			0x5A
#define PCF8523_ADDR 		0x68 // RTC


//#define PCA9685_ADDR 		0x41 		// PWM
//#define ALL_PCA9685_ADDR 		0x70 	// All PCA9685


#endif /* I2C_H_ */
