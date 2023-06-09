/*
 * pdm_hal_canb.h
 *
 *  Created on: Jun 8, 2023
 *      Author: breno
 */

#ifndef INC_PDM_HAL_CANB_H_
#define INC_PDM_HAL_CANB_H_

#include "pdm_hal_def.h"



HAL_StatusTypeDef PDMHAL_CANB_Init(void);
HAL_StatusTypeDef PDMHAL_CANB_Transmit(PDMHAL_CAN_MessageFrame *tmpCanMsg);
PDMHAL_CAN_MessageFrame *PDMHAL_CANB_Receive(void);
HAL_StatusTypeDef PDMHAL_CANB_NewConfigFilter (CAN_FilterTypeDef *newFilter);


#endif /* INC_PDM_HAL_CANB_H_ */
