all: nrfx stm32f0 stm32f1

stm32f0: stm32f0/libstm32f030x6.a stm32f0/libstm32f030x8.a stm32f0/libstm32f031x6.a stm32f0/libstm32f038xx.a stm32f0/libstm32f042x6.a stm32f0/libstm32f051x8.a stm32f0/libstm32f058xx.a stm32f0/libstm32f070x6.a stm32f0/libstm32f070xb.a stm32f0/libstm32f071xb.a stm32f0/libstm32f072xb.a stm32f0/libstm32f078xx.a stm32f0/libstm32f030xc.a stm32f0/libstm32f091xc.a stm32f0/libstm32f098xx.a 

# Not building due issues
# stm32f0/libstm32f048x6.a
# The .s file is called startup_stm32f048xx.s so the automatic derived startup_stm32f048x6.s is wrong

stm32f1:  stm32f1/libstm32f100xb.a stm32f1/libstm32f100xe.a stm32f1/libstm32f101x6.a stm32f1/libstm32f101xb.a stm32f1/libstm32f101xe.a stm32f1/libstm32f101xg.a stm32f1/libstm32f102x6.a stm32f1/libstm32f102xb.a stm32f1/libstm32f103x6.a stm32f1/libstm32f103xb.a stm32f1/libstm32f103xe.a stm32f1/libstm32f103xg.a stm32f1/libstm32f105xc.a stm32f1/libstm32f107xc.a

nrfx:	nrfx/libnrf51.a nrfx/libnrf52810.a nrfx/libnrf52811.a nrfx/linbrf52832.a nrfx/libnrf52833.a nrfx/libnrf52840.a

nrfx/libnrf51.a:
	make -C nrfx TARGET=NRF51       
nrfx/libnrf52810.a:
	make -C nrfx TARGET=NRF52810
nrfx/libnrf52811.a:
	make -C nrfx TARGET=NRF52811
nrfx/linbrf52832.a:
	make -C nrfx TARGET=NRF52832
nrfx/libnrf52833.a:
	make -C nrfx TARGET=NRF52833
nrfx/libnrf52840.a:
	make -C nrfx TARGET=NRF52840


stm32f0/libstm32f030x6.a:
	make -C stm32f0 TARGET=STM32F030x6 
stm32f0/libstm32f030x8.a:
	make -C stm32f0 TARGET=STM32F030x8 
stm32f0/libstm32f031x6.a:
	make -C stm32f0 TARGET=STM32F031x6 
stm32f0/libstm32f038xx.a:
	make -C stm32f0 TARGET=STM32F038xx 
stm32f0/libstm32f042x6.a:
	make -C stm32f0 TARGET=STM32F042x6 
stm32f0/libstm32f048x6.a:
	make -C stm32f0 TARGET=STM32F048x6 
stm32f0/libstm32f051x8.a:
	make -C stm32f0 TARGET=STM32F051x8 
stm32f0/libstm32f058xx.a:
	make -C stm32f0 TARGET=STM32F058xx 
stm32f0/libstm32f070x6.a:
	make -C stm32f0 TARGET=STM32F070x6 
stm32f0/libstm32f070xb.a:
	make -C stm32f0 TARGET=STM32F070xB 
stm32f0/libstm32f071xb.a:
	make -C stm32f0 TARGET=STM32F071xB 
stm32f0/libstm32f072xb.a:
	make -C stm32f0 TARGET=STM32F072xB 
stm32f0/libstm32f078xx.a:
	make -C stm32f0 TARGET=STM32F078xx 
stm32f0/libstm32f030xc.a:
	make -C stm32f0 TARGET=STM32F030xC 
stm32f0/libstm32f091xc.a:
	make -C stm32f0 TARGET=STM32F091xC 
stm32f0/libstm32f098xx.a:
	make -C stm32f0 TARGET=STM32F098xx 



stm32f1/libstm32f100xb.a:
	make -C stm32f1 TARGET=STM32F100xB
stm32f1/libstm32f100xe.a:
	make -C stm32f1 TARGET=STM32F100xE
stm32f1/libstm32f101x6.a:
	make -C stm32f1 TARGET=STM32F101x6
stm32f1/libstm32f101xb.a:
	make -C stm32f1 TARGET=STM32F101xB
stm32f1/libstm32f101xe.a:
	make -C stm32f1 TARGET=STM32F101xE
stm32f1/libstm32f101xg.a:
	make -C stm32f1 TARGET=STM32F101xG
stm32f1/libstm32f102x6.a:
	make -C stm32f1 TARGET=STM32F102x6
stm32f1/libstm32f102xb.a:
	make -C stm32f1 TARGET=STM32F102xB
stm32f1/libstm32f103x6.a:
	make -C stm32f1 TARGET=STM32F103x6
stm32f1/libstm32f103xb.a:
	make -C stm32f1 TARGET=STM32F103xB
stm32f1/libstm32f103xe.a:
	make -C stm32f1 TARGET=STM32F103xE
stm32f1/libstm32f103xg.a:
	make -C stm32f1 TARGET=STM32F103xG
stm32f1/libstm32f105xc.a:
	make -C stm32f1 TARGET=STM32F105xC
stm32f1/libstm32f107xc.a:
	make -C stm32f1 TARGET=STM32F107xC

