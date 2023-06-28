/*
 * pdm_rte_can.h
 *
 *  Created on: Jun 9, 2023
 *      Author: breno
 */


#include "pdm_rte_def.h"

void RTE_COMM_ReceiveCommunicationData(void);
void RTE_COMM_SendCommunicationData(void);
void RTE_CAN_OUTPUT_Transmit(PDMHAL_CAN_MessageFrame* frame);
void RTE_COMM_SendSystemIntegrityFault(void);
