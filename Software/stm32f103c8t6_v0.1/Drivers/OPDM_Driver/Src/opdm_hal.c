/*
 * opdm_hal.c
 *
 *  Created on: 27 de abr de 2023
 *      Author: breno
 */


#include "opdm_hal.h"


void PDMHAL_Init(void){
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();


	PDMHAL_ADC_Init();
	/* Initi  */
}
