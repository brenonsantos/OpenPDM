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


/* The formula that correlates the current reading with the adc reading is:
 * adc_reading = (current * shunt_resistance * current_gain) * (adc_bytes/adc_voltage)
 * where:
 * - current is the current that is being read
 * - shunt_resistance is 3.3m ohms
 * - current_gain is the gain of the current amplifier, that is 100 for LC and 50 for HC
 * - adc_bits is the number of bits that the adc can read, that is 4096
 * - adc_voltage is the max voltage that the adc can read, that is 3.3
 *
 * as shunt_resistance, current_gain, adc_bytes and adc_voltage are constants, we can simplify the formula to:
 * adc_reading_lc = current*372.36
 * adc_reading_hc = current*186.18
*/

#define HC_CURRENT_CONVERSION_TO_12BITS(current) \
    ((uint32_t)(current*186.18))

#define LC_CURRENT_CONVERSION_TO_12BITS(current) \
    ((uint32_t)(current*372.36))



/* The formula that correlates the output voltage reading with the adc reading is:
    * adc_reading = (voltage * voltage_divider_ratio) * adc_bits / adc_voltage
    * where:
    * - voltage is the voltage that is being read
    * - voltage_divider_ratio is R1/(R1+R2), that is 36k/(36k+10k)
    * - adc_bits is the number of bits of the adc, that is 4096
    * - adc_voltage is the max voltage that the adc can read, that is 3.3
    *
    * as voltage_divider_ratio, adc_bytes, adc_voltage are constants, we can simplify the formula to:
    * adc_reading = voltage * 269.83
*/
#define VOLTAGE_CONVERSION_TO_12BITS(voltage) \
	((uint32_t)(voltage*269.83))


//----------------- OUTPUT CONFIGURATION -----------------



// Global limits apply to all outputs. If a specific output has a greater limit than the global one, the global one will be used.
#define HC_GLOBAL_MAX_CURRENT 20.0f
#define LC_GLOBAL_MAX_CURRENT 10.0f
#define GLOBAL_MAX_VOLTAGE 15.5f
#define GLOBAL_MIN_VOLTAGE 9.0f
#define GLOBAL_INRUSH_TIME_LIMIT 2000
#define GLOBAL_TOTAL_CURRENT_LIMIT 50.0f

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
    const uint8_t reset_retry_attempts;
    const uint8_t reset_retry_delay_seconds;
    const uint32_t current_limit;
    const uint32_t inrush_time_limit_miliseconds;
    const uint32_t max_voltage;
    const uint32_t min_voltage;
    const uint32_t max_current;
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
