/*
 * opdm_hal_io.c
 *
 *  Created on: Mar 28, 2023
 *      Author: breno
 */

#include <pdm_hal_io.h>



/* =============== Private variables =============== */
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
		{INTERNAL_LED_GPIO_Port, INTERNAL_LED_Pin},
        {STATUS_LED_GPIO_Port, STATUS_LED_Pin}
        };


/* =============== Public functions =============== */
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void PDMHAL_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(INTERNAL_LED_GPIO_Port, INTERNAL_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MUX_INPUTS_A1_Pin|MUX_INPUTS_A2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, STATUS_LED_Pin|GATE_LC3_SIG_Pin|GATE_LC2_SIG_Pin|GATE_LC1_SIG_Pin
                          |GATE_LC0_SIG_Pin|CANC_INTERRUPT_Pin|CANB_STB_Pin|MUX_CUR_SENSE_A3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GATE_HC0_SIG_Pin|GATE_HC1_SIG_Pin|GATE_HC2_SIG_Pin|GATE_HC3_SIG_Pin
                          |CAN_CS_Pin|MUX_CUR_SENSE_A2_Pin|MUX_CUR_SENSE_A1_Pin|MUX_CUR_SENSE_A0_Pin
                          |CANB_EN_Pin|MUX_INPUTS_A0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : INTERNAL_LED_Pin */
  GPIO_InitStruct.Pin = INTERNAL_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(INTERNAL_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MUX_INPUTS_A1_Pin MUX_INPUTS_A2_Pin */
  GPIO_InitStruct.Pin = MUX_INPUTS_A1_Pin|MUX_INPUTS_A2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : STATUS_LED_Pin GATE_LC3_SIG_Pin GATE_LC2_SIG_Pin GATE_LC1_SIG_Pin
                           GATE_LC0_SIG_Pin CANC_INTERRUPT_Pin MUX_CUR_SENSE_A3_Pin */
  GPIO_InitStruct.Pin = STATUS_LED_Pin|GATE_LC3_SIG_Pin|GATE_LC2_SIG_Pin|GATE_LC1_SIG_Pin
                          |GATE_LC0_SIG_Pin|CANC_INTERRUPT_Pin|MUX_CUR_SENSE_A3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GATE_HC0_SIG_Pin GATE_HC1_SIG_Pin GATE_HC2_SIG_Pin GATE_HC3_SIG_Pin
                           MUX_CUR_SENSE_A2_Pin MUX_CUR_SENSE_A1_Pin MUX_CUR_SENSE_A0_Pin CANB_EN_Pin
                           MUX_INPUTS_A0_Pin */
  GPIO_InitStruct.Pin = GATE_HC0_SIG_Pin|GATE_HC1_SIG_Pin|GATE_HC2_SIG_Pin|GATE_HC3_SIG_Pin
                          |MUX_CUR_SENSE_A2_Pin|MUX_CUR_SENSE_A1_Pin|MUX_CUR_SENSE_A0_Pin|CANB_EN_Pin
                          |MUX_INPUTS_A0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : CAN_CS_Pin */
  GPIO_InitStruct.Pin = CAN_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(CAN_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CANB_ERR_Pin */
  GPIO_InitStruct.Pin = CANB_ERR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CANB_ERR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CANB_STB_Pin */
  GPIO_InitStruct.Pin = CANB_STB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CANB_STB_GPIO_Port, &GPIO_InitStruct);

}

void PDMHAL_SetCurrentOutput(CurrentOutputsTypedef output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_SET);
}

void PDMHAL_ResetCurrentOutput(CurrentOutputsTypedef output){
	HAL_GPIO_WritePin(current_output_port_pin_array[output].port, current_output_port_pin_array[output].pin, GPIO_PIN_RESET);
}


void PDMHAL_SetStatusLed(PDMHAL_GenericLedType led){
	// INTERNAL_LED uses inverse logic
	if (led == LED_Internal){ //
		HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_RESET);
	}
        HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_SET);
}

void PDMHAL_ResetStatusLed(PDMHAL_GenericLedType led){
	if (led == LED_Internal){
		HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_SET);
	}
        HAL_GPIO_WritePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin, GPIO_PIN_RESET);
}

void PDMHAL_ToggleStatusLed(PDMHAL_GenericLedType led){
  HAL_GPIO_TogglePin(status_led_port_pin_array[led].port, status_led_port_pin_array[led].pin);
}

