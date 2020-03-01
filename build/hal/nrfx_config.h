/*******************************************************************************
*   nrf_config.h dispatcher                                                    *
*   -----------------------                                                    *
*                                                                              *
*   This file assumed a copy of the nrfx config templates to be present in the *
*   nrfx directory. It will include the template for the defined MCU           *
*                                                                              *
*******************************************************************************/



#if defined (NRF51) ||\
    defined (NRF51422_XXAA) ||\
    defined (NRF51422_XXAB) ||\
    defined (NRF51422_XXAC) ||\
    defined (NRF51801_XXAB) ||\
    defined (NRF51802_XXAA) ||\
    defined (NRF51822_XXAA) ||\
    defined (NRF51822_XXAB) ||\
    defined (NRF51822_XXAC) ||\
    defined (NRF51824_XXAA) 
#include "nrfx/nrfx_config_nrf51.h"
#endif

// There seems to config template for nRF52805. For now use the 52832 config
// Also, this part doesn't seem mentioned. Probably some custom part ???
#if defined (NRF52805_XXAA) 
#include "nrfx/nrfx_config_nrf52832.h"
#endif

#if defined (NRF52810_XXAA) 
#include "nrfx/nrfx_config_nrf52810.h"
#endif 

#if defined (NRF52811_XXAA)
#include "nrfx/nrfx_config_nrf52811.h"
#endif

#if defined (NRF52832_XXAA) || defined (NRF52832_XXAB)
#include "nrfx/nrfx_config_nrf52832.h"
#endif


#if defined (NRF52833_XXAA)
#include "nrfx/nrfx_config_nrf52833.h"
#endif

#if defined (NRF52840_XXAA)
#include "nrfx/nrfx_config_nrf52840.h"
#endif 

#if defined (NRF5340_XXAA_APPLICATION)
#include "nrfx/nrfx_config_nrf5340_application.h"
#endif

#if defined (NRF5340_XXAA_NETWORK) 
#include "nrfx/nrfx_config_nrf5340_network.h"
#endif

#if defined (NRF9160_XXAA)
#include "nrfx/nrfx_config_nrf9160.h"
#endif

