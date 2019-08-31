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

# Projects

## PSoC4 support for libopencm3

I'm working on writing peripheral driver for Cypress PSoC4 microcontrollers to contribute to the libopencm3 project (LGPL license)

## nrfx integration in libopencm3

Building the Nordic nrfx license with libopencm3. 

<!--
WYSIWYG Markdown Editor 	https://stackedit.io/app#
-->




