/*
 * pdm_svc_adinputs.h
 *
 *  Created on: 26 de abr de 2023
 *      Author: breno
 */

#ifndef __SVC_ADINPUTS_H_
#define __SVC_ADINPUTS_H_

//#include "opdm_hal.h"
#include "opdm_hal.h"
#include "opdm_cfg.h"

typedef struct{
	PDMHAL_AnalogInputType position;
	char label[MAX_IO_LABEL_SIZE];
	uint8_t enable;
	uint32_t value;
	OPDM_INPUT_TYPE input_type;
}OPDM_INPUT_STRUCT; // talvez tenha que usar union

extern OPDM_INPUT_STRUCT AD_INPUTS[NUM_OF_AD_INPUTS];
void SVC_AD_Inputs_Init(void);
void SVC_AD_UpdateADInputs(void);
//typedef struct{
//
//}InputType_LinearAnalog;


#endif /* INC_PDM_SVC_ADINPUTS_H_ */
