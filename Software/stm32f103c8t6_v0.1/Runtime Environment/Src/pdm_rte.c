/*
 * pdm_rte.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */

#include "pdm_rte.h"

void RTE_Init(void){
    OUTPUT_initOutputs();
    RTE_OUTPUT_init();
}
