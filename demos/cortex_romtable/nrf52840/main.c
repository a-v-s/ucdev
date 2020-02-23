/*
 File:		main.c
 License: 	MIT

 Copyright (c) 2019, 2020 André van Schoubroeck

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


#include "usbd_nrfx.h"

#include "arm_cpuid.h"

#include <stdbool.h>

void usbd_reenumerate() {
	// TODO
}

char rt[128];

void parse_romtable() {

	intptr_t ROMTABLE = (intptr_t)(0xE00FF000);
	romtable_id_t *rid = (romtable_id_t*) (ROMTABLE | 0xFD0);
	romtable_pid_t romtable_pid = extract_romtable_pid(rid);

	char *prob = "Unknown";
	if (romtable_pid.identity_code == 68
			&& romtable_pid.continuation_code == 2) {
		prob = "nRF5x";
	}
	sprintf(rt, "%s %s  V:%1d CONT:%3d ID:%3d PART: %3X REV:%3d ", prob,
			cpuid(), romtable_pid.jep106_used, romtable_pid.continuation_code,
			romtable_pid.identity_code, romtable_pid.partno,
			romtable_pid.revision);

}

int main() {
	parse_romtable();

	usbd_reenumerate();
	usbd_init();

	while (1)
		;;
}
