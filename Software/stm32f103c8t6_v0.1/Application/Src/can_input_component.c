/*
 * can_input_component.c
 *
 *  Created on: Jun 9, 2023
 *      Author: breno
 */

#include "can_input_component.h"

CANBusReceiverTypedef CANBUS_RECEIVER_FRAMES[NUM_OF_CAN_RECEIVERS];


uint8_t CANBUS_RECEIVER_ProcessReceivedCANFrame(PDMHAL_CAN_MessageFrame *received_frame, CanBusReceiverType reicever_id){
  PDMHAL_CAN_MessageFrame* receiver = &CANBUS_RECEIVER_FRAMES[reicever_id].frame;
  if (received_frame->frame.CANBus != receiver->frame.CANBus ) {
	return FALSE;
  }
  if (receiver->frame.idType != received_frame->frame.idType){
	return FALSE;
  }
  if (receiver->frame.id != received_frame->frame.id){
	return FALSE;;
  }

	// CANBus, idType and id of the new message is the same as the input struct
	// Copy the new data and set the message received flag
	receiver->frame.dataLengthCode = received_frame->frame.dataLengthCode;
	for (uint8_t i = 0; i < receiver->frame.dataLengthCode; i++){
	  receiver->frame.data[i] = received_frame->frame.data[i];
	}

	CANBUS_RECEIVER_FRAMES[reicever_id].status = CAN_MSG_RECEIVED;
  return TRUE;
}
