/*
 * identify.c
 *
 *  Created on: 3 jun. 2022
 *      Author: andre
 */

#include <stdint.h>

#if defined __riscv

#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#pragma pack(push,1)
typedef enum {
	RV32 = 1,
	RV64 = 2,
	RV128 = 3,
} misa_mxl_t;

typedef struct {
	union {
		uint32_t as_uint32;
		union {
			unsigned int Extensions : 25;
			struct {
				unsigned int A : 1;
				unsigned int B : 1;
				unsigned int C : 1;
				unsigned int D : 1;
				unsigned int E : 1;
				unsigned int F : 1;
				unsigned int G : 1;
				unsigned int H : 1;
				unsigned int I : 1;
				unsigned int J : 1;
				unsigned int K : 1;
				unsigned int L : 1;
				unsigned int M : 1;
				unsigned int N : 1;
				unsigned int O : 1;
				unsigned int P : 1;
				unsigned int Q : 1;
				unsigned int R : 1;
				unsigned int S : 1;
				unsigned int T : 1;
				unsigned int U : 1;
				unsigned int V : 1;
				unsigned int W : 1;
				unsigned int X : 1;
				unsigned int Y : 1;
				unsigned int Z : 1;
			} Extension;
		};
		unsigned int			: 4;
		misa_mxl_t MXL		: 2;
	};

} misa_t;
#pragma pack(pop)

char * cpuid(){
	static char arch[32];
	misa_t misa = {.as_uint32 = read_csr(misa)};
	sprintf(arch, "RV32");
	int i = strlen(arch);

	// I should be selected over E if both are available.
	if (misa.Extension.I) {
		arch[i]='I';
		i++;
	} else if (misa.Extension.E) {
		arch[i]='E';
		i++;
	} else {
		sprintf(arch, "Unkown");
		return;
	}


	if (misa.Extension.M) {
		arch[i]='M';
		i++;
	}
	if (misa.Extension.A) {
		arch[i]='A';
		i++;
	}
	if (misa.Extension.F) {
		arch[i]='F';
		i++;
	}
	if (misa.Extension.D) {
		arch[i]='D';
		i++;
	}
	if (misa.Extension.G) {
		arch[i]='G';
		i++;
	}
	if (misa.Extension.Q) {
		arch[i]='Q';
		i++;
	}
	if (misa.Extension.L) {
		arch[i]='L';
		i++;
	}
	if (misa.Extension.C) {
		arch[i]='C';
		i++;
	}
	if (misa.Extension.B) {
		arch[i]='B';
		i++;
	}
	if (misa.Extension.J) {
		arch[i]='J';
		i++;
	}
	if (misa.Extension.T) {
		arch[i]='T';
		i++;
	}
	if (misa.Extension.P) {
		arch[i]='P';
		i++;
	}
	if (misa.Extension.V) {
		arch[i]='V';
		i++;
	}
	if (misa.Extension.N) {
		arch[i]='N';
		i++;
	}
	return arch;
}


#define  GD32_MARCHID     0x80000022		// Identifiers for GD32VF103
#define  GD32_MVENDORID   0x0000031E		// Identifiers for GD32VF103

#define  CH32_MARCHID     0x00000000		// Identifiers for CH32V103
#define  CH32_MVENDORID   0x01020304		// Identifiers for CH32V103

char * mcuid(){
	if (read_csr(marchid) == GD32_MARCHID && read_csr(mvendorid) == GD32_MVENDORID)
		return "GD32VF103";
	if (read_csr(marchid) == CH32_MARCHID && read_csr(mvendorid) == CH32_MVENDORID)
			return "CH32F103";
	return "Unkown";
}
#elif defined __ARM_EABI__
#include "arm_cpuid.h"

char * mcuid() {

	intptr_t ROMTABLE = (intptr_t) (0xE00FF000);
	romtable_id_t *rid = (romtable_id_t*) (ROMTABLE | 0xFD0);
	romtable_pid_t romtable_pid = extract_romtable_pid(rid);

	if (romtable_pid.jep106_used) {
		if (romtable_pid.identity_code == 32
				&& romtable_pid.continuation_code == 0) {
			return  "STM32F103";
		}
		if (romtable_pid.identity_code == 81
				&& romtable_pid.continuation_code == 7) {
			return  "GD32F103";
		}
		if (romtable_pid.identity_code == 59
				&& romtable_pid.continuation_code == 4) {

			switch((*(uint32_t*)(0x1FFFF7d0))) {
			case 0x0CF300FF:
				return  "APM32F103";
				break;
			case 0xFFFFFFFF:
				switch((*(uint32_t*)(0x1FFFF000))) {
				case 0x200001fc:
					return  "CS32F103";
					break;
				case 0x20000910:
					return  "CH32F103";
					break;
				}
				break;
			}


		}
	} else {
		// JEP106 not used. Legacy ASCII values are used. This should not be used
		// on new products. And this note was written in the ADI v5 specs.
		// The Only value I've been able to find is 0x41 for ARM.

		// The identity/contiuation code are not filled acoording the JEP106
		// According to speds, this is the legacy idenitification where
		// the Identity Code contains an ASCII value. On the HK32 we read
		// JEP106 = false / Identity = 0x55 / Continuation = 5
		// 0x55 corresponds with 'U'. This looks like this could be an ASCII Identifier.
		// However, if ASCII IDs are used, the expected Continuation would be 0, as
		// this field is "reserved, read as zero" when legacy ASCII IDs are used.

		// Even though these values are violating the specs, we can use
		// JEP106 = false, ID = 0x55, Cont = 5 to detect HK32.

		if (romtable_pid.identity_code == 0x55
				&& romtable_pid.continuation_code == 5) return  "HK32F103";
	}

	return "Unkown";

}

#else
#error "unsupported architecture"
#endif
