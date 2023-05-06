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


ADC_HandleTypeDef adinput_adc_handler; 	// adc1
ADC_HandleTypeDef cvsense_adc_handler; 	// adc2


PDM_HAL_PortPinTypedef CV_SENSE_MUX_ADDR[NUM_OF_CURRENT_VOLTAGE_SENSE_MULTIPLEXER] = {
    {MUX_CUR_SENSE_A0_GPIO_Port, MUX_CUR_SENSE_A0_Pin},
    {MUX_CUR_SENSE_A1_GPIO_Port, MUX_CUR_SENSE_A1_Pin},
    {MUX_CUR_SENSE_A2_GPIO_Port, MUX_CUR_SENSE_A2_Pin},
    {MUX_CUR_SENSE_A3_GPIO_Port, MUX_CUR_SENSE_A3_Pin},
};

PDM_HAL_PortPinTypedef INPUT_SENSE_MUX_ADDR[NUM_OF_INPUT_MULTIPLEXER] = {
	{MUX_INPUTS_A0_GPIO_Port, MUX_INPUTS_A0_Pin},
	{MUX_INPUTS_A1_GPIO_Port, MUX_INPUTS_A1_Pin},
	{MUX_INPUTS_A2_GPIO_Port, MUX_INPUTS_A2_Pin},
};

PDMHAL_VoltageSenseType VOLTAGE_SENSE_MUX_MAP[NUM_OF_OUTPUTS] = {
		VOLTAGE_SENSE_HC0, VOLTAGE_SENSE_HC1, VOLTAGE_SENSE_HC2, VOLTAGE_SENSE_HC3,
		VOLTAGE_SENSE_LC0, VOLTAGE_SENSE_LC1, VOLTAGE_SENSE_LC2, VOLTAGE_SENSE_LC3
};

PDMHAL_CurrentSenseType CURRENT_SENSE_MUX_MAP[NUM_OF_OUTPUTS] = {
		CURRENT_SENSE_HC0, CURRENT_SENSE_HC1, CURRENT_SENSE_HC2, CURRENT_SENSE_HC3,
		CURRENT_SENSE_LC0, CURRENT_SENSE_LC1, CURRENT_SENSE_LC2, CURRENT_SENSE_LC3
};




void PDMHAL_ADC_Init(void){
	adc1_init();
	adc2_init();
	HAL_ADCEx_Calibration_Start(&adinput_adc_handler);
	HAL_ADCEx_Calibration_Start(&cvsense_adc_handler);
}

void set_ad_input_multiplexer(PDMHAL_AnalogInputType input){
	GPIO_PinState pinState[2] = {GPIO_PIN_RESET, GPIO_PIN_SET};

	HAL_GPIO_WritePin(INPUT_SENSE_MUX_ADDR[INPUT_MUX_A2].port, INPUT_SENSE_MUX_ADDR[INPUT_MUX_A2].pin, pinState[(input & 0x04) >> 2]);
	HAL_GPIO_WritePin(INPUT_SENSE_MUX_ADDR[INPUT_MUX_A1].port, INPUT_SENSE_MUX_ADDR[INPUT_MUX_A1].pin, pinState[(input & 0x02) >> 1]);
	HAL_GPIO_WritePin(INPUT_SENSE_MUX_ADDR[INPUT_MUX_A0].port, INPUT_SENSE_MUX_ADDR[INPUT_MUX_A0].pin, pinState[(input & 0x01)]);
}

void set_current_sense_multiplexer(PDMHAL_OutputType output){
	const GPIO_PinState pinState[2] = {GPIO_PIN_RESET, GPIO_PIN_SET};

	HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A3].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A3].pin, GPIO_PIN_RESET);

	output = CURRENT_SENSE_MUX_MAP[output];

	HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A2].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A2].pin, pinState[(output & 0x04) >> 2]);
	HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A1].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A1].pin, pinState[(output & 0x02) >> 1]);
	HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A0].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A0].pin, pinState[(output & 0x01)]);
}

void set_voltage_sense_multiplexer(PDMHAL_OutputType output){
	GPIO_PinState pinState[2] = {GPIO_PIN_RESET, GPIO_PIN_SET};

  HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A3].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A3].pin, GPIO_PIN_SET);

  output = VOLTAGE_SENSE_MUX_MAP[output];

  HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A2].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A2].pin, pinState[(output & 0x04) >> 2]);
  HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A1].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A1].pin, pinState[(output & 0x02) >> 1]);
  HAL_GPIO_WritePin(CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A0].port, CV_SENSE_MUX_ADDR[CV_SENSE_MUX_A0].pin, pinState[(output & 0x01)]);
}

static void adc1_init(void){
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common config
  */
  adinput_adc_handler.Instance = ADC2;
  adinput_adc_handler.Init.ScanConvMode = ADC_SCAN_DISABLE;
  adinput_adc_handler.Init.ContinuousConvMode = DISABLE;
  adinput_adc_handler.Init.DiscontinuousConvMode = DISABLE;
  adinput_adc_handler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  adinput_adc_handler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  adinput_adc_handler.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&adinput_adc_handler) != HAL_OK){
    adc_error_handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&adinput_adc_handler, &sConfig) != HAL_OK){
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
  cvsense_adc_handler.Instance = ADC1;
  cvsense_adc_handler.Init.ScanConvMode = ADC_SCAN_DISABLE;
  cvsense_adc_handler.Init.ContinuousConvMode = DISABLE;
  cvsense_adc_handler.Init.DiscontinuousConvMode = DISABLE;
  cvsense_adc_handler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  cvsense_adc_handler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  cvsense_adc_handler.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&cvsense_adc_handler) != HAL_OK)
  {
    adc_error_handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&cvsense_adc_handler, &sConfig) != HAL_OK)
  {
    adc_error_handler();
  }
}


PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatus(ADC_HandleTypeDef* hadc){
	/* Checks if ADC is it's ready state, meaning it hasn't started */
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
	return HAL_ADC_GetValue(&adinput_adc_handler);
}

uint32_t PDMHAL_ADC_ReadOutputVoltage(void){
  return HAL_ADC_GetValue(&cvsense_adc_handler);
}

uint32_t PDMHAL_ADC_ReadOutputCurrent(void){
  return HAL_ADC_GetValue(&cvsense_adc_handler);
}

void PDMHAL_ADC_StartNewVoltageReading(PDMHAL_VoltageSenseType new_sense){
  HAL_ADC_Stop(&cvsense_adc_handler);
  set_voltage_sense_multiplexer(new_sense);
  HAL_ADC_Start(&cvsense_adc_handler);
}

void PDMHAL_ADC_StartNewCurrentReading(PDMHAL_CurrentSenseType new_sense){
  HAL_ADC_Stop(&cvsense_adc_handler);
  set_current_sense_multiplexer(new_sense);
  HAL_ADC_Start(&cvsense_adc_handler);
}

void PDMHAL_ADC_StartNewInputReading(PDMHAL_AnalogInputType new_input){
	HAL_ADC_Stop(&adinput_adc_handler);
	set_ad_input_multiplexer(new_input);
	HAL_ADC_Start(&adinput_adc_handler);
}

void PDMHAL_ADC_ContinueCurrentReading(void){
	HAL_ADC_Start(&cvsense_adc_handler);
}

void PDMHAL_ADC_ContinueReadingVoltage(void){
	HAL_ADC_Start(&cvsense_adc_handler);
}

void PDMHAL_ADC_ContinueADInputReading(void){
	HAL_ADC_Start(&adinput_adc_handler);
}

PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatusInput(void){
	return PDMHAL_ADC_CheckConversionStatus(&adinput_adc_handler);
}

PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatusVoltage(void){
	return PDMHAL_ADC_CheckConversionStatus(&cvsense_adc_handler);
}

PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatusCurrent(void){
	return PDMHAL_ADC_CheckConversionStatus(&cvsense_adc_handler);
}

void adc_error_handler(){
	// TODO
}

void hal_adc_teste(void){
//	HAL_ADC_Start(&hadc_ad_inputs);
	HAL_ADC_GetState(&adinput_adc_handler);
}
