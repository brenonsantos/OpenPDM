/*
 * pdm_hal_spi.h
 *
 *  Created on: Jun 7, 2023
 *      Author: breno
 */

#ifndef __PDM_HAL_SPI_H_
#define __PDM_HAL_SPI_H_

#include "pdm_hal_def.h"

extern SPI_HandleTypeDef hspi2;
HAL_StatusTypeDef PDMHAL_SPI_Init(void);


#endif /* __PDM_HAL_SPI_H_ */
