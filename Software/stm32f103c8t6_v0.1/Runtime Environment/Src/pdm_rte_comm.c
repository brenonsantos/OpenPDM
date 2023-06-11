/*
 * pdm_rte_can.c
 *
 *  Created on: Jun 9, 2023
 *      Author: breno
 */


#include <pdm_rte_comm.h>

void COMM_SendCANData(void);

void RTE_COMM_ReceiveCommunicationData(){
  PDMHAL_CAN_MessageFrame tmpCanMsg;

  // There isn't new messages
  if(!SVC_CAN_Receive(&tmpCanMsg)){
	return;
  }


  for (CanBusTransmiterType i = 0; i < NUM_OF_CAN_TRANSMITERS; i++){
	PDMHAL_CAN_MessageFrame* receiver = &CANBUS_RECEIVER_FRAMES[i].frame;

	if (receiver->frame.CANBus != tmpCanMsg.frame.CANBus){
	  continue;
	}
	if (receiver->frame.idType != tmpCanMsg.frame.idType){
	  continue;
	}
	if (receiver->frame.id != tmpCanMsg.frame.id){
	  continue;
	}

	// CANBus, idType and id of the new message is the same as the input struct
	// Copy the new data and set the message received flag
	receiver->frame.dataLengthCode = tmpCanMsg.frame.dataLengthCode;
	for (uint8_t i = 0; i < receiver->frame.dataLengthCode; i++){
	  receiver->frame.data[i] = tmpCanMsg.frame.data[i];
	}

	CANBUS_RECEIVER_FRAMES[i].status = CAN_MSG_RECEIVED;
  }

}

void RTE_COMM_SendCommunicationData(){
  COMM_SendCANData();
}

void COMM_SendCANData(void){
  static uint32_t elapsedTimeSinceLastMsg[NUM_OF_CAN_TRANSMITERS];
  uint32_t tick = HAL_GetTick();

  for (CanBusTransmiterType i = 0; i < NUM_OF_CAN_TRANSMITERS; i++){
	uint32_t period_ms = 1000/(uint32_t)CANBUS_TRANSMITER_FRAMES[i].frequency_hz;

	if (tick - elapsedTimeSinceLastMsg[i] > period_ms){
	  elapsedTimeSinceLastMsg[i] = HAL_GetTick();
	  CANBUS_TRANSMITER_FRAMES[i].callback(&CANBUS_TRANSMITER_FRAMES[i].frame);
	}
  }
}

void RTE_CAN_OUTPUT_Transmit(PDMHAL_CAN_MessageFrame* frame){
  SVC_CAN_Transmit(frame);
}






