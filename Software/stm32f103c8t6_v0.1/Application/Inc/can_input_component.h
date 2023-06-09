/*
 * can_input_component.h
 *
 *  Created on: Jun 9, 2023
 *      Author: breno
 */

#ifndef __CAN_INPUT_COMPONENT_H_
#define __CAN_INPUT_COMPONENT_H_

#include "opdm_cfg.h"
#include "pdm_rte.h"



#define MAX_LABEL_SIZE 4

typedef struct{
  const char label[MAX_LABEL_SIZE];
  const PDMHAL_CAN_MessageFrame frame;
  const uint32_t timeout;
  const uint8_t frequency;
}CANBusReceiverTypedef;


extern CANBusReceiverTypedef CANBUS_RECEIVER_FRAMES[NUM_OF_CAN_RECEIVERS];
#endif /* __CAN_INPUT_COMPONENT_H_ */
