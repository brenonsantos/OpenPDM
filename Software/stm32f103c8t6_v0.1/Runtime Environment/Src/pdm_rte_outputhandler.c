/*
 * pdm_rte_output.c
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */


/*
 * pdm_svc_currentoutputs.c
 *
 *  Created on: 28 de abr de 2023
 *      Author: breno
 */


#include "pdm_rte_outputhandler.h"
#include <string.h>


uint8_t RTE_isOutputEnable(CurrentOutputsTypedef output_addr){
	return CURRENT_OUTPUT_SETUP[output_addr].enable;
}











