#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int si443x_set_bitrate(uint32_t bps) {
	uint16_t bitregval;
	bool low_bitrate;
	// TX_DR = 10^6 x txdr[15:0]/2^16 [bps] (if address 70[5] = 0) or
	// TX_DR = 10^6 x txdr[15:0]/2^21 [bps] (if address 70[5] = 1)
	// 70[5] txdtrtscale: This bit should be set for Data Rates below 30 kbps.

	uint64_t temp=0;

	if (bps < 30000) {
		low_bitrate = true;
		temp = (uint64_t)bps << 21;
	} else {
		low_bitrate = false;
		temp = (uint64_t)bps << 16;
	}
	temp /= 1000000;
	bitregval = temp;


	int deviation = bps / 312;
	if (deviation < 1)  deviation = 1;
	if (deviation > 255)  deviation = 255;

/*
	We should also be setting the 0x72 Frequency Deviation Register, 
	LSB = 625 Hz
	Modulation Index = 2 * Bitrate / Deviation
	1 >= Modulation Index < 32
	So, to get a Modulation Index of 1, bitrate / 1250;
	// So, looking at it, this means the bandwidth, right? 
*/

	float mod_index = 2.0f * (float)bps / ((float)deviation*625.0f);

	printf("Bitrate: %6d: VAL %04X LOW %d DEVIATION %d INDEX %f\n", bps, bitregval, low_bitrate, deviation, mod_index);

	return 0;

}

int si443x_set_frequency(uint32_t kHz) {
	int fb, fc, hbsel;

	if (kHz < 240000) {
		// Out of range 
		return -1;
	}
	if (kHz > 960000) {
		// Out of range 
		return -1;
	}

	if (kHz < 480000) {
		// Low Band
		fb = (kHz - 240000) / 10000;
		fc =  (float)(kHz % 10000)/0.15625f;
		hbsel = 0;
	} else {
		// High Band
		fb = (kHz - 480000) / 20000;
		fc =  (float)(kHz % 20000)/0.3125f;
		hbsel = 1;
	}

	// fc vs fo ??? 
	// fcarrier = (fb+24+(fc+fo)/64000) x 10000 x (hbsel+1) + (fhch x fhs x 10) [kHz],
	float calc_freq = (((fb + 24.0f) + (fc / 64000.0f)) * 10000.0f ) * (hbsel + 1.0f);
	printf("Requested frequency: %9d KHz Band %04X fc %02X High %d Actual Freq %9f KHz\n", kHz, fb, fc, hbsel, calc_freq);

	return 0;
}


int main() {
	int i = 300;
/*
	while (1) {
		si443x_set_bitrate(i);
		i <<= 1;
		if ( i > 1000000) break;
	}	
*/
	
	// Datasheet says: Data Rate = 0.123 to 256 kbps

	si443x_set_bitrate(123);

	si443x_set_bitrate(150);
	si443x_set_bitrate(300);
	si443x_set_bitrate(1200);
	si443x_set_bitrate(2400);
	si443x_set_bitrate(4800);
	si443x_set_bitrate(9600);
	si443x_set_bitrate(19200);
	si443x_set_bitrate(38400);
	si443x_set_bitrate(57600);
	si443x_set_bitrate(115200);
	si443x_set_bitrate(230400);

	si443x_set_bitrate(256000);



//	si443x_set_frequency(915000);




}


