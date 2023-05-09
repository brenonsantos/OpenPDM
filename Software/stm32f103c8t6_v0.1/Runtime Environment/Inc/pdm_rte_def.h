/*
 * pdm_rte_def.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */

#ifndef INC_PDM_RTE_DEF_H_
#define INC_PDM_RTE_DEF_H_

#include "opdm_cfg.h"
#include "pdm_svc.h"



typedef struct{
	uint8_t output_state;
	uint8_t fault;
	uint8_t fault_buffer;
	uint32_t current_reading;
	float voltage_reading;
	float current_limit;
	uint32_t inrush_timer;
	uint8_t retry_attempts;
	uint32_t retry_timer;
}RTE_OutputControlTypedef;

// extern OPDM_CURRENT_OUTPUT_SETUP_STRUCT CURRENT_OUTPUT_SETUP[NUM_OF_CURRENT_OUTPUTS];
extern RTE_OutputControlTypedef CURRENT_OUTPUT_CONTROL[NUM_OF_OUTPUTS];


#endif /* INC_PDM_RTE_DEF_H_ */
