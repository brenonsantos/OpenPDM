/*
 * can_output_component.c
 *
 *  Created on: 9 de jun de 2023
 *      Author: breno
 */

#include "can_output_component.h"

CANBusTransmiterTypedef CANBUS_TRANSMITER_FRAMES[NUM_OF_CAN_TRANSMITERS];


void CAN_OUTPUT_Transmit_16bits(PDMHAL_CAN_MessageFrame* frame, uint16_t* data16, uint8_t dataLengthBytes){
  uint8_t data[dataLengthBytes];
  for (uint8_t i = 0; i < dataLengthBytes/2; i++){
	split16Bits(data16[i], &data[i*2]);
  }
  for (uint8_t i = 0; i < dataLengthBytes; i++){
	frame->frame.data[i] = data[i];
  }
  frame->frame.dataLengthCode = dataLengthBytes;
  RTE_CAN_OUTPUT_Transmit(frame);
}

void CAN_OUTPUT_Transmit(PDMHAL_CAN_MessageFrame* frame, uint8_t* data, uint8_t dataLengthBytes){
  frame->frame.dataLengthCode = dataLengthBytes;
  for (uint8_t i = 0; i < dataLengthBytes; i++){
	frame->frame.data[i] = data[i];
  }
  RTE_CAN_OUTPUT_Transmit(frame);
}


void split16Bits(uint16_t value, uint8_t* result){
  result[1] = value & 0xFF;           // LSB
  result[0] = (value >> 8) & 0xFF;    // MSB
}

