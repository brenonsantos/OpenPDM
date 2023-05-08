/*
 * pdm_outputhandler.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */

#ifndef INC_PDM_OUTPUTHANDLER_H_
#define INC_PDM_OUTPUTHANDLER_H_

#include "pdm_rte_def.h"

void RTE_OutputsInit(void);
void RTE_PollOutputs(void);
void RTE_UpdateFaultState(CurrentOutputsTypedef output);

typedef enum{
	NO_FAULT = 0,
	INRUSH_STATE,
	OVERCURRENT_STATE,
	OVERVOLTAGE_STATE,
	UNDERVOLTAGE_STATE
}OutputFaultStateTypedef;

#endif /* INC_PDM_OUTPUTHANDLER_H_ */
