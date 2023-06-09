/*
 * pdm_rte_output.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */


#include "pdm_rte_outputhandler.h"

static CurrentOutputsTypedef reading_index = NUM_OF_OUTPUTS;

CurrentOutputsTypedef RTE_OUTPUT_GetNextEnabled(CurrentOutputsTypedef index);
void SetOutputPowerState(CurrentOutputsTypedef outputIndex, OutputPowerStateTypedef powerState);

void RTE_OUTPUT_init(void){
	reading_index = RTE_OUTPUT_GetNextEnabled(reading_index);
	OUTPUT_initOutputs();
}

void RTE_OUTPUT_UpdateFault(void){
	OUTPUT_UpdateFaults(reading_index);
	reading_index = RTE_OUTPUT_GetNextEnabled(reading_index);
}

CurrentOutputsTypedef RTE_OUTPUT_GetNextEnabled(CurrentOutputsTypedef index){
	for(CurrentOutputsTypedef i = index+1; i < NUM_OF_OUTPUTS; i++){
		if(OUTPUT_isOutputEnable(i)) return i;
	}
	for(CurrentOutputsTypedef i = 0; i <= index; i++){
		if(OUTPUT_isOutputEnable(i)) return i;
	}
	return 0;
}


uint8_t RTE_OUTPUT_UpdateSense(void){
	static uint8_t is_reading_voltage = FALSE, first_cycle_flag = TRUE;

	if (first_cycle_flag){
		first_cycle_flag = FALSE;
		PDMHAL_ADC_StartNewCurrentReading(reading_index);
		return FALSE;
	}

	/* This piece handles the output's voltage and current readings
	 *
	 * It isn't possible to read voltage and current at the same time (ADC limitation)
	 * so, if it is reading voltage, it must wait until the reading is done
	 * to start a new current reading.
	 * Also, if the output isn't ON, it must skip the voltage reading
	*/
	if (is_reading_voltage){
		if (OUTPUT_PollVoltageSense(reading_index)){
			PDMHAL_ADC_StartNewCurrentReading(reading_index);
			is_reading_voltage = FALSE;
			// Voltage and current readings are done
			return TRUE; 
		}
		// If it is reading voltage, it must wait until the reading is done
		return FALSE; 

	if (OUTPUT_PollCurrentSense(reading_index)){
		if (OUTPUT_getPowerState(reading_index)){
			PDMHAL_ADC_StartNewVoltageReading(reading_index);
			is_reading_voltage = TRUE;
			// Current reading is done, but voltage reading must be done
			return FALSE; 
		}

		PDMHAL_ADC_StartNewCurrentReading(reading_index);
		is_reading_voltage = FALSE;
		// Current reading is done and voltage reading isn't needed
		return TRUE; 
	}
	// If it is reading current, it must wait until the reading is done
	return FALSE; 
	}
	return FALSE;
}

void RTE_OUTPUT_WriteOutputs(void){
	static CurrentOutputsTypedef writing_index = NUM_OF_OUTPUTS;
	writing_index = RTE_OUTPUT_GetNextEnabled(writing_index);

	// This is being done with a switch to define new behavior for each fault in the future, if needed
	switch(OUTPUT_CalculateState(writing_index)){
		case OUTPUT_OK:
			break;
		case OUTPUT_FAULT:
		case OUTPUT_WAITING_FOR_RESET:
		case OUTPUT_DISABLED:
			SetOutputPowerState(writing_index, OUTPUT_OFF);
			return;
	}

	SetOutputPowerState(writing_index, CURRENT_OUTPUT_SETUP[writing_index].condition_callback());
}

void SetOutputPowerState(CurrentOutputsTypedef outputIndex, OutputPowerStateTypedef powerState){
	OUTPUT_SetPowerState(outputIndex, powerState);

	if (powerState){
		PDMHAL_SetCurrentOutput(outputIndex);
	} else {
		PDMHAL_ResetCurrentOutput(outputIndex);
	}

}








