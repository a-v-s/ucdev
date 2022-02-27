#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>

void get_vendor_name(libusb_device_handle* device_handle){
//	uint8_t send_buffer[] = {0x00, 0x01};
	uint8_t send_buffer[] = {0x00, 0x01};
	uint8_t recv_buffer[64] = {0};
	int transferred = 0;
	int result = 0;
	puts("get_vendor_name");
	result = libusb_bulk_transfer(device_handle, 0x01, send_buffer, sizeof(send_buffer), &transferred, 1000);
	if (result) {
		puts("Send data failed");
		return;
	}
	printf("Sent %2d bytes\n", transferred);
	result = libusb_bulk_transfer(device_handle, 0x81, send_buffer, sizeof(recv_buffer), &transferred, 1000);
	if (result) {
		puts("Receive data failed");
		return;
	}
	printf("Received %2d bytes\n", transferred);
	for (int i = 0; i < transferred; i++) {
		printf("0x%02X ",recv_buffer[i]);
	}
	puts("");

	for (int i = 0; i < transferred; i++) {
		printf("%c",recv_buffer[i]);
	}
	puts("");
	if (transferred <2) return;
	

	if (recv_buffer[0] != send_buffer[0]) {
		puts("Command mismatch");
		return;
	}
	for (int i = 0; i < recv_buffer[1]; i++) {
		printf("%c",recv_buffer[i+2]);
	}
	puts("");
}

int main(int argc, char* argv[]) {
	int result = libusb_init(NULL);
	if (result) {
		puts("Unable to initialise libusb");
		return -1;
	}
	libusb_device_handle* device_handle = libusb_open_device_with_vid_pid(NULL, 0xdead, 0xbeef);
	if (!device_handle) {
		puts("Unable to open device");
		return -1;
	}
	result = libusb_claim_interface(device_handle,0);
		if (result) {
		puts("Unable to claim interface");
		return -1;
	}
get_vendor_name(device_handle);get_vendor_name(device_handle);get_vendor_name(device_handle);
	
	
}

