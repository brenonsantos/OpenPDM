/*
 * opdm_hal.h
 *
 *  Created on: 27 de abr de 2023
 *      Author: breno
 */

#ifndef __OPDM_HAL_H_
#define __OPDM_HAL_H_


//#include "opdm_hal_io_cfg.h"

#include "pdm_hal_canb.h"
#include "pdm_hal_canc.h"
#include "pdm_hal_adc.h"
#include "pdm_hal_io.h"
#include "pdm_hal_spi.h"

#if USE_USB_OVER_CANB
#include "usb_device.h"
#endif

void PDMHAL_Init(void);


#endif /* OPDM_DRIVER_INC_OPDM_HAL_H_ */
