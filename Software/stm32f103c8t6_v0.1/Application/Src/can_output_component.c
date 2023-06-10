/*
 * can_output_component.c
 *
 *  Created on: 9 de jun de 2023
 *      Author: breno
 */

#include "can_output_component.h"

CANBusTransmiterTypedef CANBUS_TRANSMITER_FRAMES[NUM_OF_CAN_TRANSMITERS];

void CAN_OUTPUT_Transmit_8bits(const uint8_t* data, const uint8_t dataLength){


}

void CAN_OUTPUT_Transmit_16bits(uint16_t data){

}

//void CAN_OUTPUT_Transmit_CurrentSense(CurrentOutputsTypedef output);
//void CAN_OUTPUT_Transmit_VoltageSense(CurrentOutputsTypedef output);
//void CAN_OUTPUT_Transmit_InputReading(AnalogDigitalInputType input);
//
//void CAN_OUTPUT_Transmit_8bits(uint8_t data);
//void CAN_OUTPUT_Transmit_16bits(uint8_t data);
