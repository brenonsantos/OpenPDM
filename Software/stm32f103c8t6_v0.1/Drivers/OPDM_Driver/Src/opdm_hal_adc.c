/*
 * opdm_hal_adc.c
 *
 *  Created on: 26 de abr de 2023
 *      Author: breno
 */

#include "opdm_hal_adc.h"

static void adc1_init(void);
static void adc2_init(void);
void adc_error_handler();


ADC_HandleTypeDef hadc_ad_inputs; 	// adc1
ADC_HandleTypeDef hadc_cv_sense; 	// adc2


PDM_HAL_PortPinTypedef CURRENT_VOLTAGE_SENSE_MUTIPLEXER[NUM_OF_CURRENT_VOLTAGE_SENSE_MULTIPLEXER] = {
    {MUX_CUR_SENSE_A0_GPIO_Port, MUX_CUR_SENSE_A0_Pin},
    {MUX_CUR_SENSE_A1_GPIO_Port, MUX_CUR_SENSE_A1_Pin},
    {MUX_CUR_SENSE_A2_GPIO_Port, MUX_CUR_SENSE_A2_Pin},
    {MUX_CUR_SENSE_A3_GPIO_Port, MUX_CUR_SENSE_A3_Pin},
};

PDM_HAL_PortPinTypedef INPUTS_MUTIPLEXER[NUM_OF_INPUT_MULTIPLEXER] = {
	{MUX_INPUTS_A0_GPIO_Port, MUX_INPUTS_A0_Pin},
	{MUX_INPUTS_A1_GPIO_Port, MUX_INPUTS_A1_Pin},
	{MUX_INPUTS_A2_GPIO_Port, MUX_INPUTS_A2_Pin},
};


void PDMHAL_ADC_Init(void){
	adc1_init();
	adc2_init();
	HAL_ADCEx_Calibration_Start(&hadc_ad_inputs);
	HAL_ADCEx_Calibration_Start(&hadc_cv_sense);
}

void set_ad_input_multiplexer(ANALOG_DIGITAL_INPUT_TYPE input){
	GPIO_PinState pinState[2] = {GPIO_PIN_RESET, GPIO_PIN_SET};

	HAL_GPIO_WritePin(INPUTS_MUTIPLEXER[INPUT_MUX_A2].port, INPUTS_MUTIPLEXER[INPUT_MUX_A2].pin, pinState[(input & 0x04) >> 2]);
	HAL_GPIO_WritePin(INPUTS_MUTIPLEXER[INPUT_MUX_A1].port, INPUTS_MUTIPLEXER[INPUT_MUX_A1].pin, pinState[(input & 0x02) >> 1]);
	HAL_GPIO_WritePin(INPUTS_MUTIPLEXER[INPUT_MUX_A0].port, INPUTS_MUTIPLEXER[INPUT_MUX_A0].pin, pinState[(input & 0x01)]);
}

static void adc1_init(void){
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common config
  */
  hadc_ad_inputs.Instance = ADC1;
  hadc_ad_inputs.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc_ad_inputs.Init.ContinuousConvMode = DISABLE;
  hadc_ad_inputs.Init.DiscontinuousConvMode = DISABLE;
  hadc_ad_inputs.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc_ad_inputs.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc_ad_inputs.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc_ad_inputs) != HAL_OK){
    adc_error_handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc_ad_inputs, &sConfig) != HAL_OK){
    adc_error_handler();
  }
}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void adc2_init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  /** Common config
  */
  hadc_cv_sense.Instance = ADC2;
  hadc_cv_sense.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc_cv_sense.Init.ContinuousConvMode = DISABLE;
  hadc_cv_sense.Init.DiscontinuousConvMode = DISABLE;
  hadc_cv_sense.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc_cv_sense.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc_cv_sense.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc_cv_sense) != HAL_OK)
  {
    adc_error_handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc_cv_sense, &sConfig) != HAL_OK)
  {
    adc_error_handler();
  }
}


PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatus(ADC_HandleTypeDef* hadc){
	if(HAL_IS_BIT_SET(hadc->State, HAL_ADC_STATE_READY)){
		return READY;
	}

  if(HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_SCAN) &&
	 HAL_IS_BIT_CLR(hadc->Instance->SQR1, ADC_SQR1_L)		){
	  if(HAL_IS_BIT_CLR(hadc->Instance->SR, ADC_FLAG_EOC)){ //wrong
		  return BUSY;
	  }
  }
  /* Clear regular group conversion flag */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_STRT | ADC_FLAG_EOC);

  /* Update ADC state machine */
  SET_BIT(hadc->State, HAL_ADC_STATE_REG_EOC);

  if(ADC_IS_SOFTWARE_START_REGULAR(hadc)        &&
    (hadc->Init.ContinuousConvMode == DISABLE)   ){
    /* Set ADC state */
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_REG_BUSY);

    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_INJ_BUSY)){
      SET_BIT(hadc->State, HAL_ADC_STATE_READY);
    }
  }

  /* Return ADC state */
  return CONVERSION_COMPLETE;
}


uint32_t PDMHAL_ADC_ReadInput(void){
	return HAL_ADC_GetValue(&hadc_ad_inputs);
}

void PDMHAL_ADC_StartNewInputADC(ANALOG_DIGITAL_INPUT_TYPE new_input){
	set_ad_input_multiplexer(new_input);
	HAL_Delay(1);
	HAL_ADC_Start(&hadc_ad_inputs);
}

void PDMHAL_ADC_StartInputADC(void){
	HAL_ADC_Start(&hadc_ad_inputs);

}



PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatusInput(void){
	return PDMHAL_ADC_CheckConversionStatus(&hadc_ad_inputs);
}


void adc_error_handler(){
	// TODO
}

void hal_adc_teste(void){
//	HAL_ADC_Start(&hadc_ad_inputs);
	HAL_ADC_GetState(&hadc_ad_inputs);
}
