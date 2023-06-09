/*
 * pdm_hal_can.h
 *
 *  Created on: Jun 7, 2023
 *      Author: breno
 */

#ifndef __PDM_HAL_CAN_H_
#define __PDM_HAL_CAN_H_

#include "pdm_canc_MCP2515.h"
#include "pdm_hal_def.h"

typedef enum{
	CANB_EN = 0,
	CANB_ERR,
	CANB_STB,
	NUM_OF_CANB_PINS
}CANB_PINS_TYPE;

typedef enum{
	CANC_INTERRUPT = 0,
	CANC_SPI_SS,
	NUM_OF_CANC_PINS
}CANC_PINS_TYPE;

typedef union {
  struct {
    uint8_t idType;
    uint32_t id;
    uint8_t dlc;
//    uint8_t data[8];
    uint8_t data0;
    uint8_t data1;
    uint8_t data2;
    uint8_t data3;
    uint8_t data4;
    uint8_t data5;
    uint8_t data6;
    uint8_t data7;
  } frame;
  uint8_t array[14];
} CANC_MSG;

#define dSTANDARD_CAN_MSG_ID_2_0B 1
#define dEXTENDED_CAN_MSG_ID_2_0B 2

uint8_t PDMHAL_CANC_Init(CANC_BaudRate baudRate);
void PDMHAL_CANC_Sleep(void);
uint8_t PDMHAL_CANC_Transmit(CANC_MSG *tempCanMsg);
uint8_t PDMHAL_CANC_Receive(CANC_MSG *tempCanMsg);
uint8_t PDMHAL_CANC_messagesInBuffer(void);
uint8_t PDMHAL_CANC_isBussOff(void);
uint8_t PDMHAL_CANC_isRxErrorPassive(void);
uint8_t PDMHAL_CANC_isTxErrorPassive(void);


#endif /* __PDM_HAL_CAN_H_ */
