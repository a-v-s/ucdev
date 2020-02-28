/*
 * demo.c
 *
 *  Created on: 24 dec. 2019
 *      Author: andre
 */

#include "usbd.h"

uint8_t temp_recv_buffer[64];
uint8_t temp_send_buffer[64];



void transfer_in_complete(usbd_handle_t *handle, uint8_t epnum, void *data,
		size_t size) {

}

void transfer_out_complete(usbd_handle_t *handle, uint8_t epnum, void *data,
		size_t size) {

	// Execute DAP command (process request and prepare response)
	//   request:  pointer to request data
	//   response: pointer to response data
	//   return:   number of bytes in response (lower 16 bits)
	//             number of bytes in request (upper 16 bits)

	int result = DAP_ExecuteCommand(data, temp_send_buffer);
	usbd_transmit(handle, 0x80 | epnum, temp_send_buffer, result & 0xFFFF);
}

void usbd_demo_setup_descriptors(usbd_handle_t *handle) {
	handle->descriptor_device = add_descriptor(handle,
			sizeof(usb_descriptor_device_t));
	handle->descriptor_device->bDescriptorType = USB_DT_DEVICE;
	handle->descriptor_device->bMaxPacketSize0 = 64;
	handle->descriptor_device->bNumConfigurations = 1;
	handle->descriptor_device->bcdUSB = 0x0101;
	handle->descriptor_device->idVendor = 0xdead;
	handle->descriptor_device->idProduct = 0xbeef;

	handle->descriptor_device->bDeviceClass = 0x00;
	// For HID we need another HID descriptor
	// What content should it contain?

	handle->descriptor_device->iManufacturer = 1;
	handle->descriptor_device->iProduct = 2;
	handle->descriptor_device->iSerialNumber = 3;

	handle->descriptor_configuration[0] = add_descriptor(handle,
			sizeof(usb_descriptor_configuration_t));
	handle->descriptor_configuration[0]->wTotalLength =
			handle->descriptor_configuration[0]->bLength;
	handle->descriptor_configuration[0]->bDescriptorType = USB_DT_CONFIGURATION;
	handle->descriptor_configuration[0]->bConfigurationValue = 1;
	handle->descriptor_configuration[0]->bMaxPower = 10;
	handle->descriptor_configuration[0]->bmAttributes = 0x80;
	handle->descriptor_configuration[0]->bNumInterfaces = 1;

	usb_descriptor_interface_t *iface = add_descriptor(handle,
			sizeof(usb_descriptor_configuration_t));
	handle->descriptor_configuration[0]->wTotalLength += iface->bLength;
	iface->bDescriptorType = USB_DT_INTERFACE;
	iface->bInterfaceClass = 0x03;
	iface->bNumEndpoints = 2;
	iface->bInterfaceNumber = 0;
	iface->bAlternateSetting = 0;
	iface->iInterface = 2;

	// We need to add a HID Descriptor

	usbd_descriptor_hid_t *hid_descriptor = add_descriptor(handle,
			sizeof(usbd_descriptor_hid_t));
	handle->descriptor_configuration[0]->wTotalLength += hid_descriptor->bLength;
	hid_descriptor->bDescriptorType = 0x21; // TODO define this
	hid_descriptor->bCountryCode = 0;
	hid_descriptor->bNumDescriptors = 1;
	hid_descriptor->bcdHID = 0x0111;
	hid_descriptor->reports.wDescriptorLength = 33;//sizeof(usb_hid);
	hid_descriptor->reports.bDescriptorType = 0x22;

	// HID Uses Interrupt End Points

	usbd_add_endpoint_in(handle, 1, 0x81, USB_EP_ATTR_TYPE_INTERRUPT, 64, 1,
			(usbd_transfer_cb_f) &transfer_in_complete);

	usbd_add_endpoint_out(handle, 1, 0x01, USB_EP_ATTR_TYPE_INTERRUPT, 64, 1,
			temp_recv_buffer, 64, (usbd_transfer_cb_f) &transfer_out_complete);

	// Is there a size limit to USB Strings? They appear to get truncated at 32 characters
	// I swear I've seen longer strings, or am I imagining things?
	// Perhaps there is an error in the way I handle USB requests?
	handle->descriptor_string[1] = add_string_descriptor_utf16(handle, u"BlaatSchaap (https://www.blaatschaap.be)");
	handle->descriptor_string[2] = add_string_descriptor_utf16(handle, u"BlaatSchaap CMSIS-DAP");

	handle->descriptor_string[3] = add_string_descriptor_utf16(handle, u"1234");

}
