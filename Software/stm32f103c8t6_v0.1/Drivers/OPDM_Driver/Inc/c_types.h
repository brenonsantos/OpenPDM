/*
 * c_types.h
 *
 *  Created on: 4 de abr de 2023
 *      Author: breno
 */

#ifndef __C_TYPES_H_
#define __C_TYPES_H_

#define ENABLE 1
#define DISABLE 0

#define TRUE 1
#define FALSE 0

typedef enum{
	DIGITAL_ACTIVE_H = 0,
	DIGITAL_ACTIVE_L,
	LINEAR_ANALOG,
	CALIBRATED_ANALOG,
	ROTARY_SWITCH,
	NUM_OF_INPUT_TYPES
}OPDM_INPUT_TYPE;

#endif /* OPDM_DRIVER_INC_C_TYPES_H_ */
