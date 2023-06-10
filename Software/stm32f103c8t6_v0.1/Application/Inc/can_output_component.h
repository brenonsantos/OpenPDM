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

typedef struct{
  char label[MAX_CAN_LABEL_SIZE];
  PDMHAL_CAN_MessageFrame frame;
  uint32_t timeout_ms;
  uint8_t frequency_hz;
}CANBusTransmiterTypedef;

extern CANBusTransmiterTypedef CANBUS_TRANSMITER_FRAMES[NUM_OF_CAN_TRANSMITERS];

void CAN_OUTPUT_Transmit_CurrentSense(CurrentOutputsTypedef output);
void CAN_OUTPUT_Transmit_VoltageSense(CurrentOutputsTypedef output);
void CAN_OUTPUT_Transmit_InputReading(AnalogDigitalInputType input);

void CAN_OUTPUT_Transmit_8bits(uint8_t data);
void CAN_OUTPUT_Transmit_16bits(uint8_t data);


#endif /* __CAN_OUTPUT_COMPONENT_H_ */
