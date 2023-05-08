/*
 * pdm_rte_inputhandler.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */


#include "pdm_rte_inputhandler.h"
#include <string.h>

uint8_t isAdInputEnable(AnalogDigitalInputType input){
	return ANALOG_DIGITAL_INPUT[input].enable;
}

AnalogDigitalInputType getNextEnabledInput(AnalogDigitalInputType current_input){
	for(AnalogDigitalInputType i = current_input+1; i < NUM_OF_AD_INPUTS; i++){
		if(isAdInputEnable(i)) return i;
	}
	for(AnalogDigitalInputType i = 0; i <= current_input; i++){
		if(isAdInputEnable(i)) return i;
	}
	return 0;
}

void RTE_PollInputs(void){
	static AnalogDigitalInputType reading_index = 0;
	static uint32_t reading = 0;
	
    PDMHAL_AdcStatusType conversion_status = SVC_GetConversionStatusInput();
	switch(conversion_status){
		case(BUSY):
			return;
		case(CONVERSION_COMPLETE):
            reading = SVC_ReadInput(reading_index);
			ANALOG_DIGITAL_INPUT[reading_index].value = reading;

			reading_index = getNextEnabledInput(reading_index);
			break;
		case(READY):
			reading_index = getNextEnabledInput(NUM_OF_AD_INPUTS);
			break;
	}

	PDMHAL_ADC_StartNewInputReading(reading_index);
}

uint32_t RTE_ReadInputValue(AnalogDigitalInputType input){
	if (!isAdInputEnable(input))
		return 0;
   return ANALOG_DIGITAL_INPUT[input].value;
}
