/******************************************************************************
 File:         si443x.h
 Author:       André van Schoubroeck
 License:      MIT

 Contains parts of RadioLib (https://github.com/jgromes/RadioLib)
    MIT license, Copyright (c) 2019 Jan Gromeš


 ********************************************************************************
 MIT License

 Copyright (c) 2021 André van Schoubroeck <andre@blaatschaap.be>

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
 *******************************************************************************/

#ifndef RADIO_SI443X_H_
#define RADIO_SI443X_H_

#include "bshal_spim.h"


#define SI433X_DIR_READ		(0<<7)
#define SI433X_DIR_WRITE	(1<<7)


// Si443x series common registers
#define SI443X_REG_DEVICE_TYPE                        (0x00)
#define SI443X_REG_DEVICE_VERSION                     (0x01)
#define SI443X_REG_DEVICE_STATUS                      (0x02)
#define SI443X_REG_INTERRUPT_STATUS_1                 (0x03)
#define SI443X_REG_INTERRUPT_STATUS_2                 (0x04)
#define SI443X_REG_INTERRUPT_ENABLE_1                 (0x05)
#define SI443X_REG_INTERRUPT_ENABLE_2                 (0x06)
#define SI443X_REG_OP_FUNC_CONTROL_1                  (0x07)
#define SI443X_REG_OP_FUNC_CONTROL_2                  (0x08)
#define SI443X_REG_XOSC_LOAD_CAPACITANCE              (0x09)
#define SI443X_REG_MCU_OUTPUT_CLOCK                   (0x0A)
#define SI443X_REG_GPIO0_CONFIG                       (0x0B)
#define SI443X_REG_GPIO1_CONFIG                       (0x0C)
#define SI443X_REG_GPIO2_CONFIG                       (0x0D)
#define SI443X_REG_IO_PORT_CONFIG                     (0x0E)
#define SI443X_REG_ADC_CONFIG                         (0x0F)
#define SI443X_REG_ADC_SENSOR_AMP_OFFSET              (0x10)
#define SI443X_REG_ADC_VALUE                          (0x11)
#define SI443X_REG_TEMP_SENSOR_CONTROL                (0x12)
#define SI443X_REG_TEMP_VALUE_OFFSET                  (0x13)
#define SI443X_REG_WAKEUP_TIMER_PERIOD_1              (0x14)
#define SI443X_REG_WAKEUP_TIMER_PERIOD_2              (0x15)
#define SI443X_REG_WAKEUP_TIMER_PERIOD_3              (0x16)
#define SI443X_REG_WAKEUP_TIMER_VALUE_1               (0x17)
#define SI443X_REG_WAKEUP_TIMER_VALUE_2               (0x18)
#define SI443X_REG_LOW_DC_MODE_DURATION               (0x19)
#define SI443X_REG_LOW_BATT_DET_THRESHOLD             (0x1A)
#define SI443X_REG_BATT_VOLTAGE_LEVEL                 (0x1B)
#define SI443X_REG_IF_FILTER_BANDWIDTH                (0x1C)
#define SI443X_REG_AFC_LOOP_GEARSHIFT_OVERRIDE        (0x1D)
#define SI443X_REG_AFC_TIMING_CONTROL                 (0x1E)
#define SI443X_REG_CLOCK_REC_GEARSHIFT_OVERRIDE       (0x1F)
#define SI443X_REG_CLOCK_REC_OVERSAMP_RATIO           (0x20)
#define SI443X_REG_CLOCK_REC_OFFSET_2                 (0x21)
#define SI443X_REG_CLOCK_REC_OFFSET_1                 (0x22)
#define SI443X_REG_CLOCK_REC_OFFSET_0                 (0x23)
#define SI443X_REG_CLOCK_REC_TIMING_LOOP_GAIN_1       (0x24)
#define SI443X_REG_CLOCK_REC_TIMING_LOOP_GAIN_0       (0x25)
#define SI443X_REG_RSSI                               (0x26)
#define SI443X_REG_RSSI_CLEAR_CHANNEL_THRESHOLD       (0x27)
#define SI443X_REG_ANTENNA_DIVERSITY_1                (0x28)
#define SI443X_REG_ANTENNA_DIVERSITY_2                (0x29)
#define SI443X_REG_AFC_LIMITER                        (0x2A)
#define SI443X_REG_AFC_CORRECTION                     (0x2B)
#define SI443X_REG_OOK_COUNTER_1                      (0x2C)
#define SI443X_REG_OOK_COUNTER_2                      (0x2D)
#define SI443X_REG_SLICER_PEAK_HOLD                   (0x2E)
#define SI443X_REG_DATA_ACCESS_CONTROL                (0x30)
#define SI443X_REG_EZMAC_STATUS                       (0x31)
#define SI443X_REG_HEADER_CONTROL_1                   (0x32)
#define SI443X_REG_HEADER_CONTROL_2                   (0x33)
#define SI443X_REG_PREAMBLE_LENGTH                    (0x34)
#define SI443X_REG_PREAMBLE_DET_CONTROL               (0x35)
#define SI443X_REG_SYNC_WORD_3                        (0x36)
#define SI443X_REG_SYNC_WORD_2                        (0x37)
#define SI443X_REG_SYNC_WORD_1                        (0x38)
#define SI443X_REG_SYNC_WORD_0                        (0x39)
#define SI443X_REG_TRANSMIT_HEADER_3                  (0x3A)
#define SI443X_REG_TRANSMIT_HEADER_2                  (0x3B)
#define SI443X_REG_TRANSMIT_HEADER_1                  (0x3C)
#define SI443X_REG_TRANSMIT_HEADER_0                  (0x3D)
#define SI443X_REG_TRANSMIT_PACKET_LENGTH             (0x3E)
#define SI443X_REG_CHECK_HEADER_3                     (0x3F)
#define SI443X_REG_CHECK_HEADER_2                     (0x40)
#define SI443X_REG_CHECK_HEADER_1                     (0x41)
#define SI443X_REG_CHECK_HEADER_0                     (0x42)
#define SI443X_REG_HEADER_ENABLE_3                    (0x43)
#define SI443X_REG_HEADER_ENABLE_2                    (0x44)
#define SI443X_REG_HEADER_ENABLE_1                    (0x45)
#define SI443X_REG_HEADER_ENABLE_0                    (0x46)
#define SI443X_REG_RECEIVED_HEADER_3                  (0x47)
#define SI443X_REG_RECEIVED_HEADER_2                  (0x48)
#define SI443X_REG_RECEIVED_HEADER_1                  (0x49)
#define SI443X_REG_RECEIVED_HEADER_0                  (0x4A)
#define SI443X_REG_RECEIVED_PACKET_LENGTH             (0x4B)
#define SI443X_REG_ADC8_CONTROL                       (0x4F)
#define SI443X_REG_CHANNEL_FILTER_COEFF               (0x60)
#define SI443X_REG_XOSC_CONTROL_TEST                  (0x62)
#define SI443X_REG_AGC_OVERRIDE_1                     (0x69)
#define SI443X_REG_TX_POWER                           (0x6D)
#define SI443X_REG_TX_DATA_RATE_1                     (0x6E)
#define SI443X_REG_TX_DATA_RATE_0                     (0x6F)
#define SI443X_REG_MODULATION_MODE_CONTROL_1          (0x70)
#define SI443X_REG_MODULATION_MODE_CONTROL_2          (0x71)
#define SI443X_REG_FREQUENCY_DEVIATION                (0x72)
#define SI443X_REG_FREQUENCY_OFFSET_1                 (0x73)
#define SI443X_REG_FREQUENCY_OFFSET_2                 (0x74)
#define SI443X_REG_FREQUENCY_BAND_SELECT              (0x75)
#define SI443X_REG_NOM_CARRIER_FREQUENCY_1            (0x76)
#define SI443X_REG_NOM_CARRIER_FREQUENCY_0            (0x77)
#define SI443X_REG_FREQUENCY_HOPPING_CHANNEL_SEL      (0x79)
#define SI443X_REG_FREQUENCY_HOPPING_STEP_SIZE        (0x7A)
#define SI443X_REG_TX_FIFO_CONTROL_1                  (0x7C)
#define SI443X_REG_TX_FIFO_CONTROL_2                  (0x7D)
#define SI443X_REG_RX_FIFO_CONTROL                    (0x7E)
#define SI443X_REG_FIFO_ACCESS                        (0x7F)



typedef struct {
	bshal_spim_instance_t * spim
} si443x_t;


#endif /* RADIO_SI443X_H_ */
