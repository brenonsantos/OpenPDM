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
       CURRENT_OUTPUT_CONTROL[i].voltage_reading = VOLTAGE_CONVERSION_TO_12BITS(12.0f); // init with the nominal battery voltage
       CURRENT_OUTPUT_CONTROL[i].current_limit = 0;
       CURRENT_OUTPUT_CONTROL[i].inrush_timer = 0;
       CURRENT_OUTPUT_CONTROL[i].retry_attempts = 0;
	   CURRENT_OUTPUT_CONTROL[i].retry_timer = 0;
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


// TODO: fix
void RTE_WriteOutputState(CurrentOutputsTypedef output, OutputStateTypedef state){
//	if (CURRENT_OUTPUT_CONTROL[output].fault){
//		CURRENT_OUTPUT_CONTROL[output].output_state = FALSE;
//		return;
//	}
	CURRENT_OUTPUT_CONTROL[output].output_state = state;
}

OutputFaultStateTypedef CheckFaultCondition(CurrentOutputsTypedef output){
	RTE_OutputControlTypedef* output_control = &CURRENT_OUTPUT_CONTROL[output];


//	if (output_control->voltage_reading > CURRENT_OUTPUT_SETUP[output].max_voltage){
//		return OVERVOLTAGE_STATE;
//	}
//	if (output_control->voltage_reading < CURRENT_OUTPUT_SETUP[output].min_voltage){
//		return UNDERVOLTAGE_STATE;
//	}

	/* The following code checks if the output current reading is above the current limit:
	 *
	 * If it is, it checks if the fault flag is active, meaning that the fault has already been detected, 
	 * If it is not, it checks if the fault buffer flag is active, meaning that the inrush current is being detected
	 * If it is, it checks if the inrush time limit has been reached, meaning that a fault has just happened
	 * If it is not, it sets the inrush timer and returns the inrush state
	 */ 
	if (output_control->current_reading > CURRENT_OUTPUT_SETUP[output].current_limit){
		if (output_control->fault){
			return OVERCURRENT_STATE;
		} 
		if (output_control->fault_buffer){
			uint32_t time_since_inrush_detection = HAL_GetTick() - output_control->inrush_timer;

			if (time_since_inrush_detection > CURRENT_OUTPUT_SETUP[output].inrush_time_limit_miliseconds){
				return OVERCURRENT_STATE;
			}

		return INRUSH_STATE;
		}
		output_control->inrush_timer = HAL_GetTick();
		return INRUSH_STATE;	
	}

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
//			CURRENT_OUTPUT_CONTROL[output].fault = FALSE; // There are conditions to reset a fault
			CURRENT_OUTPUT_CONTROL[output].fault_buffer = FALSE;
			break;
	}
 }

void RTE_ResetFault(output){
	CURRENT_OUTPUT_CONTROL[output].fault = FALSE;
}

OutputStateTypedef RTE_CalculateOutputState(CurrentOutputsTypedef output){
	RTE_OutputControlTypedef* output_control = &CURRENT_OUTPUT_CONTROL[output];

	if(!CURRENT_OUTPUT_SETUP[output].enable){
		RTE_WriteOutputState(output, OUTPUT_DISABLED);
		return OUTPUT_DISABLED;
	}
	
	if (!CURRENT_OUTPUT_SETUP[output].reset_enable && output_control->fault){
		RTE_WriteOutputState(output, OUTPUT_FAULT);
		return OUTPUT_FAULT;
	}

	if (output_control->fault && CURRENT_OUTPUT_SETUP[output].reset_enable){

		if (output_control->retry_attempts >= CURRENT_OUTPUT_SETUP[output].reset_retry_attempts){
			RTE_WriteOutputState(output, OUTPUT_FAULT);
			return OUTPUT_FAULT;
		}

		if (output_control->output_state != OUTPUT_WAITING_FOR_RESET){
			output_control->retry_timer = HAL_GetTick();
			RTE_WriteOutputState(output, OUTPUT_WAITING_FOR_RESET);
			return OUTPUT_WAITING_FOR_RESET;
		}


		uint32_t time_since_reset_request = HAL_GetTick() - output_control->retry_timer;
		if(time_since_reset_request < CURRENT_OUTPUT_SETUP[output].reset_retry_delay_seconds*1000){
			RTE_WriteOutputState(output, OUTPUT_WAITING_FOR_RESET);
			return OUTPUT_WAITING_FOR_RESET;
		}

		output_control->retry_attempts++;
		output_control->retry_timer = 0;
		RTE_WriteOutputState(output, OUTPUT_OK);
		RTE_ResetFault(output);
		return OUTPUT_OK;
	}

	RTE_WriteOutputState(output, OUTPUT_OK);
	return OUTPUT_OK;
}
