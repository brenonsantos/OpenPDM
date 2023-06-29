/*
 * input_component.c
 *
 *  Created on: Jun 6, 2023
 *      Author: breno
 */


#include "input_component.h"

uint8_t INPUT_isInputEnable(AnalogDigitalInputType input){
	return ANALOG_DIGITAL_INPUT[input].enable;
}
