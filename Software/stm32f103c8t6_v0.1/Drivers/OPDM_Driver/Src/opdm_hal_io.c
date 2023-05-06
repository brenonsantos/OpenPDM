/*
 * opdm_hal_io.c
 *
 *  Created on: Mar 28, 2023
 *      Author: breno
 */

#include "opdm_hal_io.h"
//-------------------- Defines --------------------


//-------------------- Private variables --------------------
PDM_HAL_PortPinTypedef current_output_port_pin_array[NUM_OF_CURRENT_OUTPUTS] = {
        {GATE_HC0_SIG_GPIO_Port, GATE_HC0_SIG_Pin},
        {GATE_HC1_SIG_GPIO_Port, GATE_HC1_SIG_Pin},
        {GATE_HC2_SIG_GPIO_Port, GATE_HC2_SIG_Pin},
        {GATE_HC3_SIG_GPIO_Port, GATE_HC3_SIG_Pin},
        {GATE_LC0_SIG_GPIO_Port, GATE_LC0_SIG_Pin},
        {GATE_LC1_SIG_GPIO_Port, GATE_LC1_SIG_Pin},
        {GATE_LC2_SIG_GPIO_Port, GATE_LC2_SIG_Pin},
        {GATE_LC3_SIG_GPIO_Port, GATE_LC3_SIG_Pin},
        };

//-------------------- Private function prototypes ----------


//-------------------- Public variables --------------------



void PDMHAL_SetCurrentOutput(PDMHAL_CurrentOutputType output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_SET);
}

void PDMHAL_ResetCurrentOutput(PDMHAL_CurrentOutputType output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_RESET);
}

