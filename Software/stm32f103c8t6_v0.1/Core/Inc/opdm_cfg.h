/*
 * opdm_output_cfg.h
 *
 *  Created on: Mar 30, 2023
 *      Author: breno
 */

#ifndef __OPDM_CFG_H_
#define __OPDM_CFG_H_

#include "pdm_hal_def.h"
#include "pdm_svc.h"
#include "pdm_def.h"
#include "sw_components.h"



//----------------- OUTPUT CONFIGURATION -----------------



// Global limits apply to all outputs. If a specific output has a greater limit than the global one, the global one will be used.
#define HC_GLOBAL_MAX_CURRENT 20.0f
#define LC_GLOBAL_MAX_CURRENT 10.0f
#define GLOBAL_MAX_VOLTAGE 15.5f
#define GLOBAL_MIN_VOLTAGE 9.0f
#define GLOBAL_INRUSH_TIME_LIMIT 2000
#define GLOBAL_TOTAL_CURRENT_LIMIT 50.0f

#define MAX_LABEL_SIZE 4


void PDM_APPLY_CONFIG(void);


//----------------- INPUT CONFIGURATION -----------------




#endif /* __OPDM_OUTPUT_CFG_H_ */
