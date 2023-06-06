/*
 * opdm_hal.c
 *
 *  Created on: 27 de abr de 2023
 *      Author: breno
 */


#include <pdm_hal.h>


void PDMHAL_Init(void){
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();


	PDMHAL_ADC_Init();
	/* Initi  */
}

// moving average filter for adc readings
uint32_t moving_average(uint32_t *data, uint32_t new_sample, MOVING_AVERAGE_WINDOW_SIZE window_size){
	uint32_t sum = 0;
	for(int i = 0; i < window_size-1; i++){
		data[i] = data[i+1];
		sum += data[i];
	}
	data[window_size-1] = new_sample;
	sum += new_sample;
	return (sum / window_size);
}
