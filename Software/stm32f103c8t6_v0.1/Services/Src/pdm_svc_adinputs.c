

#include "pdm_svc_adinputs.h"
#include <string.h>

OPDM_INPUT_STRUCT AD_INPUTS[NUM_OF_AD_INPUTS];

void SVC_AD_Inputs_Init(){

	ANALOG_DIGITAL_INPUT_TYPE AD_INPUT_POSITION_CFG[NUM_OF_AD_INPUTS] = {
		ANALOG_DIGITAL_INPUT_0, ANALOG_DIGITAL_INPUT_1, ANALOG_DIGITAL_INPUT_2, ANALOG_DIGITAL_INPUT_3,
		ANALOG_DIGITAL_INPUT_4, ANALOG_DIGITAL_INPUT_5, ANALOG_DIGITAL_INPUT_6, ANALOG_DIGITAL_INPUT_7
	};

	uint8_t INPUT_ENABLE_CFG[NUM_OF_AD_INPUTS] = {
            INPUT0_EN, INPUT1_EN, INPUT2_EN, INPUT3_EN,
			INPUT4_EN, INPUT5_EN, INPUT6_EN, INPUT7_EN
    };

	char INPUT_LABEL_CFG[NUM_OF_AD_INPUTS][MAX_IO_LABEL_SIZE] = {
			INPUT0_LABEL, INPUT1_LABEL, INPUT2_LABEL, INPUT3_LABEL,
			INPUT4_LABEL, INPUT5_LABEL, INPUT6_LABEL, INPUT7_LABEL
	};

	char INPUT_TYPE_CFG[NUM_OF_AD_INPUTS] = {
			INPUT0_TYPE, INPUT1_TYPE, INPUT2_TYPE, INPUT3_TYPE,
			INPUT4_TYPE, INPUT5_TYPE, INPUT6_TYPE, INPUT7_TYPE
	};

	for(int i = 0; i < NUM_OF_AD_INPUTS; i++){
		AD_INPUTS[i].value = 0;
		AD_INPUTS[i].position = AD_INPUT_POSITION_CFG[i];
		AD_INPUTS[i].enable = INPUT_ENABLE_CFG[i];
		strcpy(AD_INPUTS[i].label, INPUT_LABEL_CFG[i]);
		AD_INPUTS[i].input_type = INPUT_TYPE_CFG[i];
	}
}

uint8_t isAdInputEnable(ANALOG_DIGITAL_INPUT_TYPE input){
	return AD_INPUTS[input].enable;
}

ANALOG_DIGITAL_INPUT_TYPE getNextEnabledInput(ANALOG_DIGITAL_INPUT_TYPE current_input){
	for(ANALOG_DIGITAL_INPUT_TYPE i = current_input+1; i < NUM_OF_AD_INPUTS; i++){
		if(isAdInputEnable(i)) return i;
	}
	for(ANALOG_DIGITAL_INPUT_TYPE i = 0; i <= current_input; i++){
		if(isAdInputEnable(i)) return i;
	}
	return 0;
}



void SVC_AD_UpdateADInputs(void){ //provavelmente um serviço ou RTE
	static uint8_t sample_index = 0, first_update_call = TRUE;
	static ANALOG_DIGITAL_INPUT_TYPE current_input = 0;;
	static uint32_t reading = 0;

//	if(first_update_call){
//		current_input = getNextEnabledInput(NUM_OF_AD_INPUTS);
//		PDMHAL_ADC_StartNewInputADC(current_input);
//		first_update_call = FALSE;
//		return;
//	}

	PDMHAL_AdcStatusType conversion_status = PDMHAL_ADC_CheckConversionStatusInput();
	switch(conversion_status){
		case(BUSY):
			return;
		case(CONVERSION_COMPLETE):
			reading += PDMHAL_ADC_ReadInput();

			/* The final value is a mean of ADC_SAMPLE_COUNT measurements */
			sample_index++;
			if(sample_index < ADC_SAMPLE_COUNT){
				PDMHAL_ADC_StartInputADC();
				return;
			}
			reading = reading/ADC_SAMPLE_COUNT;
			AD_INPUTS[current_input].value = reading;

			current_input = getNextEnabledInput(current_input);
			PDMHAL_ADC_StartNewInputADC(current_input);
			break;
		case(READY):
			current_input = getNextEnabledInput(NUM_OF_AD_INPUTS);
			PDMHAL_ADC_StartNewInputADC(current_input);
			break;
	}

}
