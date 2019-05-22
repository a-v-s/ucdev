# ucdev

Welcome to ucdev - microcontroller development

A collection of libraries and scripts for embedded development.
This repository has just been started and at the moment mostly contains some existing projects related to microcontroller development as submodules. The projects includes here contain peripheral drivers and libraries.

I have split up the libraries in ext and ext-nonfree. In the ext-nonfree I have put libraries which have some usage restrictions, such as "can only be used with chips from manufacturer x", or "can only be used in non-commercial projects", which would make them GPL-incompatible.

On licenses, I prefer libraries under licenses like MIT, BSD and Apache. I want to be concerned about code, and not about legal license compatibility.

## ext
External libraries using an open source license

| Repository | License | Description |
|--|--|--|
|libopencm3	| LGPL3+ | firmware library for various mcu (mostly STM32)  |
|nrfx		| BSD3 | firmware library for Nordic nRF5x and nRF91x |
|stm8-header| MIT  | MIT licensed headers for STM8 using SDCC compiler|
|CMSIS_5| Apache 2.0 | Cortex Microcontroller Software Interface Standard
| 

## ext-nonfree
External libraries using a license with some non-free restrictions. 
These restrictions usually mean the code may only be used on the suppliers 
hardware. 

| Repository | License | Description |
|--|--|--|
| Gecko_SDK | Non-Free | firmware library for Silicon Labs EFM32, EFR32 and EZR32 |
| stm8s-header | Non-Free | Patched ST headers for SDCC compatibility | 

# Projects

## PSoC4 support for libopencm3

I'm working on writing peripheral driver for Cypress PSoC4 microcontrollers to contribute to the libopencm3 project (LGPL license)

## nrfx integration in libopencm3

Building the Nordic nrfx license with libopencm3. 

<!--
WYSIWYG Markdown Editor 	https://stackedit.io/app#
-->




