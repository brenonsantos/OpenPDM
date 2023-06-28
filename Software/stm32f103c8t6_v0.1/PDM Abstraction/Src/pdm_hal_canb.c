/*
 * pdm_hal_canb.c
 *
 *  Created on: Jun 8, 2023
 *      Author: breno
 */

#include "pdm_hal_canb.h"

/** Private Variables */
/* Internal CAN variables */
CAN_HandleTypeDef hcan;
CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
uint8_t	newMsgFlag = FALSE;

CAN_FilterTypeDef sFilterConfig = {
	.FilterActivation 		= CAN_FILTER_ENABLE,
	.FilterBank 			= 0,
	.FilterMode 			= CAN_FILTERMODE_IDMASK,
	.FilterIdHigh 			= 0x0000,
	.FilterIdLow 			= 0x0000,
	.FilterMaskIdHigh 		= 0x0000,
	.FilterMaskIdLow 		= 0x0000,
	.FilterFIFOAssignment 	= CAN_RX_FIFO0,
	.SlaveStartFilterBank 	= 14,
};

/** Public Variables */
PDMHAL_CAN_MessageFrame newMsg;

/** Private Function Prototypes */
HAL_StatusTypeDef CANB_ActivateNotification (void);
HAL_StatusTypeDef CANB_Init (void);
HAL_StatusTypeDef CANB_ConfigFilter (void);
void CANB_Error_Handler (void);

/** CANB API Calls */
/**
 * @brief CAN Initialization Function
 * @param None
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef PDMHAL_CANB_Init (void) {
  HAL_StatusTypeDef error_code = CANB_Init ();
  if (error_code != HAL_OK)
	return error_code;

  error_code = CANB_ConfigFilter ();
  if (error_code != HAL_OK)
	return error_code;

  error_code = CANB_ActivateNotification ();
  if (error_code != HAL_OK)
	return error_code;

  void PDMHAL_CANB_SetModeNormal(void);

  return HAL_OK;
}

HAL_StatusTypeDef PDMHAL_CANB_Transmit (PDMHAL_CAN_MessageFrame *tmpCanMsg) {
  CAN_TxHeaderTypeDef pHeader;
  uint8_t aData[8];
  uint32_t pTxMailbox;

  if (tmpCanMsg->frame.idType == CAN_Standard) {
	pHeader.IDE = CAN_ID_STD;
	pHeader.StdId = tmpCanMsg->frame.id;
  }
  else {
	pHeader.IDE = CAN_ID_EXT;
	pHeader.ExtId = tmpCanMsg->frame.id;
  }

  pHeader.RTR = CAN_RTR_DATA;
  pHeader.DLC = tmpCanMsg->frame.dataLengthCode;

  for (uint8_t i = 0; i < tmpCanMsg->frame.dataLengthCode; i++) {
	aData[i] = tmpCanMsg->frame.data[i];
  }

  return HAL_CAN_AddTxMessage (&hcan, &pHeader, aData, &pTxMailbox);
}

PDMHAL_CAN_MessageFrame* PDMHAL_CANB_Receive (void) {
  if (newMsgFlag) {
	newMsgFlag = FALSE;
	// Convert received message to PDM style message
	newMsg.frame.CANBus = CAN_B;
	newMsg.frame.dataLengthCode = RxHeader.DLC;

	if (RxHeader.IDE == CAN_ID_STD) {
	  newMsg.frame.idType = CAN_Standard;
	  newMsg.frame.id = RxHeader.StdId;
	}
	else {
	  newMsg.frame.idType = CAN_Extended;
	  newMsg.frame.id = RxHeader.ExtId;
	}

	for (uint8_t i = 0; i < RxHeader.DLC; i++) {
	  newMsg.frame.data[i] = RxData[i];
	}
	return &newMsg;
  }
  newMsgFlag = FALSE;
  return NULL;
}


HAL_StatusTypeDef PDMHAL_CANB_NewConfigFilter (CAN_FilterTypeDef *newFilter) {
  sFilterConfig.FilterActivation = newFilter->FilterActivation;
  sFilterConfig.FilterBank = newFilter->FilterBank;
  sFilterConfig.FilterMode = newFilter->FilterMode;
  sFilterConfig.FilterIdHigh = newFilter->FilterIdHigh;
  sFilterConfig.FilterIdLow = newFilter->FilterIdLow;
  sFilterConfig.FilterMaskIdHigh = newFilter->FilterMaskIdHigh;
  sFilterConfig.FilterMaskIdLow = newFilter->FilterMaskIdLow;
  sFilterConfig.FilterFIFOAssignment = newFilter->FilterFIFOAssignment;
  sFilterConfig.SlaveStartFilterBank = newFilter->SlaveStartFilterBank;
  return CANB_ConfigFilter ();

}

void PDMHAL_CANB_SetModeNormal(void){
  HAL_GPIO_WritePin(CANB_EN_GPIO_Port, CANB_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CANB_STB_GPIO_Port, CANB_STB_Pin, GPIO_PIN_SET);
}

void PDMHAL_CANB_SetModeSleep(void){
  HAL_GPIO_WritePin(CANB_EN_GPIO_Port, CANB_EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CANB_STB_GPIO_Port, CANB_STB_Pin, GPIO_PIN_RESET);
}

/** CANB Private Variables */

void HAL_CAN_RxFifo0MsgPendingCallback (CAN_HandleTypeDef *hcan) {
  if (HAL_CAN_GetRxMessage (hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
	CANB_Error_Handler ();
	return;
  }
//  if (!newMsgFlag) #TODO: add a buffer to cache messages
  newMsgFlag = TRUE;
}

HAL_StatusTypeDef CANB_ConfigFilter (void) {
  return HAL_CAN_ConfigFilter (&hcan, &sFilterConfig);
}

HAL_StatusTypeDef CANB_Init (void) {
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;

  return HAL_CAN_Init (&hcan);
}

HAL_StatusTypeDef CANB_ActivateNotification (void) {
  return HAL_CAN_ActivateNotification (&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void CANB_Error_Handler (void) {
  //#TODO:CANB Error handler
}


