/*
 * pdm_canc_MCP2515.c
 *
 *  Created on: Jun 7, 2023
 *      Author: breno
 */

#ifndef __PDM_CANC_MCP2515_C_
#define __PDM_CANC_MCP2515_C_

#include "pdm_canc_MCP2515.h"

extern SPI_HandleTypeDef hspi2;
#define SPI_CAN &hspi2
#define SPI_TIMEOUT 10
#define MCP2515_SetCSHigh()	HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_SET)
#define MCP2515_SetCSLow()	HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_RESET)

/* Prototypes */
static void CANC_SPI_Tx (uint8_t data);
static void CANC_SPI_TxBuffer (uint8_t *buffer, uint8_t length);
static uint8_t CANC_SPI_Rx (void);
static void CANC_SPI_RxBuffer (uint8_t *buffer, uint8_t length);

/* initialize MCP2515 */
uint8_t MCP2515_Initialize (void) {
  MCP2515_SetCSHigh();

  uint8_t loop = 10;

  do {
	/* check SPI Ready */
	if (HAL_SPI_GetState (SPI_CAN) == HAL_SPI_STATE_READY)
	  return TRUE;

	loop--;
  }
  while (loop > 0);

  return FALSE;
}

/* Change mode MCP2515 mode */
uint8_t MCP2515_SetMode (uint8_t mode) {

  /* send request for mode change */
  MCP2515_WriteByte (MCP2515_CANCTRL, mode);

  uint8_t loop = 10;

  do {
	/* confirm mode configuration */
	if ((MCP2515_ReadByte (MCP2515_CANSTAT) & MCP2515_CANSTAT_OPMOD) == mode)
	  return TRUE;

	loop--;
  }
  while (loop > 0);

  return FALSE;
}

/* Change mode to config */
uint8_t MCP2515_SetConfigMode () {
  return MCP2515_SetMode (MCP2515_CANCTRL_REQOP_CONFIG);
}

/* Change mode as normal mode */
uint8_t MCP2515_SetNormalMode (void) {
  return MCP2515_SetMode (MCP2515_CANCTRL_REQOP_NORMAL);
}
/* Enter sleep mode */
uint8_t MCP2515_SetSleepMode (void) {
  return MCP2515_SetMode (MCP2515_CANCTRL_REQOP_SLEEP);
}

/* MCP2515 SPI-Reset */
void MCP2515_Reset (void) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (MCP2515_RESET);

  MCP2515_SetCSHigh();
}

/* read single byte */
uint8_t MCP2515_ReadByte (uint8_t address) {
  uint8_t retVal;

  MCP2515_SetCSLow();

  CANC_SPI_Tx (MCP2515_READ);
  CANC_SPI_Tx (address);
  retVal = CANC_SPI_Rx ();

  MCP2515_SetCSHigh();

  return retVal;
}

/* read buffer */
void MCP2515_ReadRxSequence (uint8_t instruction, uint8_t *data, uint8_t length) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (instruction);
  CANC_SPI_RxBuffer (data, length);

  MCP2515_SetCSHigh();
}

/* write single byte */
void MCP2515_WriteByte (uint8_t address, uint8_t data) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (MCP2515_WRITE);
  CANC_SPI_Tx (address);
  CANC_SPI_Tx (data);

  MCP2515_SetCSHigh();
}

/* write buffer */
void MCP2515_WriteByteSequence (uint8_t startAddress, uint8_t endAddress,
								uint8_t *data) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (MCP2515_WRITE);
  CANC_SPI_Tx (startAddress);
  CANC_SPI_TxBuffer (data, (endAddress - startAddress + 1));

  MCP2515_SetCSHigh();
}

/* write to TxBuffer */
void MCP2515_LoadTxSequence (uint8_t instruction, uint8_t *idReg, uint8_t dlc,
							 uint8_t *data) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (instruction);
  CANC_SPI_TxBuffer (idReg, 4);
  CANC_SPI_Tx (dlc);
  CANC_SPI_TxBuffer (data, dlc);

  MCP2515_SetCSHigh();
}

/* write to TxBuffer(1 byte) */
void MCP2515_LoadTxBuffer (uint8_t instruction, uint8_t data) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (instruction);
  CANC_SPI_Tx (data);

  MCP2515_SetCSHigh();
}

/* request to send */
void MCP2515_RequestToSend (uint8_t instruction) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (instruction);

  MCP2515_SetCSHigh();
}

/* read status */
uint8_t MCP2515_ReadStatus (void) {
  uint8_t retVal;

  MCP2515_SetCSLow();

  CANC_SPI_Tx (MCP2515_READ_STATUS);
  retVal = CANC_SPI_Rx ();

  MCP2515_SetCSHigh();

  return retVal;
}

/* read RX STATUS register */
uint8_t MCP2515_GetRxStatus (void) {
  uint8_t retVal;

  MCP2515_SetCSLow();

  CANC_SPI_Tx (MCP2515_RX_STATUS);
  retVal = CANC_SPI_Rx ();

  MCP2515_SetCSHigh();

  return retVal;
}

/* Use when changing register value */
void MCP2515_BitModify (uint8_t address, uint8_t mask, uint8_t data) {
  MCP2515_SetCSLow();

  CANC_SPI_Tx (MCP2515_BIT_MOD);
  CANC_SPI_Tx (address);
  CANC_SPI_Tx (mask);
  CANC_SPI_Tx (data);

  MCP2515_SetCSHigh();
}

/* SPI Tx wrapper function  */
static void CANC_SPI_Tx (uint8_t data) {
  HAL_SPI_Transmit (SPI_CAN, &data, 1, SPI_TIMEOUT);
}

/* SPI Tx wrapper function */
static void CANC_SPI_TxBuffer (uint8_t *buffer, uint8_t length) {
  HAL_SPI_Transmit (SPI_CAN, buffer, length, SPI_TIMEOUT);
}

/* SPI Rx wrapper function */
static uint8_t CANC_SPI_Rx (void) {
  uint8_t retVal;
  HAL_SPI_Receive (SPI_CAN, &retVal, 1, SPI_TIMEOUT);
  return retVal;
}

/* SPI Rx wrapper function */
static void CANC_SPI_RxBuffer (uint8_t *buffer, uint8_t length) {
  HAL_SPI_Receive (SPI_CAN, buffer, length, SPI_TIMEOUT);
}

#endif /* __PDM_CANC_MCP2515_C_ */
