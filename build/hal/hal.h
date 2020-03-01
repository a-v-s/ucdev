#ifndef __MCU_H__
#define __MCU_H__

#if defined (NRF51) ||\
    defined (NRF51422_XXAA) ||\
    defined (NRF51422_XXAB) ||\
    defined (NRF51422_XXAC) ||\
    defined (NRF51801_XXAB) ||\
    defined (NRF51802_XXAA) ||\
    defined (NRF51822_XXAA) ||\
    defined (NRF51822_XXAB) ||\
    defined (NRF51822_XXAC) ||\
    defined (NRF51824_XXAA) ||\
defined(NRF52805_XXAA) || defined(NRF52810_XXAA) ||defined (NRF52811_XXAA) ||  \
defined (NRF52832_XXAA) || defined (NRF52832_XXAB) || defined (NRF52833_XXAA) ||\
defined (NRF52840_XXAA) || defined (NRF5340_XXAA_APPLICATION) || defined (NRF5340_XXAA_NETWORK) ||\
defined (NRF9160_XXAA)
	#include "system_nrf.h"	
	#include "nrf.h"
	#include "nrf_hal.h"
#endif

#if defined (STM32F030x6) || defined (STM32F030x8) ||                           \
    defined (STM32F031x6) || defined (STM32F038xx) ||                           \
    defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
    defined (STM32F051x8) || defined (STM32F058xx) ||                           \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
    defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)
#include "system_stm32f0xx.h"
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#endif

#if defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101x6) || \
    defined (STM32F101xB) || defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F102x6) || defined (STM32F102xB) || defined (STM32F103x6) || \
    defined (STM32F103xB) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
#include "system_stm32f1xx.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#endif

#if defined (STM32F205xx) || defined (STM32F215xx) || defined (STM32F207xx) || defined (STM32F217xx)
#include "system_stm32f2xx.h"
#include "stm32f2xx.h"
#include "stm32f2xx_hal.h"
#endif

#if defined (STM32F301x8) || defined (STM32F302x8) || defined (STM32F318xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx) || \
    defined (STM32F303x8) || defined (STM32F334x8) || defined (STM32F328xx) || \
    defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F373xC) || defined (STM32F378xx)
#include "system_stm32f3xx.h"
#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"
#endif

#if defined (STM32F405xx) || defined (STM32F415xx) || defined (STM32F407xx) || defined (STM32F417xx) || \
    defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
    defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || defined (STM32F410Cx) || \
    defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469xx) || \
    defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || defined (STM32F412Vx) || \
    defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#endif

#if defined (STM32F756xx) || defined (STM32F746xx) || defined (STM32F745xx) || defined (STM32F767xx) || \
    defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx) || defined (STM32F722xx) || \
    defined (STM32F723xx) || defined (STM32F732xx) || defined (STM32F733xx) || defined (STM32F730xx) || \
    defined (STM32F750xx)
#include "system_stm32f7xx.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#endif

#if defined (STM32G071xx) || defined (STM32G081xx) || defined (STM32G070xx) || defined (STM32G030xx) || defined (STM32G031xx) || defined (STM32G041xx)
#include "system_stm32g0xx.h"
#include "stm32g0xx.h"
#include "stm32g0xx_hal.h"
#endif


#if defined (STM32G431xx) || defined (STM32G441xx) || \
    defined (STM32G471xx) || defined (STM32G473xx) || defined (STM32G474xx) || defined (STM32G483xx) || defined (STM32G484xx) || defined (STM32GBK1CB)
#include "system_stm32g4xx.h"
#include "stm32g4xx.h"
#include "stm32g4xx_hal.h"
#endif

#if defined (STM32L010x4) || defined (STM32L010x6) || defined (STM32L010x8) || defined (STM32L010xB) || \
    defined (STM32L011xx) || defined (STM32L021xx) || \
    defined (STM32L031xx) || defined (STM32L041xx) || \
    defined (STM32L051xx) || defined (STM32L052xx) || defined (STM32L053xx) || \
    defined (STM32L061xx) || defined (STM32L062xx) || defined (STM32L063xx) || \
    defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || \
    defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
#include "system_stm32l0xx.h"
#include "stm32l0xx.h"
#include "stm32l0xx_hal.h"
#endif

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) || \
    defined (STM32L151xB) || defined (STM32L151xBA) || defined (STM32L151xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L151xDX) || defined (STM32L151xE) || \
    defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L152xDX) || defined (STM32L152xE) || \
    defined (STM32L162xC) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L162xDX) || defined (STM32L162xE)
#include "system_stm32l1xx.h"
#include "stm32l1xx.h"
#include "stm32l1xx_hal.h"
#endif

#if defined (STM32L412xx) || defined (STM32L422xx) || \
    defined (STM32L431xx) || defined (STM32L432xx) || defined (STM32L433xx) || defined (STM32L442xx) || defined (STM32L443xx) || \
    defined (STM32L451xx) || defined (STM32L452xx) || defined (STM32L462xx) || \
    defined (STM32L471xx) || defined (STM32L475xx) || defined (STM32L476xx) || defined (STM32L485xx) || defined (STM32L486xx) || \
    defined (STM32L496xx) || defined (STM32L4A6xx) || \
    defined (STM32L4P5xx) || defined (STM32L4Q5xx) || \
    defined (STM32L4R5xx) || defined (STM32L4R7xx) || defined (STM32L4R9xx) || defined (STM32L4S5xx) || defined (STM32L4S7xx) || defined (STM32L4S9xx)
#include "system_stm32l4xx.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#endif


#if defined (STM32L552xx) || defined (STM32L562xx)
#include "system_stm32l5xx.h"
#include "stm32l5xx.h"
#include "stm32l5xx_hal.h"
#endif


#if defined(STM32WB55xx) || defined(STM32WB50xx)
#include "system_stm32wbxx.h"
#include "stm32wbxx.h"
#include "stm32wbxx_hal.h"
#endif






#endif // __MCU_H__
