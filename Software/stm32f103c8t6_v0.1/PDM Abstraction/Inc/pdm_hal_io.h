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
	LED_Internal = 0,
	LED_Status,
	NUM_OF_GENERIC_LEDS
}PDMHAL_GenericLedType;

void PDMHAL_GPIO_Init(void);

void PDMHAL_SetCurrentOutput(CurrentOutputsTypedef output);
void PDMHAL_ResetCurrentOutput(CurrentOutputsTypedef output);

void PDMHAL_SetStatusLed(PDMHAL_GenericLedType led);
void PDMHAL_ResetStatusLed(PDMHAL_GenericLedType led);
void PDMHAL_ToggleStatusLed(PDMHAL_GenericLedType led);

/* __OPDM_HAL_IO_H_ */
#endif 
