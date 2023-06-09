/*
 * opdm_hal_io.c
 *
 *  Created on: Mar 28, 2023
 *      Author: breno
 */

#include <pdm_hal_io.h>
//-------------------- Defines --------------------


//-------------------- Private variables --------------------
static PDMHAL_PortPinTypedef current_output_port_pin_array[NUM_OF_OUTPUTS] = {
        {GATE_HC0_SIG_GPIO_Port, GATE_HC0_SIG_Pin},
        {GATE_HC1_SIG_GPIO_Port, GATE_HC1_SIG_Pin},
        {GATE_HC2_SIG_GPIO_Port, GATE_HC2_SIG_Pin},
        {GATE_HC3_SIG_GPIO_Port, GATE_HC3_SIG_Pin},
        {GATE_LC0_SIG_GPIO_Port, GATE_LC0_SIG_Pin},
        {GATE_LC1_SIG_GPIO_Port, GATE_LC1_SIG_Pin},
        {GATE_LC2_SIG_GPIO_Port, GATE_LC2_SIG_Pin},
        {GATE_LC3_SIG_GPIO_Port, GATE_LC3_SIG_Pin},
        };

static PDMHAL_PortPinTypedef status_led_port_pin_array[NUM_OF_GENERIC_LEDS] = {
        {STATUS_LED_GPIO_Port, STATUS_LED_Pin},
        {INTERNAL_LED_GPIO_Port, INTERNAL_LED_Pin}
        };

//-------------------- Public variables --------------------

//-------------------- Private function prototypes ----------

void PDMHAL_SetCurrentOutput(CurrentOutputsTypedef output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_SET);
}

void PDMHAL_ResetCurrentOutput(CurrentOutputsTypedef output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_RESET);
}


void PDMHAL_SetStatusLed(PDMHAL_GenericLedType led){
	// INTERNAL_LED uses inverse logic
	if (led == INTERNAL_LED){ //
		HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_RESET);
	}
        HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_SET);
}

void PDMHAL_ResetStatusLed(PDMHAL_GenericLedType led){
	if (led == INTERNAL_LED){
		HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_SET);
	}
        HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_RESET);
}




