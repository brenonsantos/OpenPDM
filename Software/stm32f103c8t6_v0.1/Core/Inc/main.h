/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "opdm_hal.h"
#include "pdm_svc.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
//#define INTERNAL_LED_Pin GPIO_PIN_13
//#define INTERNAL_LED_GPIO_Port GPIOC
//#define MUX_INPUTS_A1_Pin GPIO_PIN_14
//#define MUX_INPUTS_A1_GPIO_Port GPIOC
//#define MUX_INPUTS_A2_Pin GPIO_PIN_15
//#define MUX_INPUTS_A2_GPIO_Port GPIOC
//#define CURRENT_VOLTAGE_SENSE_ADC_PIN_Pin GPIO_PIN_0
//#define CURRENT_VOLTAGE_SENSE_ADC_PIN_GPIO_Port GPIOA
//#define AD_INPUTS_ADC_PIN_Pin GPIO_PIN_1
//#define AD_INPUTS_ADC_PIN_GPIO_Port GPIOA
//#define STATUS_LED_Pin GPIO_PIN_3
//#define STATUS_LED_GPIO_Port GPIOA
//#define GATE_LC0_SIG_Pin GPIO_PIN_4
//#define GATE_LC0_SIG_GPIO_Port GPIOA
//#define GATE_LC1_SIG_Pin GPIO_PIN_5
//#define GATE_LC1_SIG_GPIO_Port GPIOA
//#define GATE_LC2_SIG_Pin GPIO_PIN_6
//#define GATE_LC2_SIG_GPIO_Port GPIOA
//#define GATE_LC3_SIG_Pin GPIO_PIN_7
//#define GATE_LC3_SIG_GPIO_Port GPIOA
//#define GATE_HC1_SIG_Pin GPIO_PIN_0
//#define GATE_HC1_SIG_GPIO_Port GPIOB
//#define GATE_HC0_SIG_Pin GPIO_PIN_1
//#define GATE_HC0_SIG_GPIO_Port GPIOB
//#define GATE_HC3_SIG_Pin GPIO_PIN_10
//#define GATE_HC3_SIG_GPIO_Port GPIOB
//#define GATE_HC2_SIG_Pin GPIO_PIN_11
//#define GATE_HC2_SIG_GPIO_Port GPIOB
//#define CANC_INTERRUPT_Pin GPIO_PIN_8
//#define CANC_INTERRUPT_GPIO_Port GPIOA
//#define CANB_ERR_Pin GPIO_PIN_9
//#define CANB_ERR_GPIO_Port GPIOA
//#define CANB_STB_Pin GPIO_PIN_10
//#define CANB_STB_GPIO_Port GPIOA
//#define MUX_CUR_SENSE_A3_Pin GPIO_PIN_15
//#define MUX_CUR_SENSE_A3_GPIO_Port GPIOA
//#define MUX_CUR_SENSE_A2_Pin GPIO_PIN_3
//#define MUX_CUR_SENSE_A2_GPIO_Port GPIOB
//#define MUX_CUR_SENSE_A1_Pin GPIO_PIN_4
//#define MUX_CUR_SENSE_A1_GPIO_Port GPIOB
//#define MUX_CUR_SENSE_A0_Pin GPIO_PIN_5
//#define MUX_CUR_SENSE_A0_GPIO_Port GPIOB
//#define CANB_EN_Pin GPIO_PIN_6
//#define CANB_EN_GPIO_Port GPIOB
//#define MUX_INPUTS_A0_Pin GPIO_PIN_7
//#define MUX_INPUTS_A0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
