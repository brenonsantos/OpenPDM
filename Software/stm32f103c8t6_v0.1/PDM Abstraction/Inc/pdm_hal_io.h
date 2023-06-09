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


void PDMHAL_SetCurrentOutput(CurrentOutputsTypedef output);
void PDMHAL_ResetCurrentOutput(CurrentOutputsTypedef output);

void PDMHAL_SetStatusLed(PDMHAL_GenericLedType led);
void PDMHAL_ResetStatusLed(PDMHAL_GenericLedType led);

/* __OPDM_HAL_IO_H_ */
#endif 
