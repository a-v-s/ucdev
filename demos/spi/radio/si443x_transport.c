/******************************************************************************
 File:         si443x_transport.c
 Author:       André van Schoubroeck
 License:      MIT


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

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "si443x.h"

int si443x_recv(si443x_t *rc66x, uint8_t reg, uint8_t *data, size_t amount) {
	uint8_t addr = reg | SI433X_DIR_READ;
	int result = 0;

	result = bshal_spim_transmit(rc66x->spim, &addr, 1, true);
	if (result)
		return result;
	return bshal_spim_transceive(rc66x->spim, data, amount, false);
}

int si443x_send(si443x_t *rc66x, uint8_t reg, uint8_t *data, size_t amount) {
	int result = 0;
	uint8_t addr = reg | SI433X_DIR_WRITE;

	result = bshal_spim_transmit(rc66x->spim, &addr, 1, true);
	if (result)
		return result;
	result = bshal_spim_transmit(rc66x->spim, data, amount,
			false);
	return result;

}

int si443x_get_reg8(si443x_t *rc66x, uint8_t reg, uint8_t *value) {
	return si443x_recv(rc66x, reg, value, 1);
}

int si443x_set_reg8(si443x_t *rc66x, uint8_t reg, uint8_t value) {
	return si443x_send(rc66x, reg, &value, 1);
}

int si443x_or_reg8(si443x_t *rc66x, uint8_t reg, uint8_t value) {
	uint8_t tmpval;
	int result;
	result = si443x_get_reg8(rc66x, reg, &tmpval);
	if (result)
		return result;
	tmpval |= value;
	return si443x_set_reg8(rc66x, reg, tmpval);
}

int si443x_and_reg8(si443x_t *rc66x, uint8_t reg, uint8_t value) {
	uint8_t tmpval;
	int result;
	result = si443x_get_reg8(rc66x, reg, &tmpval);
	if (result)
		return result;
	tmpval &= value;
	return si443x_set_reg8(rc66x, reg, tmpval);
}

