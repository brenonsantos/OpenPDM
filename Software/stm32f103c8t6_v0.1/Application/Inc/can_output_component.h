/*
 * can_output_component.h
 *
 *  Created on: 9 de jun de 2023
 *      Author: breno
 */

#ifndef __CAN_OUTPUT_COMPONENT_H_
#define __CAN_OUTPUT_COMPONENT_H_

#include "opdm_cfg.h"
#include "pdm_rte.h"

#define MAX_CAN_LABEL_SIZE 8

#define MAX_16Bits

typedef uint8_t (*CanTransmitCallback)(PDMHAL_CAN_MessageFrame *frame);

typedef struct{
  char label[MAX_CAN_LABEL_SIZE];
  PDMHAL_CAN_MessageFrame frame;
  uint32_t timeout_ms;
  float frequency_hz;
  CanTransmitCallback callback;
}CANBusTransmiterTypedef;

extern CANBusTransmiterTypedef CANBUS_TRANSMITER_FRAMES[NUM_OF_CAN_TRANSMITERS];

void split16Bits(uint16_t value, uint8_t* result);

//void CAN_OUTPUT_Transmit_CurrentSense(PDMHAL_CAN_MessageFrame* frame, CurrentOutputsTypedef output);
//void CAN_OUTPUT_Transmit_VoltageSense(PDMHAL_CAN_MessageFrame* frame, CurrentOutputsTypedef output);
//void CAN_OUTPUT_Transmit_InputReading(PDMHAL_CAN_MessageFrame* frame, AnalogDigitalInputType input);

void CAN_OUTPUT_Transmit_16bits(PDMHAL_CAN_MessageFrame* frame, uint16_t* data, uint8_t dataLength);
void CAN_OUTPUT_Transmit(PDMHAL_CAN_MessageFrame* frame, uint8_t* data, uint8_t dataLengthBytes);



#endif /* __CAN_OUTPUT_COMPONENT_H_ */
