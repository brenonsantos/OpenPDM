/*
 * input_component.c
 *
 *  Created on: Jun 6, 2023
 *      Author: breno
 */

#include "output_component.h"

OutputControlTypedef CURRENT_OUTPUT_CONTROL[NUM_OF_OUTPUTS];

void OUTPUT_WriteOutputState(CurrentOutputsTypedef output, OutputStateTypedef state);

void OUTPUT_initOutputs(void){
	for(CurrentOutputsTypedef i = 0; i < NUM_OF_OUTPUTS; i++){
       CURRENT_OUTPUT_CONTROL[i].output_state = OUTPUT_OK;
       CURRENT_OUTPUT_CONTROL[i].fault = NO_FAULT;
       CURRENT_OUTPUT_CONTROL[i].fault_buffer = FALSE;
       CURRENT_OUTPUT_CONTROL[i].current_reading = 0;
       CURRENT_OUTPUT_CONTROL[i].voltage_reading = VOLTAGE_CONVERSION_TO_12BITS(14.0f); // init with the nominal battery voltage
       CURRENT_OUTPUT_CONTROL[i].peak_current = 0;
       CURRENT_OUTPUT_CONTROL[i].inrush_timer = 0;
       CURRENT_OUTPUT_CONTROL[i].retry_attempts = 0;
	   CURRENT_OUTPUT_CONTROL[i].retry_timer = 0;
   }
}

void OUTPUT_Reset(CurrentOutputsTypedef output){
		CURRENT_OUTPUT_CONTROL[output].output_state = OUTPUT_OK;
       	CURRENT_OUTPUT_CONTROL[output].fault = NO_FAULT;
       	CURRENT_OUTPUT_CONTROL[output].fault_buffer = FALSE;
       	CURRENT_OUTPUT_CONTROL[output].current_reading = 0;
       	CURRENT_OUTPUT_CONTROL[output].voltage_reading = VOLTAGE_CONVERSION_TO_12BITS(14.0f); // init with the nominal battery voltage
       	CURRENT_OUTPUT_CONTROL[output].peak_current = 0;
       	CURRENT_OUTPUT_CONTROL[output].inrush_timer = 0;
       	CURRENT_OUTPUT_CONTROL[output].retry_attempts = 0;
	   	CURRENT_OUTPUT_CONTROL[output].retry_timer = 0;
}

OutputStateTypedef OUTPUT_CalculateState(CurrentOutputsTypedef output){
	OutputControlTypedef* output_control = &CURRENT_OUTPUT_CONTROL[output];

	if(!CURRENT_OUTPUT_SETUP[output].enable){
		OUTPUT_WriteOutputState(output, OUTPUT_DISABLED);
		return OUTPUT_DISABLED;
	}

	if (!CURRENT_OUTPUT_SETUP[output].reset_enable && output_control->fault){
		OUTPUT_WriteOutputState(output, OUTPUT_FAULT);
		return OUTPUT_FAULT;
	}

	if (output_control->fault && CURRENT_OUTPUT_SETUP[output].reset_enable){

		if (output_control->retry_attempts >= CURRENT_OUTPUT_SETUP[output].reset_retry_attempts){
			OUTPUT_WriteOutputState(output, OUTPUT_FAULT);
			return OUTPUT_FAULT;
		}

		if (output_control->output_state != OUTPUT_WAITING_FOR_RESET){
			output_control->retry_timer = HAL_GetTick();
			OUTPUT_WriteOutputState(output, OUTPUT_WAITING_FOR_RESET);
			return OUTPUT_WAITING_FOR_RESET;
		}

		uint32_t time_since_reset_request = HAL_GetTick() - output_control->retry_timer;
		if(time_since_reset_request < CURRENT_OUTPUT_SETUP[output].reset_retry_delay_seconds*1000){
			OUTPUT_WriteOutputState(output, OUTPUT_WAITING_FOR_RESET);
			return OUTPUT_WAITING_FOR_RESET;
		}

		output_control->retry_attempts++;
		output_control->retry_timer = 0;
		OUTPUT_WriteOutputState(output, OUTPUT_OK);
		OUTPUT_ResetFault(output);
		return OUTPUT_OK;
	}

	OUTPUT_WriteOutputState(output, OUTPUT_OK);
	return OUTPUT_OK;
}

OutputFaultStateTypedef CheckCurrentCondition(CurrentOutputsTypedef output){
	OutputControlTypedef* output_control = &CURRENT_OUTPUT_CONTROL[output];
	/* The following code checks if the output current reading is above the current limit:
	 *
	 * If it is, it checks if the fault flag is active, meaning that the fault has already been detected,
	 * If it is not, it checks if the fault buffer flag is active, meaning that the inrush current is being detected
	 * If a inrush current is being detected, it checks if the inrush time limit has been reached, meaning that a fault has just happened
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

OutputFaultStateTypedef CheckVoltageCondition(CurrentOutputsTypedef output){
	OutputControlTypedef* output_control = &CURRENT_OUTPUT_CONTROL[output];

	if (output_control->voltage_reading > CURRENT_OUTPUT_SETUP[output].max_voltage){
		return OVERVOLTAGE_STATE;
	}
	if (output_control->voltage_reading < CURRENT_OUTPUT_SETUP[output].min_voltage){
		return UNDERVOLTAGE_STATE;
	}
	return NO_FAULT;
}

void OUTPUT_UpdateFaults(CurrentOutputsTypedef output){
	CURRENT_OUTPUT_CONTROL[output].fault = CheckCurrentCondition(output);
	if (CURRENT_OUTPUT_CONTROL[output].fault == NO_FAULT){
		CURRENT_OUTPUT_CONTROL[output].fault = CheckVoltageCondition(output);
	}

	switch(CURRENT_OUTPUT_CONTROL[output].fault){
		case(OVERCURRENT_STATE):
			CURRENT_OUTPUT_CONTROL[output].fault_buffer = FALSE;
			break;
		case(INRUSH_STATE):
			CURRENT_OUTPUT_CONTROL[output].fault_buffer = TRUE;
			break;
		case(OVERVOLTAGE_STATE):
			break;
		case(UNDERVOLTAGE_STATE):
			break;
		case(NO_FAULT):
			CURRENT_OUTPUT_CONTROL[output].fault_buffer = FALSE;
			break;
	}
 }


uint8_t OUTPUT_PollVoltageSense(CurrentOutputsTypedef reading_index){

	PDMHAL_AdcStatusType conversion_status = PDMHAL_ADC_CheckConversionStatusVoltage();
	switch(conversion_status){
		case(BUSY):
			return FALSE;
		case(CONVERSION_COMPLETE):
			CURRENT_OUTPUT_CONTROL[reading_index].voltage_reading = PDMHAL_ADC_ReadOutputVoltage(reading_index);
			return TRUE;
		case(READY):
			return FALSE;
	}
	return FALSE;
}

uint8_t OUTPUT_PollCurrentSense(CurrentOutputsTypedef reading_index){
	static uint32_t reading = 0;

	PDMHAL_AdcStatusType conversion_status = PDMHAL_ADC_CheckConversionStatusCurrent();
	switch(conversion_status){
		case(BUSY):
			break;
		case(CONVERSION_COMPLETE):
			reading = PDMHAL_ADC_ReadOutputCurrent(reading_index);
			CURRENT_OUTPUT_CONTROL[reading_index].current_reading = reading;

			if (reading > CURRENT_OUTPUT_CONTROL[reading_index].peak_current){
				CURRENT_OUTPUT_CONTROL[reading_index].peak_current = reading;
			}

			return TRUE;
		case(READY):
			break;
	}
	return FALSE;
}


void OUTPUT_WriteOutputState(CurrentOutputsTypedef output, OutputStateTypedef state){
	if (state == OUTPUT_OK && CURRENT_OUTPUT_CONTROL[output].fault != NO_FAULT){ // Just a redundant check
		CURRENT_OUTPUT_CONTROL[output].output_state = OUTPUT_FAULT;
	}
	CURRENT_OUTPUT_CONTROL[output].output_state = state;
}

uint8_t OUTPUT_isOutputEnable(CurrentOutputsTypedef output_addr){
	return CURRENT_OUTPUT_SETUP[output_addr].enable;
}

OutputPowerStateTypedef OUTPUT_getPowerState(CurrentOutputsTypedef output){
	return CURRENT_OUTPUT_CONTROL[output].power_state;
}

void OUTPUT_ResetFault(CurrentOutputsTypedef output){
	CURRENT_OUTPUT_CONTROL[output].fault = NO_FAULT;
}

void OUTPUT_ResetRetryAttempts(CurrentOutputsTypedef output){
	CURRENT_OUTPUT_CONTROL[output].retry_attempts = 0;
}

void OUTPUT_SetPowerState(CurrentOutputsTypedef outputIndex, OutputPowerStateTypedef powerState){
	CURRENT_OUTPUT_CONTROL[outputIndex].power_state = powerState;
}

