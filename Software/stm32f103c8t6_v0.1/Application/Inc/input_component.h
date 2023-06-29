/*
 * input_component.h
 *
 *  Created on: Jun 6, 2023
 *      Author: breno
 */

#ifndef INC_INPUT_COMPONENT_H_
#define INC_INPUT_COMPONENT_H_

#include "opdm_cfg.h"
#include "pdm_rte.h"

#define MAX_LABEL_SIZE 4


typedef struct{
	const char label[MAX_LABEL_SIZE];
	const uint8_t enable;
    uint32_t value;
	const OPDM_INPUT_TYPE input_type;
}InputConfigTypedef; // talvez tenha que usar union

extern InputConfigTypedef ANALOG_DIGITAL_INPUT[NUM_OF_AD_INPUTS];
uint8_t INPUT_isInputEnable(AnalogDigitalInputType input);




#endif /* INC_INPUT_COMPONENT_H_ */
