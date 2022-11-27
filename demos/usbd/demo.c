/*
 File:		demo.c
 License: 	MIT

Copyright (c) 2018 - 2022 André van Schoubroeck <andre@blaatschaap.be>

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
#include "usbd.h"
#include "serialnumber.h"

#include "usbd_descriptor_winusb.h"
#include "usbd_descriptor_webusb.h"

#include "ConvertUTF.h"

uint8_t temp_recv_buffer[256];
void transfer_in_complete(bscp_usbd_handle_t *handle, uint8_t epnum, void *data,
		size_t size) {

}

void transfer_out_complete(bscp_usbd_handle_t *handle, uint8_t epnum,
		void *data, size_t size) {

	if (!size)
		return;
	//__asm__ __volatile__ ("bkpt #0");
	// This is a test to reply the data increased by 1;
	((uint8_t*) (data))[0]++;
	bscp_usbd_transmit(handle, 0x80 | epnum, data, size);

}

bscp_usbd_handler_result_t bscp_usbd_handle_user_request(
		bscp_usbd_handle_t *handle, usb_setuprequest_t *req, void **buf,
		size_t *len) {


	if (req ->bRequest == USB_REQ_GET_DESCRIPTOR &&
			(req->wValue >> 8) == USB_DT_BOS) {
#pragma pack(push,1)
		static struct {
			usbd_descriptor_bos_t bos;
			usbd_bos_capability_microsoft_descriptor_t bos_winusb;
		} bos_respose;
#pragma pack(pop)

		bos_respose.bos.bDescriptorType = USB_DT_BOS;
		bos_respose.bos.bLength = sizeof(usbd_descriptor_bos_t);
		bos_respose.bos.bNumDeviceCaps = 1;
		bos_respose.bos.wTotalLength = sizeof(usbd_descriptor_bos_t)
				+ sizeof(usbd_bos_capability_microsoft_descriptor_t);

		usbd_bos_capability_microsoft_descriptor_t *bos_winusb = add_descriptor(
				handle, sizeof(usbd_bos_capability_microsoft_descriptor_t));

		bos_respose.bos_winusb.bLength =
				sizeof(usbd_bos_capability_microsoft_descriptor_t);

		bos_respose.bos_winusb.bDescriptorType = 0x10;
		bos_respose.bos_winusb.bDevCapabilityType = 0x05;
		bos_respose.bos_winusb.bReserved = 0x00;
		bos_respose.bos_winusb.guid = USBD_BOS_CAP_MICROSOFT_UUID;
		bos_respose.bos_winusb.dwWindowsVersion = NTDDI_WINBLUE;

		bos_respose.bos_winusb.wMSOSDescriptorSetTotalLength =
				sizeof(usbd_msos20_set_header_descriptor_t)
						+ sizeof(usbd_msos20_compatible_id_descriptor_t)
						+ sizeof(usbd_msos20_registry_property_descriptor_t);

		bos_respose.bos_winusb.bMS_VendorCode = REQUESTVALUE_MICROSOFT;
		bos_respose.bos_winusb.bAltEnumCode = 0x00;

		if (req->wLength < sizeof(bos_respose)) {
			*len = req->wLength;
		} else {
			*len = sizeof(bos_respose);
		}

		*buf = &bos_respose;

		return RESULT_HANDLED;
	}

	if (req->bRequest == REQUESTVALUE_MICROSOFT) {

#pragma pack(push,1)

		//  Note: This is the format for a single interface device
		//  For multi interface device, a "composite" device
		//  a different response is required

		static struct {
			usbd_msos20_set_header_descriptor_t set_header;
			usbd_msos20_compatible_id_descriptor_t compatible_id;
			usbd_msos20_registry_property_descriptor_t registery_property;
		} winusb_response;
#pragma pack(pop)

		winusb_response.set_header.wLength =
				sizeof(usbd_msos20_set_header_descriptor_t);
		winusb_response.set_header.wDescriptorType =
				MS_OS_20_SET_HEADER_DESCRIPTOR;
		winusb_response.set_header.dwWindowsVersion = NTDDI_WINBLUE;
		winusb_response.set_header.wTotalLength = sizeof(winusb_response);

		winusb_response.compatible_id.wLength =
				sizeof(usbd_msos20_compatible_id_descriptor_t);
		winusb_response.compatible_id.wDescriptorType =
				MS_OS_20_FEATURE_COMPATIBLE_ID;
		winusb_response.compatible_id.CompatibleID = USBD_MSOS_DRIVER_WINUSB;

		winusb_response.registery_property.wLength =
				sizeof(usbd_msos20_registry_property_descriptor_t);
		winusb_response.registery_property.wDescriptorType = 0x04; // MS_OS_20_FEATURE_REG_PROPERTY
		winusb_response.registery_property.wPropertyDataType = 0x07; // REG_MULTI_SZ
		winusb_response.registery_property.wPropertyNameLength = 0x2a;
		winusb_response.registery_property.wPropertyDataLength = 0x50;

		uint8_t PropertyName[] = "DeviceInterfaceGUIDs";
		uint8_t *pni_begin = PropertyName;
		uint16_t *pno_begin = winusb_response.registery_property.PropertyName;
		ConvertUTF8toUTF16(&pni_begin, PropertyName + sizeof(PropertyName),
				&pno_begin,
				&winusb_response.registery_property.PropertyName[20], 0);

		// NOTE: Generate a new GUID for a new project.
		uint8_t PropertyData[39] = "{3e295e33-b22f-466e-80d9-3a5e6574cfe8}";
		uint8_t *pdi_begin = PropertyData;
		uint16_t *pdo_begin = winusb_response.registery_property.PropertyData;
		ConvertUTF8toUTF16(&pdi_begin, PropertyData + sizeof(PropertyData),
				&pdo_begin,
				&winusb_response.registery_property.PropertyData[40], 0);


		if (req->wLength < sizeof(winusb_response)) {
			*len = req->wLength;
		} else {
			*len = sizeof(winusb_response);
		}

		*buf = &winusb_response;
		*len = sizeof(winusb_response);
		return RESULT_HANDLED;
	}
	return RESULT_NEXT_PARSER;

}

void bscp_usbd_demo_setup_descriptors(bscp_usbd_handle_t *handle) {
	handle->descriptor_device = add_descriptor(handle,
			sizeof(usb_descriptor_device_t));
	handle->descriptor_device->bDescriptorType = USB_DT_DEVICE;
	handle->descriptor_device->bMaxPacketSize0 = 64;
	handle->descriptor_device->bNumConfigurations = 1;
	handle->descriptor_device->bcdUSB = 0x0201; // USB 2.1 for BOS
	//handle->descriptor_device->bcdUSB = 0x0200; // USB 2.0 for no BOS
	handle->descriptor_device->idVendor = 0xdead;
	handle->descriptor_device->idProduct = 0xbeef;

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

	// TODO Make function to add interfaces (and altsettings)

	usb_descriptor_interface_t *iface = add_descriptor(handle,
			sizeof(usb_descriptor_configuration_t));
	handle->descriptor_configuration[0]->wTotalLength += iface->bLength;
	iface->bDescriptorType = USB_DT_INTERFACE;
	iface->bInterfaceProtocol = 0xff;
	iface->bNumEndpoints = 2;
	iface->bInterfaceNumber = 0;
	iface->bAlternateSetting = 0;

	bscp_usbd_add_endpoint_in(handle, 1, 1, USB_EP_ATTR_TYPE_INTERRUPT, 64, 1,
			(bscp_usbd_transfer_cb_f) &transfer_in_complete);
	bscp_usbd_add_endpoint_out(handle, 1, 1, USB_EP_ATTR_TYPE_INTERRUPT, 64, 1,
			temp_recv_buffer, sizeof(temp_recv_buffer),
			(bscp_usbd_transfer_cb_f) &transfer_out_complete);

	// Be sure to save the file as UTF-8. ;)
	handle->descriptor_string[1] = add_string_descriptor_utf16(handle, u"BlaatSchaap");

	// The u"string" prefix encodes it as UTF16 from the start
	handle->descriptor_string[2] = add_string_descriptor_utf16(handle, u"USB Device Demo | Some long string to test it that works");
	//handle->descriptor_string[2] = add_string_descriptor_utf16(handle, u"USB Device Demo");

	uint16_t serial_number[9] = { 0 };
	GetSerialStringUTF16(serial_number, 8);
	handle->descriptor_string[3] = add_string_descriptor_utf16(handle,
			serial_number);

	bscp_usbd_request_handler_add(handle, bscp_usbd_handle_user_request);

}
