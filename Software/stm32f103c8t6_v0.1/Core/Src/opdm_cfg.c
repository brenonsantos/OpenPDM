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

#define HC_OUTPUT_MAX_CURRENT 20.0f
#define LC_OUTPUT_MAX_CURRENT 10.0f


const CurrentOutputConfigTypedef CURRENT_OUTPUT_SETUP[] ={
    [HC0] = {
        .enable = TRUE,
        .label = "HC0",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(1.0f, HC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        .max_current = 10.0,
        .condition_callback = HC0_OUTPUT_CONDITION
    },
    [HC1] = {
        .enable = TRUE,
        .label = "HC1",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(1.0f, HC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        .max_current = 10.0,
        .condition_callback = HC1_OUTPUT_CONDITION
    },
    [HC2] = {
        .enable = TRUE,
        .label = "HC2",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(5.0f, HC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        .max_current = 10.0,
        .condition_callback = HC2_OUTPUT_CONDITION
    },
    [HC3] = {
        .enable = TRUE,
        .label = "HC3",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(5.0f, HC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        .max_current = 10.0,
        .condition_callback = HC3_OUTPUT_CONDITION
    },
    [LC0] = {
        .enable = TRUE,
        .label = "LC0",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .max_current = 10.0,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(5.0f, LC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        
        .condition_callback = LC0_OUTPUT_CONDITION
    },
    [LC1] = {
        .enable = TRUE,
        .label = "LC1",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(5.0f, LC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        .max_current = 10.0,
        .condition_callback = LC1_OUTPUT_CONDITION
    },
    [LC2] = {
        .enable = TRUE,
        .label = "LC2",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(1.0f, LC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        .max_current = 10.0,
        .condition_callback = LC2_OUTPUT_CONDITION
    },
    [LC3] = {
        .enable = TRUE,
        .label = "LC3",
        .reset_enable = FALSE,
        .reset_retry_count = 3,
        .reset_retry_delay_seconds = 2,
        .current_limit = FLOAT_TO_UINT32_FOR_ADC_COMPARISON(0.5f, LC_OUTPUT_MAX_CURRENT),
        .inrush_time_limit_miliseconds = 1000,
        .max_voltage = 15.5,
        .min_voltage = 9.0,
        .max_current = 10.0,
        .condition_callback = LC3_OUTPUT_CONDITION
    }
};
