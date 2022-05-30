/*
 * nmea.c
 *
 *  Created on: 30 jan. 2022
 *      Author: andre
 *
 *      Enable and disable MNEA sentences
 *      Based upon https://gis.stackexchange.com/questions/198846/enabling-disabling-nmea-sentences-on-u-blox-gps-receiver
 */

int calculateChecksum(const char *msg) {
	int checksum = 0;
	for (int i = 0; msg[i] && i < 32; i++)
		checksum ^= (unsigned char) msg[i];

	return checksum;
}

int nemaMsgSend(const char *msg) {

	static char send_line[83];
	memset(send_line, 0, sizeof(send_line));
	snprintf(send_line, sizeof(send_line) - 1, "$%s*%.2X\r\n", msg,
			calculateChecksum(msg));

 	test_uart_send((void*) send_line, strlen(send_line));

	return 0;
}

int nemaMsgDisable(const char *nema) {
	if (strlen(nema) != 3)
		return -1;

	char tmp[32];
	//snprintf(tmp, sizeof(tmp) - 1, "PUBX,40,%s,0,0,0,0", nema);
	snprintf(tmp, sizeof(tmp) - 1, "PUBX,40,%s,0,0,0,0,0,0", nema);
	nemaMsgSend(tmp);

	return 0;
}

int nemaMsgEnable(const char *nema) {
	if (strlen(nema) != 3)
		return -1;

	char tmp[32];
	//snprintf(tmp, sizeof(tmp) - 1, "PUBX,40,%s,0,1,0,0", nema);
	snprintf(tmp, sizeof(tmp) - 1, "PUBX,40,%s,0,1,0,0,0,0", nema);
	nemaMsgSend(tmp);

	return 0;
}

