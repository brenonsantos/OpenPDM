/*
 * opdm_hal_io.h
 *
 *  Created on: Mar 21, 2023
 *      Author: breno
 */

#ifndef __OPDM_HAL_IO_H_
#define __OPDM_HAL_IO_H_


#include "opdm_hal_def.h"

//----------------- ENUMS -----------------

typedef enum{
	HC0_OUTPUT = 0,
	HC1_OUTPUT,
	HC2_OUTPUT,
	HC3_OUTPUT,
	LC0_OUTPUT,
	LC1_OUTPUT,
	LC2_OUTPUT,
	LC3_OUTPUT,
	NUM_OF_CURRENT_OUTPUTS
}PDMHAL_CurrentOutputType;


typedef enum{
	INTERNAL_LED = 0,
	STATUS_LED = 1,
	NUM_OF_LEDS
}LED_OUTPUT_TYPE;

typedef enum{
	CANB_EN = 0,
	CANB_ERR,
	CANB_STB,
	NUM_OF_CANB_PINS
}CANB_PINS_TYPE;

typedef enum{
	CANC_INTERRUPT = 0,
	NUM_OF_CANC_PINS
}CANC_PINS_TYPE;

void PDMHAL_SetCurrentOutput(PDMHAL_CurrentOutputType output);
void PDMHAL_ResetCurrentOutput(PDMHAL_CurrentOutputType output);

/* OPDM_DRIVER_OPDM_HAL_IO_H_ */
#endif 
