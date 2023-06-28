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

typedef enum{
  CAN_MSG_NOT_RECEIVED = 0,
  CAN_MSG_RECEIVED,
  CAN_MSG_TIMEOUT
}CANBusReceivedMessageStatus;

typedef enum{
  CAN_MSG_SIZE_1FRAME = 0,
  CAN_MSG_SIZE_2FRAME,
  CAN_MSG_SIZE_4FRAME,
  CAN_MSG_SIZE_8FRAME
}CANBusFrameSize;

#define MAX_CAN_LABEL_SIZE 8

typedef struct{
  CANBusReceivedMessageStatus status;
  char label[MAX_CAN_LABEL_SIZE];
  PDMHAL_CAN_MessageFrame frame;
  uint32_t timeout_ms;
  CANBusFrameSize size;
}CANBusReceiverTypedef;



extern CANBusReceiverTypedef CANBUS_RECEIVER_FRAMES[NUM_OF_CAN_RECEIVERS];


uint8_t CANBUS_RECEIVER_ProcessReceivedCANFrame(PDMHAL_CAN_MessageFrame *received_frame, CanBusReceiverType reicever_id);

#endif /* __CAN_INPUT_COMPONENT_H_ */
