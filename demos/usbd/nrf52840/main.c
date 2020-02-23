#include "usbd_nrfx.h"

#include "arm_cpuid.h"

#include <stdbool.h>


void usbd_reenumerate(){
    // TODO
}


char rt[128];

void romtable() {
	intptr_t ROMTABLE = (intptr_t) (0xE00FF000);
	romtable_id_t *rid = (romtable_id_t*) (ROMTABLE | 0xFD0);
	bool jep106_used = (rid->pid2 & (1 << 3)) == (1 << 3);
	int continuation_code = rid->pid4 & 0xF;
	int identity_code = ((rid->pid1 & 0xf0) >> 4) | ((rid->pid2 & 0x7) << 4);
	int partno = rid->pid0 | ((rid->pid1 & 0xF) << 8);
	int revision = (rid->pid3 & 0x0F) >> 4;
	int modified = (rid->pid3 & 0xF);

	int is_table_size_4k = (rid->pid4 & 0xF0) >> 4;

	char *prob = "Unknown";

	sprintf(rt, "%s %s  V:%1d CONT:%3d ID:%3d PART: %3X REV:%3d ", prob,
			cpuid(), jep106_used, continuation_code, identity_code, partno,
			revision);

	// nRF52840 : Cortex-M4 r0p1  V:1 CONT:  2 ID: 68 PART:   8 REV:  0
}


int main() {
	romtable();
	usbd_reenumerate();
	usbd_init();

	while (1)
		;;
}
