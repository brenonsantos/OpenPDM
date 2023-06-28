/*
 * pdm_can.c
 *
 *  Created on: Jun 8, 2023
 *      Author: breno
 */


#include <pdm_svc_can.h>

uint8_t SVC_CAN_TransmitCanB(PDMHAL_CAN_MessageFrame *tmpCanMsg);
uint8_t SVC_CAN_TransmitCanC(PDMHAL_CAN_MessageFrame *tmpCanMsg);
PDMHAL_CAN_MessageFrame SVC_CAN_ReceiveCanB(void);
PDMHAL_CAN_MessageFrame SVC_CAN_ReceiveCanC(void);


uint8_t SVC_CAN_Transmit(PDMHAL_CAN_MessageFrame *tmpCanMsg){
  uint8_t error_code = 0;
  switch (tmpCanMsg->frame.CANBus){
	case CAN_B:
	  if (USE_USB_OVER_CANB){
		return 1;
	  }
	  return SVC_CAN_TransmitCanB(tmpCanMsg);
	case CAN_C:
	  return SVC_CAN_TransmitCanC(tmpCanMsg);
	default:
	  error_code = 1;
  }


  return error_code;
}

uint8_t SVC_CAN_Receive(PDMHAL_CAN_MessageFrame *tmpCanMsg){
  CANC_MSG tmpCanCMsg;
  if (PDMHAL_CANC_Receive(&tmpCanCMsg)){
	tmpCanMsg->frame.CANBus = CAN_C;
	tmpCanMsg->frame.dataLengthCode = tmpCanCMsg.frame.dlc;
	tmpCanMsg->frame.id = tmpCanCMsg.frame.id;
	tmpCanMsg->frame.idType = tmpCanCMsg.frame.idType;

	tmpCanMsg->frame.data[0] = tmpCanCMsg.frame.data0;
	tmpCanMsg->frame.data[1] = tmpCanCMsg.frame.data1;
	tmpCanMsg->frame.data[2] = tmpCanCMsg.frame.data2;
	tmpCanMsg->frame.data[3] = tmpCanCMsg.frame.data3;
	tmpCanMsg->frame.data[4] = tmpCanCMsg.frame.data4;
	tmpCanMsg->frame.data[5] = tmpCanCMsg.frame.data5;
	tmpCanMsg->frame.data[6] = tmpCanCMsg.frame.data6;
	tmpCanMsg->frame.data[7] = tmpCanCMsg.frame.data7;
	return TRUE;
  }
  
  if (!USE_USB_OVER_CANB){
	  PDMHAL_CAN_MessageFrame *tmpCanBMsg = PDMHAL_CANB_Receive();
	  if (tmpCanBMsg != NULL){
		tmpCanMsg = tmpCanBMsg;
		return TRUE;
	  }
  }

  return FALSE;
}


uint8_t SVC_CAN_TransmitCanC(PDMHAL_CAN_MessageFrame *tmpCanMsg){

  CANC_MSG msg;
  msg.frame.idType 	= tmpCanMsg->frame.idType;
  msg.frame.id		= tmpCanMsg->frame.id;
  msg.frame.dlc		= tmpCanMsg->frame.dataLengthCode;
  msg.frame.data0	= tmpCanMsg->frame.data[0];
  msg.frame.data1 	= tmpCanMsg->frame.data[1];
  msg.frame.data2 	= tmpCanMsg->frame.data[2];
  msg.frame.data3 	= tmpCanMsg->frame.data[3];
  msg.frame.data4 	= tmpCanMsg->frame.data[4];
  msg.frame.data5 	= tmpCanMsg->frame.data[5];
  msg.frame.data6 	= tmpCanMsg->frame.data[6];
  msg.frame.data7 	= tmpCanMsg->frame.data[7];
  
  return PDMHAL_CANC_Transmit(&msg);
}

uint8_t SVC_CAN_TransmitCanB(PDMHAL_CAN_MessageFrame *tmpCanMsg){
  if (USE_USB_OVER_CANB){
	return 1;
  }
  return PDMHAL_CANB_Transmit(tmpCanMsg);
}
