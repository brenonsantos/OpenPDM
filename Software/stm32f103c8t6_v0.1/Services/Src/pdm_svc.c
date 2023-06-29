/*
 * pdm_svc_init.c
 *
 *  Created on: 27 de abr de 2023
 *      Author: breno
 */

#include <pdm_svc.h>

PDMHAL_CAN_MessageFrame systemIntegrityFaultCANMsg = {
	.frame = {
		.CANBus = CAN_C,
		.idType = CAN_Standard,
		.id = 0xFFFA,
		.dataLengthCode = 8,
		.data = {'F', 'A', 'U', 'L', 'T', ' ', '=', '('}
	}
};

void SVC_Init(void){

}

PDM_Status SVC_PDM_UpdateSystemIntegrity(void){
static uint32_t currentGlobalLimit = LC_CURRENT_CONVERSION_TO_12BITS(GLOBAL_TOTAL_CURRENT_LIMIT);
  // Checks if the total current is above the limit
  if (RTE_OUTPUT_GetTotalCurrentDraw() >= currentGlobalLimit) {
	return PDM_FAULT;
  }
  return PDM_OK;
}

void SVC_PDM_SendSystemIntegrityFault(void){
  SVC_CAN_Transmit(&systemIntegrityFaultCANMsg);
}

