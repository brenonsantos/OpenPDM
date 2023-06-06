/*
 * input.component.h
 *
 *  Created on: Jun 6, 2023
 *      Author: breno
 */

#ifndef __OUTPUT_COMPONENT_H
#define __OUTPUT_COMPONENT_H

#include "opdm_cfg.h"
#include "pdm_rte.h"

void ResetOutput(CurrentOutputsTypedef output);

typedef struct{
	uint8_t output_state;
	uint8_t fault;
	uint8_t fault_buffer;
	uint32_t current_reading;
	uint32_t voltage_reading;
	uint32_t peak_current;
	uint32_t inrush_timer;
	uint8_t retry_attempts;
	uint32_t retry_timer;
}OutputControlTypedef;


typedef enum{
	NO_FAULT = 0,
	INRUSH_STATE,
	OVERCURRENT_STATE,
	OVERVOLTAGE_STATE,
	UNDERVOLTAGE_STATE
}OutputFaultStateTypedef;

typedef enum{
	OUTPUT_OK,
	OUTPUT_WAITING_FOR_RESET,
	OUTPUT_FAULT,
	OUTPUT_DISABLED,
}OutputStateTypedef;

extern OutputControlTypedef CURRENT_OUTPUT_CONTROL[NUM_OF_OUTPUTS];
// extern OPDM_CURRENT_OUTPUT_SETUP_STRUCT CURRENT_OUTPUT_SETUP[NUM_OF_CURRENT_OUTPUTS];

OutputStateTypedef CalculateOutputState(CurrentOutputsTypedef output);

#endif /* __OUTPUT_COMPONENT_H */
