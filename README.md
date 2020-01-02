# ucdev

Welcome to ucdev - microcontroller development

A collection of libraries and scripts for embedded development.
This repository has just been started and at the moment mostly contains some existing projects related to microcontroller development as submodules. The projects includes here contain peripheral drivers and libraries.

These external repositories are under various licenses. Some of these licenses have usage restrictions, usually saying they can only be used with silicon from said manufacturer, or that the code license is not affected by external licenses. Such restrictions make them GPL incompatible. 


## ext
External libraries

| Repository | License | Description |
|--|--|--|
| CMSIS_5       | Apache 2.0 | Cortex Microcontroller Software Interface Standard       |
| Gecko_SDK     | Non-Free | firmware library for Silicon Labs EFM32, EFR32 and EZR32   |
| libopencm3	  | LGPL3+ | firmware library for various mcu (mostly STM32)              |
| nrfx		      | 3BSD | firmware library for Nordic nRF5x and nRF91x                   |
| stm8-header   | MIT  | MIT licensed headers for STM8 using SDCC compiler              |
| stm8s-header  | Non-Free | Patched ST headers for SDCC compatibility                  | 
| STM32Cube*    | Mixed | Official ST SDK libraries                                     |

libopencm3 is under a LGPL license. As on embedded systems libraries are usually statically linked, this is effectivly GPL.

For STM32Cube* see License.md in their directories. Basically, the HAL is 3BSD.
The USB libraries are SLA0044, wich states that other code licenses won't change its license, rendering it GPL incompatible. 

# Projects (lib)

## libhlusb

High Level USB library: implements the USB protocol, agnostic of the hardware,
so it can be used in combination with any microcontroller once some glue code
with the low level drivers has been written. This project is in development.
There are hardware bindings for STM32CubeF1 and nrfx. Currently it can 
enumerate, send and transmit data.

## libws2812dma

WS2812 Implementation using DMA transfers. This project started out on the
STM32F103. It uses the timer hardware to generate a PWM signal, where using DMA
transfers set the duty cycle per cycle, implementing the WS2812 protocol this 
way. It can control up to 4 channels simultaneously. 
There is a port for the NRF52 series, however for the time being this is a 
single channel only implementation.

<!--
WYSIWYG Markdown Editor 	https://stackedit.io/app#
-->




