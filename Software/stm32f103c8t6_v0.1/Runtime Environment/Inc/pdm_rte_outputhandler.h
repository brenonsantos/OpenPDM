/*
 * pdm_outputhandler.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */

#ifndef INC_PDM_OUTPUTHANDLER_H_
#define INC_PDM_OUTPUTHANDLER_H_

#include "pdm_rte_def.h"



void RTE_PollOuputCurrentReading(void);
void RTE_UpdateFaults(CurrentOutputsTypedef output);

CurrentOutputsTypedef RTE_getNextEnabledOutput(CurrentOutputsTypedef current_output);
void RTE_ResetOutput(CurrentOutputsTypedef output);
void RTE_UpdateFaults(CurrentOutputsTypedef output);
void RTE_ResetFault(CurrentOutputsTypedef output);
void RTE_ResetRetryAttempts(CurrentOutputsTypedef output);



#endif /* INC_PDM_OUTPUTHANDLER_H_ */
