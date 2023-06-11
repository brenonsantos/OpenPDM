/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
void PollReadings(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  PDMHAL_Init();
  RTE_Init();
  PDM_APPLY_CONFIG();
  uint8_t hasOutputBeenUpdated = FALSE;
  /* USER CODE END 2 */
//  CANC_MSG txMessage;
//  CANC_MSG rxMessage;
//  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  /* Update all measurements */
	  hasOutputBeenUpdated = RTE_OUTPUT_UpdateSense();

//	  if (RTE_PDM_UpdateSystemIntegrity() == FAULT){
//		  RTE_PDM_HandleSystemFault();
////		  RTE_OUTPUT_PowerOffAllOutputs();
////		  RTE_COMM_SendSystemIntegrityFault();
//		  HAL_Delay(100);
//		  continue;
//	  }
//	  RTE_INPUT_PollInputs();
	  RTE_COMM_ReceiveCommunicationData();

	  /* Update all status */
	  if (hasOutputBeenUpdated){
		  RTE_OUTPUT_UpdateFault();
	  }

	  /* Write all outputs */
	  RTE_OUTPUT_WriteOutputs();
	  RTE_COMM_SendCommunicationData();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

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

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void PollReadings(void){
	RTE_PollInputs();
	RTE_PollOuputCurrentReading();
	//RTE_ReadCAN();
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

//	if(CANC_Receive(&rxMessage)){
//	  txMessage.frame.idType = rxMessage.frame.idType;
//	  txMessage.frame.id = rxMessage.frame.id;
//	  txMessage.frame.dlc = rxMessage.frame.dlc;
//	  txMessage.frame.data0++;
//	  txMessage.frame.data1 = rxMessage.frame.data1;
//	  txMessage.frame.data2 = rxMessage.frame.data2;
//	  txMessage.frame.data3 = rxMessage.frame.data3;
//	  txMessage.frame.data4 = rxMessage.frame.data4;
//	  txMessage.frame.data5 = rxMessage.frame.data5;
//	  txMessage.frame.data6 = rxMessage.frame.data6;
//	  txMessage.frame.data7 = rxMessage.frame.data7;
//	  CANC_Transmit(&txMessage);
//	}

//	txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
//	txMessage.frame.id = 0x0A;
//	txMessage.frame.dlc = 8;
//	txMessage.frame.data0 = 0;
//	txMessage.frame.data1 = 1;
//	txMessage.frame.data2 = 2;
//	txMessage.frame.data3 = 3;
//	txMessage.frame.data4 = 4;
//	txMessage.frame.data5 = 5;
//	txMessage.frame.data6 = 6;
//	txMessage.frame.data7 = 7;
//	CANC_Transmit(&txMessage);
//
//	HAL_Delay(100);

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
