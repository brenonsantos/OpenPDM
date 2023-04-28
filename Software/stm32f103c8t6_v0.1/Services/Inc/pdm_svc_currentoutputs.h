/*
 * pdm_svc_currentoutputs.h
 *
 *  Created on: 28 de abr de 2023
 *      Author: breno
 */

#ifndef INC_PDM_SVC_CURRENTOUTPUTS_H_
#define INC_PDM_SVC_CURRENTOUTPUTS_H_

//#include "opdm_hal.h"
#include "opdm_hal_io.h"
#include "opdm_cfg.h"



typedef struct{
	char output_label[MAX_IO_LABEL_SIZE];

	uint8_t output_enable;
	uint8_t reset_enable;
	// uint8_t pwm_enable;
	// OPDM_OUTPUT_PWM_TYPE pwm;
	int inrush_time_limit;
	int reset_retry_delay;
	int reset_retry_count;

	float current_setpoint;
	float max_current;
	float min_voltage;
	float max_voltage;

	condition_t condition_callback;

}OPDM_CURRENT_OUTPUT_SETUP_STRUCT;

typedef struct{
	uint8_t output_state;
	uint8_t fault;
	uint8_t fault_buffer;
	float current_reading;
	float voltage_reading;
	float current_setpoint;
	float inrush_timer;
	int retry_attempts;
}OPDM_CURRENT_OUTPUT_CONTROL_STRUCT;

extern OPDM_CURRENT_OUTPUT_SETUP_STRUCT CURRENT_OUTPUT_SETUP[NUM_OF_CURRENT_OUTPUTS];
extern OPDM_CURRENT_OUTPUT_CONTROL_STRUCT CURRENT_OUTPUT_CONTROL[NUM_OF_CURRENT_OUTPUTS];


#endif /* INC_PDM_SVC_CURRENTOUTPUTS_H_ */
