/*
 * opdm_output_cfg.h
 *
 *  Created on: Mar 30, 2023
 *      Author: breno
 */

#ifndef __OPDM_CFG_H_
#define __OPDM_CFG_H_

#include "opdm_hal_def.h"
#include "pdm_def.h"

//----------------- OUTPUT CONFIGURATION -----------------
#define ADCBYTES 4096 // 12 bits adc
#define FLOAT_TO_UINT32_FOR_ADC_COMPARISON(dividend, divisor) \
    ((uint32_t)(((dividend) / (divisor)) * ADCBYTES))

// Global limits apply to all outputs. If a specific output has a greater limit than the global one, the global one will be used.
#define HC_GLOBAL_MAX_CURRENT 20.0
#define LC_GLOBAL_MAX_CURRENT 10.0
#define GLOBAL_MAX_VOLTAGE 15.5
#define GLOBAL_MIN_VOLTAGE 9.0
#define GLOBAL_INRUSH_TIME_LIMIT 2000
#define GLOBAL_TOTAL_CURRENT_LIMIT 50.0

#define MAX_IO_LABEL_SIZE 4

typedef char (*condition_t)(void);

char HC0_OUTPUT_CONDITION(void);
char HC1_OUTPUT_CONDITION(void);
char HC2_OUTPUT_CONDITION(void);
char HC3_OUTPUT_CONDITION(void);

char LC0_OUTPUT_CONDITION(void);
char LC1_OUTPUT_CONDITION(void);
char LC2_OUTPUT_CONDITION(void);
char LC3_OUTPUT_CONDITION(void);

typedef struct {
    const uint8_t enable;
    const char *label;
    const uint8_t reset_enable;
    const uint8_t reset_retry_count;
    const uint8_t reset_retry_delay_seconds;
    const uint32_t current_limit;
    const uint32_t inrush_time_limit_miliseconds;
    const float max_voltage;
    const float min_voltage;
    const float max_current;
    condition_t condition_callback;
}CurrentOutputConfigTypedef;

typedef struct{
	const char label[MAX_IO_LABEL_SIZE];
	const uint8_t enable;
    uint32_t value;
	const OPDM_INPUT_TYPE input_type;
}InputConfigTypedef; // talvez tenha que usar union

extern InputConfigTypedef ANALOG_DIGITAL_INPUT[];
extern const CurrentOutputConfigTypedef CURRENT_OUTPUT_SETUP[];

//----------------- INPUT CONFIGURATION -----------------






#endif /* __OPDM_OUTPUT_CFG_H_ */
