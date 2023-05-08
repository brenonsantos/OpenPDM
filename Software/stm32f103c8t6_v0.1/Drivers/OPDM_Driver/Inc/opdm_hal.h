/*
 * opdm_hal.h
 *
 *  Created on: 27 de abr de 2023
 *      Author: breno
 */

#ifndef __OPDM_HAL_H_
#define __OPDM_HAL_H_


//#include "opdm_hal_io_cfg.h"

#include "opdm_hal_adc.h"
#include "opdm_hal_io.h"

void PDMHAL_Init(void);

uint32_t moving_average(uint32_t *data, uint32_t new_sample, MOVING_AVERAGE_WINDOW_SIZE window_size);

#endif /* OPDM_DRIVER_INC_OPDM_HAL_H_ */
