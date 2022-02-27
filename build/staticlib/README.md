Build Static Libs for STM32Cube* and nrfx libraries:

Inspired by how libopencm3 builds, I'd figured I could make static libs out of the STM32Cube libraries as well.
So Basically, it builds the HAL + Startup files into a .a file that can be linked in the project.

For now it has been built for nRF51, nRF52, STM32F0 and STM32F1. 




TODO: 

At the moment it doesn't build for stm32f048x6 due the fact the define and the startup file differ in name. 
The code for handling the nRF52832 can be adjusted for this purpose

There are no CPU/FPU flags for nRF53 and nRF91 defined 
