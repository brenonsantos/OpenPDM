/*
 * opdm_output_cfg.c
 *
 *  Created on: 31 de mar de 2023
 *      Author: breno
 */

#include "opdm_cfg.h"




/* TODO: this is a temporary solution. Probably it shouldn't receive void, but the CAN messages and the inputs readings.

char OUTPUT_CONDITION(condition_t condition_function, can_msgs, inputs){
    return condition_function(can_msgs, inputs);
}
*/
char OUTPUT_CONDITION(condition_t condition_function){
    return condition_function();
}

char HC0_OUTPUT_CONDITION(void){
    return TRUE;
}

char HC1_OUTPUT_CONDITION(void){
    return TRUE;
}

char HC2_OUTPUT_CONDITION(void){
    return TRUE;
}

char HC3_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC0_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC1_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC2_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC3_OUTPUT_CONDITION(void){
    return TRUE;
}


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


InputConfigTypedef ANALOG_DIGITAL_INPUT[] ={
		[ANALOG_DIGITAL_INPUT_0] = {
				.enable = TRUE,
				.label = "IN0",
				.input_type = DIGITAL_ACTIVE_H,
                .value = 0,
		},
        [ANALOG_DIGITAL_INPUT_1] = {
                .enable = FALSE,
                .label = "IN1",
				.input_type = DIGITAL_ACTIVE_H,
                .value = 0,
		},
        [ANALOG_DIGITAL_INPUT_2] = {
                .enable = TRUE,
                .label = "IN2",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [ANALOG_DIGITAL_INPUT_3] = {
                .enable = TRUE,
                .label = "IN3",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [ANALOG_DIGITAL_INPUT_4] = {
                .enable = FALSE,
                .label = "IN4",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [ANALOG_DIGITAL_INPUT_5] = {
                .enable = TRUE,
                .label = "IN5",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [ANALOG_DIGITAL_INPUT_6] = {
                .enable = TRUE,
                .label = "IN6",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [ANALOG_DIGITAL_INPUT_7] = {
                .enable = TRUE,
                .label = "IN7",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        }
};

const CurrentOutputConfigTypedef CURRENT_OUTPUT_SETUP[] ={
    [HC0] = {
        .enable = TRUE,
        .label = "HC0",
        .reset_enable = TRUE,
        .reset_retry_attempts = 5,
        .reset_retry_delay_seconds = 5,
        .current_limit = HC_CURRENT_CONVERSION_TO_12BITS(1.0f),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
        .max_current = HC_CURRENT_CONVERSION_TO_12BITS(HC_GLOBAL_MAX_CURRENT),
        .condition_callback = HC0_OUTPUT_CONDITION
    },
    [HC1] = {
        .enable = TRUE,
        .label = "HC1",
        .reset_enable = TRUE,
        .reset_retry_attempts = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = HC_CURRENT_CONVERSION_TO_12BITS(1.0f),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
        .max_current = HC_CURRENT_CONVERSION_TO_12BITS(HC_GLOBAL_MAX_CURRENT),
        .condition_callback = HC1_OUTPUT_CONDITION
    },
    [HC2] = {
        .enable = TRUE,
        .label = "HC2",
        .reset_enable = TRUE,
        .reset_retry_attempts = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = HC_CURRENT_CONVERSION_TO_12BITS(5.0f),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
        .max_current = HC_CURRENT_CONVERSION_TO_12BITS(HC_GLOBAL_MAX_CURRENT),
        .condition_callback = HC2_OUTPUT_CONDITION
    },
    [HC3] = {
        .enable = TRUE,
        .label = "HC3",
        .reset_enable = FALSE,
        .reset_retry_attempts = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = HC_CURRENT_CONVERSION_TO_12BITS(0.5f),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
        .max_current = HC_CURRENT_CONVERSION_TO_12BITS(HC_GLOBAL_MAX_CURRENT),
        .condition_callback = HC3_OUTPUT_CONDITION
    },
    [LC0] = {
		.enable = TRUE,
		.label = "LC0",
		.reset_enable = FALSE,
		.reset_retry_attempts = 3,
		.reset_retry_delay_seconds = 2,
		.current_limit = LC_CURRENT_CONVERSION_TO_12BITS(5.0f),
		.inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
		.max_current = LC_CURRENT_CONVERSION_TO_12BITS(LC_GLOBAL_MAX_CURRENT),
        .condition_callback = LC0_OUTPUT_CONDITION
    },
    [LC1] = {
        .enable = TRUE,
        .label = "LC1",
        .reset_enable = FALSE,
        .reset_retry_attempts = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = LC_CURRENT_CONVERSION_TO_12BITS(5.0f),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
        .max_current = LC_CURRENT_CONVERSION_TO_12BITS(LC_GLOBAL_MAX_CURRENT),
        .condition_callback = LC1_OUTPUT_CONDITION
    },
    [LC2] = {
        .enable = TRUE,
        .label = "LC2",
        .reset_enable = FALSE,
        .reset_retry_attempts = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = LC_CURRENT_CONVERSION_TO_12BITS(2.5f),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
        .max_current = LC_CURRENT_CONVERSION_TO_12BITS(LC_GLOBAL_MAX_CURRENT),
        .condition_callback = LC2_OUTPUT_CONDITION
    },
    [LC3] = {
        .enable = TRUE,
        .label = "LC3",
        .reset_enable = FALSE,
        .reset_retry_attempts = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = LC_CURRENT_CONVERSION_TO_12BITS(0.5f),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = VOLTAGE_CONVERSION_TO_12BITS(15.0f),
        .min_voltage = VOLTAGE_CONVERSION_TO_12BITS(9.0f),
        .max_current = LC_CURRENT_CONVERSION_TO_12BITS(LC_GLOBAL_MAX_CURRENT),
        .condition_callback = LC3_OUTPUT_CONDITION
    }
};


