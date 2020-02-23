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
