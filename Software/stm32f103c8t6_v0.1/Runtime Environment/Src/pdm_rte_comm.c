/*
 * pdm_rte_can.c
 *
 *  Created on: Jun 9, 2023
 *      Author: breno
 */


#include <pdm_rte_comm.h>


void COMM_SendCANData(void);
void COMM_SendUSBData(void);

void RTE_COMM_ReceiveCommunicationData(){


  PDMHAL_CAN_MessageFrame tmpCanMsg;
  // Check if there is new messages
  if(!SVC_CAN_Receive(&tmpCanMsg)){
	return;
  }

  for (CanBusReceiverType i = 0; i < NUM_OF_CAN_RECEIVERS; i++){
	CANBUS_RECEIVER_ProcessReceivedCANFrame(&tmpCanMsg, i);
  }
}

void RTE_COMM_SendCommunicationData(){
  COMM_SendCANData();
#if USE_USB_OVER_CANB
	COMM_SendUSBData();
#endif
}

void COMM_SendCANData(void){
  static uint32_t elapsedTimeSinceLastMsg[NUM_OF_CAN_TRANSMITERS];
  uint32_t tick = HAL_GetTick();

  for (CanBusTransmiterType i = 0; i < NUM_OF_CAN_TRANSMITERS; i++){
	uint32_t period_ms = (uint32_t)(1000/CANBUS_TRANSMITER_FRAMES[i].frequency_hz);

	if (tick - elapsedTimeSinceLastMsg[i] > period_ms){
	  elapsedTimeSinceLastMsg[i] = HAL_GetTick();
	  CANBUS_TRANSMITER_FRAMES[i].callback(&CANBUS_TRANSMITER_FRAMES[i].frame);
	}
  }
}

void RTE_CAN_OUTPUT_Transmit(PDMHAL_CAN_MessageFrame* frame){
  SVC_CAN_Transmit(frame);
}

void RTE_COMM_SendSystemIntegrityFault(void){
  SVC_PDM_SendSystemIntegrityFault();
}

void COMM_SendUSBData(void){

  USB_TransmitPDMStatus();
}






