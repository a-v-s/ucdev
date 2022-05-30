/******************************************************************************
 File:         si443x.c
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

#include "si443x.h"

#include <stdint.h>

int si433x_init(bshal_spim_t *spim, si443x_t *si443x) {
	si443x->spim = spim;

	uint8_t device_type = -1;
	uint8_t device_version = -1;

	si443x_get_reg8(si443x, SI433X_REG_DEVICE_TYPE, &device_type);
	si443x_get_reg8(si443x, SI433X_REG_DEVICE_VERSION, &device_version);
}

int16_t si443x_set_frequency(si443x_t *si443x, float newFreq) {
	// set mode to standby
	int16_t state = standby();

	// check high/low band
	uint8_t bandSelect = RADIOLIB_SI443X_BAND_SELECT_LOW;
	uint8_t freqBand = (newFreq / 10) - 24;
	uint8_t afcLimiter = 80;
	_freq = newFreq;
	if (newFreq >= 480.0) {
		bandSelect = RADIOLIB_SI443X_BAND_SELECT_HIGH;
		freqBand = (newFreq / 20) - 24;
		afcLimiter = 40;
	}

	// calculate register values
	uint16_t freqCarrier = ((newFreq / (10 * ((bandSelect >> 5) + 1)))
			- freqBand - 24) * (uint32_t) 64000;

	// update registers
	state = si443x_aet_reg8(si443x, SI443X_REG_FREQUENCY_BAND_SELECT, bandSelect | freqBand, 5, 0);
	state |= si443x_aet_reg8(si443x, SI443X_REG_NOM_CARRIER_FREQUENCY_1, (uint8_t)((freqCarrier & 0xFF00) >> 8));
	state |= si443x_aet_reg8(si443x, SI443X_REG_NOM_CARRIER_FREQUENCY_0, (uint8_t)(freqCarrier & 0xFF));
	state |= si443x_aet_reg8(si443x, SI443X_REG_AFC_LIMITER, afcLimiter);

	return (state);
}

