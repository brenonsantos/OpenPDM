/*
 * pdm_svc_adinputs.h
 *
 *  Created on: 26 de abr de 2023
 *      Author: breno
 */

#ifndef __SVC_ADINPUTS_H_
#define __SVC_ADINPUTS_H_

#include "opdm_hal.h"
//#include "opdm_cfg.h"


PDMHAL_AdcStatusType SVC_GetConversionStatusInput(void);
uint32_t SVC_ReadInput(AnalogDigitalInputType reading_index);

//typedef struct{
//
//}InputType_LinearAnalog;


#endif /* INC_PDM_SVC_ADINPUTS_H_ */
