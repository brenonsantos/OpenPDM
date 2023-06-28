/*
 * opdm_hal.c
 *
 *  Created on: 27 de abr de 2023
 *      Author: breno
 */


#include "pdm_hal.h"

HAL_StatusTypeDef HAL_InitError, CANC_InitError, CANB_InitError, SPI_InitError,
	ADC_InitError;

void PDMHAL_Init (void) {
  HAL_InitError = HAL_Init ();
  PDMHAL_GPIO_Init();
  SPI_InitError = PDMHAL_SPI_Init ();
  ADC_InitError = PDMHAL_ADC_Init ();
  CANC_InitError = PDMHAL_CANC_Init (CANC_500KBPS);

#if USE_USB_OVER_CANB
  MX_USB_DEVICE_Init();
#else
  CANB_InitError = PDMHAL_CANB_Init ();
#endif

}
