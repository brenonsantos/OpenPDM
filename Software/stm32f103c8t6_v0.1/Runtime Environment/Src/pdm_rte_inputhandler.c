/*
 * pdm_rte_inputhandler.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */


#include "pdm_rte_inputhandler.h"

AnalogDigitalInputType getNextEnabledInput(AnalogDigitalInputType current_input){
	for(AnalogDigitalInputType i = current_input+1; i < NUM_OF_AD_INPUTS; i++){
		if(INPUT_isInputEnable(i)) return i;
	}
	for(AnalogDigitalInputType i = 0; i <= current_input; i++){
		if(INPUT_isInputEnable(i)) return i;
	}
	return 0;
}

void RTE_INPUT_PollInputs (void) {
  static AnalogDigitalInputType reading_index = 0;


  PDMHAL_AdcStatusType conversion_status = PDMHAL_ADC_CheckConversionStatusInput ();
  switch (conversion_status) {
	case (BUSY):
	  return;
	case (CONVERSION_COMPLETE):
	  ANALOG_DIGITAL_INPUT[reading_index].value = PDMHAL_ADC_ReadInput(reading_index);
	  reading_index = getNextEnabledInput (reading_index);
	  break;
	case (READY):
	  break;
  }

  PDMHAL_ADC_StartNewInputReading (reading_index);
}

uint32_t RTE_ReadInputValue(AnalogDigitalInputType input){
	if (!INPUT_isInputEnable(input))
		return 0;
   return ANALOG_DIGITAL_INPUT[input].value;
}
