/*
 * pdm_svc_currentoutputs.h
 *
 *  Created on: 28 de abr de 2023
 *      Author: breno
 */

#ifndef INC_PDM_SVC_CURRENTOUTPUTS_H_
#define INC_PDM_SVC_CURRENTOUTPUTS_H_

#include <pdm_hal.h>
//#include "opdm_cfg.h"

PDMHAL_AdcStatusType SVC_GetConversionStatusVoltage(void);
PDMHAL_AdcStatusType SVC_GetConversionStatusCurrent(void);
uint32_t SVC_ReadVoltage(CurrentOutputsTypedef reading_index);
uint32_t SVC_ReadCurrent(CurrentOutputsTypedef reading_index);

#endif /* INC_PDM_SVC_CURRENTOUTPUTS_H_ */
