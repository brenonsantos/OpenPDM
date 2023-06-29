/*
 * pdm_can.h
 *
 *  Created on: Jun 8, 2023
 *      Author: breno
 */

#ifndef __PDM_CAN_H_
#define __PDM_CAN_H_

#include "pdm_hal.h"



uint8_t SVC_CAN_Transmit(PDMHAL_CAN_MessageFrame *tmpCanMsg);
uint8_t SVC_CAN_Receive(PDMHAL_CAN_MessageFrame *tmpCanMsg);


#endif /* __PDM_CAN_H_ */
