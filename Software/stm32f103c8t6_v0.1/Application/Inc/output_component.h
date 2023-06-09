/*
 * output_component.h
 *
 *  Created on: Jun 6, 2023
 *      Author: breno
 */

#ifndef __OUTPUT_COMPONENT_H
#define __OUTPUT_COMPONENT_H

#include "opdm_cfg.h"
#include "pdm_rte.h"

#define MAX_LABEL_SIZE 4

typedef uint8_t (*condition_t)(void);

typedef enum{
	NO_FAULT = 0,
	INRUSH_STATE,
	OVERCURRENT_STATE,
	OVERVOLTAGE_STATE,
	UNDERVOLTAGE_STATE
}OutputFaultStateTypedef;

typedef enum{
	OUTPUT_FAULT = 0,
	OUTPUT_OK,
	OUTPUT_WAITING_FOR_RESET,
	OUTPUT_DISABLED,
}OutputStateTypedef;

typedef enum{
	OUTPUT_OFF = 0,
	OUTPUT_ON,
}OutputPowerStateTypedef;

typedef struct {
    const uint8_t enable;
    const char *label;
    const uint8_t reset_enable;
    const uint8_t reset_retry_attempts;
    const uint8_t reset_retry_delay_seconds;
    const uint32_t current_limit;
    const uint32_t inrush_time_limit_miliseconds;
    const uint32_t max_voltage;
    const uint32_t min_voltage;
    const uint32_t max_current;
    condition_t condition_callback;
}CurrentOutputConfigTypedef;

typedef struct{
	OutputPowerStateTypedef power_state;
	OutputStateTypedef output_state;
	OutputFaultStateTypedef fault;
	uint8_t fault_buffer;
	uint32_t current_reading;
	uint32_t voltage_reading;
	uint32_t peak_current;
	uint32_t inrush_timer;
	uint8_t retry_attempts;
	uint32_t retry_timer;
}OutputControlTypedef;


extern OutputControlTypedef CURRENT_OUTPUT_CONTROL[NUM_OF_OUTPUTS];
extern const CurrentOutputConfigTypedef CURRENT_OUTPUT_SETUP[NUM_OF_OUTPUTS];
// extern OPDM_CURRENT_OUTPUT_SETUP_STRUCT CURRENT_OUTPUT_SETUP[NUM_OF_CURRENT_OUTPUTS];
void OUTPUT_initOutputs(void);
void OUTPUT_Reset(CurrentOutputsTypedef output);


uint8_t OUTPUT_PollCurrentSense(CurrentOutputsTypedef reading_index);
uint8_t OUTPUT_PollVoltageSense(CurrentOutputsTypedef reading_index);
OutputStateTypedef OUTPUT_CalculateState(CurrentOutputsTypedef output);;
void OUTPUT_ResetFault(CurrentOutputsTypedef output);
void OUTPUT_UpdateFaults(CurrentOutputsTypedef output);

uint8_t OUTPUT_isOutputEnable(CurrentOutputsTypedef output_addr);
OutputPowerStateTypedef OUTPUT_getPowerState(CurrentOutputsTypedef output);
void OUTPUT_SetPowerState(CurrentOutputsTypedef outputIndex, OutputPowerStateTypedef powerState);

#endif /* __OUTPUT_COMPONENT_H */
