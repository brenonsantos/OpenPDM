/*
 * pdm_rte_output.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */


#include "pdm_rte_outputhandler.h"



CurrentOutputsTypedef RTE_OUTPUT_GetNextEnabled(CurrentOutputsTypedef index);
void SetOutputPowerState(CurrentOutputsTypedef outputIndex, OutputPowerStateTypedef powerState);

void RTE_OUTPUT_init(void){
//	reading_index = RTE_OUTPUT_GetNextEnabled(reading_index);
	OUTPUT_initOutputs();
}

void RTE_OUTPUT_UpdateFault(void){
	static CurrentOutputsTypedef index = NUM_OF_OUTPUTS;
	index = RTE_OUTPUT_GetNextEnabled(index);
	OUTPUT_UpdateFaults(index);

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


uint8_t RTE_OUTPUT_UpdateSense (void) {
  static uint8_t is_reading_voltage = FALSE, first_cycle_flag = TRUE;
  static CurrentOutputsTypedef reading_index = NUM_OF_OUTPUTS;
  static const uint8_t DEBUG_ReadVoltage = FALSE;

  if (first_cycle_flag) {
	first_cycle_flag = FALSE;
	reading_index = RTE_OUTPUT_GetNextEnabled (reading_index);
	PDMHAL_ADC_StartNewCurrentReading (reading_index);
	return FALSE;
  }

  /* This piece handles the output's voltage and current readings
   *
   * It isn't possible to read voltage and current at the same time (using the same multiplexer)
   * so, if it is reading voltage, it must wait until the reading is done
   * to start a new current reading.
   *
   * note: there is a mistake in OPDM V0.1 PCB, where the analog multiplexer circuit can output
   * voltages higher than 3V3 when reading voltage, so it MUST be disabled.
   */

  if (is_reading_voltage) {
	if (OUTPUT_PollVoltageSense (reading_index)) {
	  reading_index = RTE_OUTPUT_GetNextEnabled (reading_index);
	  PDMHAL_ADC_StartNewCurrentReading (reading_index);
	  is_reading_voltage = FALSE;

	  // Voltage and current readings are done
	  return TRUE;
	}
	// If it is reading voltage, it must wait until the reading is done
	return FALSE;
  }
  if (OUTPUT_PollCurrentSense (reading_index)) {

	if (DEBUG_ReadVoltage == FALSE){
	  reading_index = RTE_OUTPUT_GetNextEnabled (reading_index);
	  PDMHAL_ADC_StartNewCurrentReading(reading_index);
	  is_reading_voltage = FALSE;
	  return TRUE;
	}
	PDMHAL_ADC_StartNewVoltageReading (reading_index);
	is_reading_voltage = TRUE;
	// Current reading is done, but voltage reading must be done
	return FALSE;
  }
  // If it is reading current, it must wait until the reading is done
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

void RTE_OUTPUT_PowerOffAllOutputs(void){
  for(CurrentOutputsTypedef i = 0; i < NUM_OF_OUTPUTS; i++){
	SetOutputPowerState(i, OUTPUT_OFF);
  }
}


uint32_t RTE_OUTPUT_GetTotalCurrentDraw(void){
  /* The function calculates the total current draw by summing the current readings
   * from different output circuits. The high current circuits have a different mapping
   * compared to the low current circuit. The real amps value of the high current measurement
   * is double that of the low current circuit. To obtain the total current draw, the high current
   * is mapped to represent the same value as the low current measurement. Here's an example:
   *
   * hc_current = 20 Amps = 4095 (max current of this output)
   * lc_current = 10 Amps = 4095 (max current of this output)
   * total_current = lc_current + hc_current = 30 Amps = 4095 + 2 * 4095
   *
   * Check the Core>Inc>pdm_def.h LC_CURRENT_CONVERSION_TO_12BITS and HC_CURRENT_CONVERSION_TO_12BITS
   */
  uint32_t sum = 0;
  for(CurrentOutputsTypedef i = 0; i <= HC3; i++){
	  sum += 2*CURRENT_OUTPUT_CONTROL[i].current_reading;
  }
  for(CurrentOutputsTypedef i = HC3; i <= LC3; i++){
	  sum += CURRENT_OUTPUT_CONTROL[i].current_reading;
  }
  return sum;
}
void SetOutputPowerState(CurrentOutputsTypedef outputIndex, OutputPowerStateTypedef powerState){
	OUTPUT_SetPowerState(outputIndex, powerState);

	if (powerState){
		PDMHAL_SetCurrentOutput(outputIndex);
	} else {
		PDMHAL_ResetCurrentOutput(outputIndex);
	}

}








