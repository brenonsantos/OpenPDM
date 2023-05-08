/*
 * pdm_rte_output.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */


/*
 * pdm_svc_currentoutputs.c
 *
 *  Created on: 28 de abr de 2023
 *      Author: breno
 */


#include "pdm_rte_outputhandler.h"
#include <string.h>

RTE_OutputControlTypedef CURRENT_OUTPUT_CONTROL[NUM_OF_OUTPUTS];

void RTE_OutputsInit(){
	for(CurrentOutputsTypedef i = 0; i < NUM_OF_OUTPUTS; i++){
       CURRENT_OUTPUT_CONTROL[i].output_state = FALSE;
       CURRENT_OUTPUT_CONTROL[i].fault = FALSE;
       CURRENT_OUTPUT_CONTROL[i].fault_buffer = FALSE;
       CURRENT_OUTPUT_CONTROL[i].current_reading = 0;
       CURRENT_OUTPUT_CONTROL[i].voltage_reading = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(12.0f, 14.4f); // 14.4 -> nominal batery voltage?
       CURRENT_OUTPUT_CONTROL[i].current_limit = 0;
       CURRENT_OUTPUT_CONTROL[i].inrush_timer = 0;
       CURRENT_OUTPUT_CONTROL[i].retry_attempts = 0;
   }
}

uint8_t isOutputEnable(CurrentOutputsTypedef output_addr){
	return CURRENT_OUTPUT_SETUP[output_addr].enable;
}

CurrentOutputsTypedef getNextEnabledOutput(CurrentOutputsTypedef current_output){
	for(CurrentOutputsTypedef i = current_output+1; i < NUM_OF_OUTPUTS; i++){
		if(isOutputEnable(i)) return i;
	}
	for(CurrentOutputsTypedef i = 0; i <= current_output; i++){
		if(isOutputEnable(i)) return i;
	}
	return 0;
}

uint8_t PollVoltageSense(CurrentOutputsTypedef reading_index){
	static uint32_t reading = 0;

	PDMHAL_AdcStatusType conversion_status = SVC_GetConversionStatusVoltage();
	switch(conversion_status){
		case(BUSY):
			return FALSE;
		case(CONVERSION_COMPLETE):
			reading = SVC_ReadVoltage(reading_index);
			CURRENT_OUTPUT_CONTROL[reading_index].voltage_reading = reading;
			return TRUE;
		case(READY):
			return FALSE;
	}
	return FALSE;
}

uint8_t PollCurrentSense(CurrentOutputsTypedef reading_index){
	static uint32_t reading = 0;

	PDMHAL_AdcStatusType conversion_status = SVC_GetConversionStatusCurrent();
	switch(conversion_status){
		case(BUSY):
			break;
		case(CONVERSION_COMPLETE):
			reading = SVC_ReadCurrent(reading_index);
			CURRENT_OUTPUT_CONTROL[reading_index].current_reading = reading;
			return TRUE;
		case(READY):
			break;
	}
	return FALSE;
}


void RTE_PollOutputs(void){
	static CurrentOutputsTypedef reading_index = 0;
	static uint8_t is_reading_voltage = FALSE, first_cycle_flag = TRUE;

	if (first_cycle_flag){
		first_cycle_flag = FALSE;
		reading_index = getNextEnabledOutput(NUM_OF_OUTPUTS);
		PDMHAL_ADC_StartNewCurrentReading(reading_index);
		return;
	}

	if (is_reading_voltage){
		if (PollVoltageSense(reading_index)){
			is_reading_voltage = FALSE;
			reading_index = getNextEnabledOutput(reading_index);
			PDMHAL_ADC_StartNewCurrentReading(reading_index);
		}
	}
	else{
		if (PollCurrentSense(reading_index)){
			is_reading_voltage = TRUE;
			PDMHAL_ADC_StartNewVoltageReading(reading_index);
		}
	}
}

void RTE_WriteOutputState(CurrentOutputsTypedef output, StateTypedef state){
	if (CURRENT_OUTPUT_CONTROL[output].fault){
		CURRENT_OUTPUT_CONTROL[output].output_state = FALSE;
		return;
	}
	CURRENT_OUTPUT_CONTROL[output].output_state = state;
}

OutputFaultStateTypedef CheckFaultCondition(CurrentOutputsTypedef output){
	RTE_OutputControlTypedef* output_control = &CURRENT_OUTPUT_CONTROL[output];
	uint32_t tickstart = 0U;
	tickstart = HAL_GetTick();
//
//	if (output_control->voltage_reading > CURRENT_OUTPUT_SETUP[output].max_voltage){
//		return OVERVOLTAGE_STATE;
//	}
//	if (output_control->voltage_reading < CURRENT_OUTPUT_SETUP[output].min_voltage){
//		return UNDERVOLTAGE_STATE;
//	}
//
	// checks if there is overcurrent
	if (output_control->current_reading > CURRENT_OUTPUT_SETUP[output].current_limit){
		if (output_control->fault){
			return OVERCURRENT_STATE;
		}
		/* if there is overcurrent, checks if the fault flag is active, 
		*  meaning an inrush current is being detected
		*/ 
		if (output_control->fault_buffer){
			uint32_t time_since_inrush_detection = tickstart - output_control->inrush_timer;

			if (time_since_inrush_detection > CURRENT_OUTPUT_SETUP[output].inrush_time_limit_miliseconds){
				return OVERCURRENT_STATE;
			} // end of comparison between inrush detection and inrush time limit
		return INRUSH_STATE;
		}else{
			output_control->inrush_timer = HAL_GetTick();
			return INRUSH_STATE;
		} // end of check if fault flag is active

		// if the fault flag is not active, it means that the fault has just happened
//		if (!output_control->fault_buffer){
//
//		}

	} // end of check for overcurrent
	output_control->inrush_timer = 0;
	return NO_FAULT;
}

void RTE_UpdateFaultState(CurrentOutputsTypedef output){
	OutputFaultStateTypedef fault_status = CheckFaultCondition(output);

	switch(fault_status){
		case(OVERCURRENT_STATE):
			CURRENT_OUTPUT_CONTROL[output].fault = TRUE;
			CURRENT_OUTPUT_CONTROL[output].fault_buffer = FALSE;
			break;
		case(INRUSH_STATE):
			CURRENT_OUTPUT_CONTROL[output].fault = FALSE;
			CURRENT_OUTPUT_CONTROL[output].fault_buffer = TRUE;
			break;
		case(OVERVOLTAGE_STATE):
			CURRENT_OUTPUT_CONTROL[output].fault = TRUE;
			break;
		case(UNDERVOLTAGE_STATE):
			CURRENT_OUTPUT_CONTROL[output].fault = TRUE;
			break;
		case(NO_FAULT):
			CURRENT_OUTPUT_CONTROL[output].fault = FALSE;
			CURRENT_OUTPUT_CONTROL[output].fault = FALSE;
			break;
	}
}

