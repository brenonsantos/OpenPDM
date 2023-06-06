/*
 * opdm_hal_io.h
 *
 *  Created on: Mar 21, 2023
 *      Author: breno
 */

#ifndef __OPDM_HAL_IO_H_
#define __OPDM_HAL_IO_H_


#include <pdm_hal_def.h>

//----------------- ENUMS -----------------

typedef enum{
	INTERNAL_LED = 0,
	STATUS_LED = 1,
	NUM_OF_GENERIC_LEDS
}PDMHAL_GenericLedType;

//typedef enum{
//	CANB_EN = 0,
//	CANB_ERR,
//	CANB_STB,
//	NUM_OF_CANB_PINS
//}CANB_PINS_TYPE;
//
//typedef enum{
//	CANC_INTERRUPT = 0,
//	NUM_OF_CANC_PINS
//}CANC_PINS_TYPE;

void PDMHAL_SetCurrentOutput(CurrentOutputsTypedef output);
void PDMHAL_ResetCurrentOutput(CurrentOutputsTypedef output);

void PDMHAL_SetStatusLed(PDMHAL_GenericLedType led);
void PDMHAL_ResetStatusLed(PDMHAL_GenericLedType led);

/* OPDM_DRIVER_OPDM_HAL_IO_H_ */
#endif 
