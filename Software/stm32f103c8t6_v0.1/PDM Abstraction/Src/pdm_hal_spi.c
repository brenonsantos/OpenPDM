/*
 * pdm_hal_spi.c
 *
 *  Created on: Jun 7, 2023
 *      Author: breno
 */

#include "pdm_hal_spi.h"
SPI_HandleTypeDef hspi2;

/**
  * This SPI is used by the MCP2515 CAN controller.
  * which supports up to 10 MHz
  * The BaudRatePrescaler is accordingly
  */

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
HAL_StatusTypeDef PDMHAL_SPI_Init(void){
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;

	return HAL_SPI_Init(&hspi2);
}
