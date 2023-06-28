/*
 * pdm_svc_init.h
 *
 *  Created on: 27 de abr de 2023
 *      Author: breno
 */

#ifndef __SVC_INIT_H_
#define __SVC_INIT_H_

//#include "pdm_hal.h"
#include "pdm_svc_can.h"
#include "opdm_cfg.h"



typedef enum{
  PDM_FAULT,
  PDM_OK,
  PDM_SLEEP
}PDM_Status;

void SVC_Init(void);

PDM_Status SVC_PDM_UpdateSystemIntegrity(void);
void SVC_PDM_SendSystemIntegrityFault(void);


#endif /* INC_PDM_SVC_INIT_H_ */
