/*
 * opdm_hal_io.c
 *
 *  Created on: Mar 28, 2023
 *      Author: breno
 */

#include "opdm_hal_io.h"
#include <string.h>
//-------------------- Defines --------------------


//-------------------- Private variables --------------------


//-------------------- Private function prototypes ----------



//-------------------- Public variables --------------------

// Public variables


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

//CURRENT_OUTPUT_SETUP[output].gpio_addr.port, CURRENT_OUTPUT_SETUP[output].gpio_addr.pin
void PDMHAL_SetCurrentOutput(CURRENT_OUTPUT_TYPE output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_SET);
}

void PDMHAL_ResetCurrentOutput(CURRENT_OUTPUT_TYPE output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_RESET);
}


