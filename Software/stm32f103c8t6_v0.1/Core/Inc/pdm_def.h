/*
 * pdm_def.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */

#ifndef INC_PDM_DEF_H_
#define INC_PDM_DEF_H_


#define ENABLE 1
#define DISABLE 0

#define TRUE 1
#define FALSE 0

//typedef enum{
//	ON = 1,
//	OFF = 1
//}StateTypedef;


typedef enum{
	HC0,
	HC1,
	HC2,
	HC3,
	LC0,
	LC1,
	LC2,
	LC3,
	NUM_OF_OUTPUTS
}CurrentOutputsTypedef;

typedef enum{
	ANALOG_DIGITAL_INPUT_0 = 0,
	ANALOG_DIGITAL_INPUT_1,
	ANALOG_DIGITAL_INPUT_2,
	ANALOG_DIGITAL_INPUT_3,
	ANALOG_DIGITAL_INPUT_4,
	ANALOG_DIGITAL_INPUT_5,
	ANALOG_DIGITAL_INPUT_6,
	ANALOG_DIGITAL_INPUT_7,
	NUM_OF_AD_INPUTS
}AnalogDigitalInputType;

#endif /* INC_PDM_DEF_H_ */
