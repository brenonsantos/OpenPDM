/*
 * pdm_svc_currentoutputs.c
 *
 *  Created on: 28 de abr de 2023
 *      Author: breno
 */


#include "pdm_svc_currentoutputs.h"
#include <string.h>



OPDM_CURRENT_OUTPUT_SETUP_STRUCT CURRENT_OUTPUT_SETUP[NUM_OF_CURRENT_OUTPUTS];

OPDM_CURRENT_OUTPUT_CONTROL_STRUCT CURRENT_OUTPUT_CONTROL[NUM_OF_CURRENT_OUTPUTS];


void SVC_OutputInit(){

    uint8_t OUTPUT_ENABLE_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_EN, HC1_EN, HC2_EN, HC3_EN,
            LC0_EN, LC1_EN, LC2_EN, LC3_EN
    };

    char OUTPUT_LABEL_CFG[NUM_OF_CURRENT_OUTPUTS][MAX_IO_LABEL_SIZE] = {
            HC0_LABEL, HC1_LABEL, HC2_LABEL, HC3_LABEL,
            LC0_LABEL, LC1_LABEL, LC2_LABEL, LC3_LABEL
    };

    uint8_t OUTPUT_RESET_ENABLE_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_RESET_ENABLE, HC1_RESET_ENABLE, HC2_RESET_ENABLE, HC3_RESET_ENABLE,
            LC0_RESET_ENABLE, LC1_RESET_ENABLE, LC2_RESET_ENABLE, LC3_RESET_ENABLE
    };

    int OUTPUT_RESET_RETRY_DELAY_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_RESET_RETRY_DELAY, HC1_RESET_RETRY_DELAY, HC2_RESET_RETRY_DELAY, HC3_RESET_RETRY_DELAY,
            LC0_RESET_RETRY_DELAY, LC1_RESET_RETRY_DELAY, LC2_RESET_RETRY_DELAY, LC3_RESET_RETRY_DELAY,
    };

    int OUTPUT_INRUSH_TIME_LIMIT_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_INRUSH_TIME_LIMIT, HC1_INRUSH_TIME_LIMIT, HC2_INRUSH_TIME_LIMIT, HC3_INRUSH_TIME_LIMIT,
            LC0_INRUSH_TIME_LIMIT, LC1_INRUSH_TIME_LIMIT, LC2_INRUSH_TIME_LIMIT, LC3_INRUSH_TIME_LIMIT
    };

    int OUTPUT_RESET_RETRY_COUNT_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_RESET_RETRY_COUNT, HC1_RESET_RETRY_COUNT, HC2_RESET_RETRY_COUNT, HC3_RESET_RETRY_COUNT,
            LC0_RESET_RETRY_COUNT, LC1_RESET_RETRY_COUNT, LC2_RESET_RETRY_COUNT, LC3_RESET_RETRY_COUNT
    };

    float OUTPUT_MAX_CCURRENT_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_MAX_CURRENT, HC1_MAX_CURRENT, HC2_MAX_CURRENT, HC3_MAX_CURRENT,
            LC0_MAX_CURRENT, LC1_MAX_CURRENT, LC2_MAX_CURRENT, LC3_MAX_CURRENT
    };

    float OUTPUT_MIN_VOLTAGE_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_MIN_VOLTAGE, HC1_MIN_VOLTAGE, HC2_MIN_VOLTAGE, HC3_MIN_VOLTAGE,
            LC0_MIN_VOLTAGE, LC1_MIN_VOLTAGE, LC2_MIN_VOLTAGE, LC3_MIN_VOLTAGE
    };

    float OUTPUT_MAX_VOLTAGE_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_MAX_VOLTAGE, HC1_MAX_VOLTAGE, HC2_MAX_VOLTAGE, HC3_MAX_VOLTAGE,
            LC0_MAX_VOLTAGE, LC1_MAX_VOLTAGE, LC2_MAX_VOLTAGE, LC3_MAX_VOLTAGE
    };

    float OUTPUT_CURRENT_SETPOINT_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_CURRENT_SETPOINT, HC1_CURRENT_SETPOINT, HC2_CURRENT_SETPOINT, HC3_CURRENT_SETPOINT,
            LC0_CURRENT_SETPOINT, LC1_CURRENT_SETPOINT, LC2_CURRENT_SETPOINT, LC3_CURRENT_SETPOINT
    };

    static const condition_t OUTPUT_CONDITION_CFG[NUM_OF_CURRENT_OUTPUTS] = {
            HC0_OUTPUT_CONDITION, HC1_OUTPUT_CONDITION, HC2_OUTPUT_CONDITION, HC3_OUTPUT_CONDITION,
            LC0_OUTPUT_CONDITION, LC1_OUTPUT_CONDITION, LC2_OUTPUT_CONDITION, LC3_OUTPUT_CONDITION
    };


    for(int i = 0; i < NUM_OF_CURRENT_OUTPUTS; i++){
        if (OUTPUT_INRUSH_TIME_LIMIT_CFG[i] > GLOBAL_INRUSH_TIME_LIMIT){
            OUTPUT_INRUSH_TIME_LIMIT_CFG[i] = GLOBAL_INRUSH_TIME_LIMIT;
        }
        if (OUTPUT_MAX_VOLTAGE_CFG[i] > GLOBAL_MAX_VOLTAGE){
            OUTPUT_MAX_VOLTAGE_CFG[i] = GLOBAL_MAX_VOLTAGE;
        }

        if (OUTPUT_MIN_VOLTAGE_CFG[i] < GLOBAL_MIN_VOLTAGE){
            OUTPUT_MIN_VOLTAGE_CFG[i] = GLOBAL_MIN_VOLTAGE;
        }

        if (OUTPUT_INRUSH_TIME_LIMIT_CFG[i] > GLOBAL_INRUSH_TIME_LIMIT){
            OUTPUT_INRUSH_TIME_LIMIT_CFG[i] = GLOBAL_INRUSH_TIME_LIMIT;
        }

        strcpy(CURRENT_OUTPUT_SETUP[i].output_label, OUTPUT_LABEL_CFG[i]);
        CURRENT_OUTPUT_SETUP[i].output_enable = OUTPUT_ENABLE_CFG[i];
        CURRENT_OUTPUT_SETUP[i].reset_enable = OUTPUT_RESET_ENABLE_CFG[i];
        CURRENT_OUTPUT_SETUP[i].inrush_time_limit = OUTPUT_INRUSH_TIME_LIMIT_CFG[i];
        CURRENT_OUTPUT_SETUP[i].reset_retry_delay = OUTPUT_RESET_RETRY_DELAY_CFG[i];
        CURRENT_OUTPUT_SETUP[i].reset_retry_count = OUTPUT_RESET_RETRY_COUNT_CFG[i];
        CURRENT_OUTPUT_SETUP[i].current_setpoint = OUTPUT_CURRENT_SETPOINT_CFG[i];
        CURRENT_OUTPUT_SETUP[i].max_current = OUTPUT_MAX_CCURRENT_CFG[i];
        CURRENT_OUTPUT_SETUP[i].min_voltage = OUTPUT_MIN_VOLTAGE_CFG[i];
        CURRENT_OUTPUT_SETUP[i].max_voltage = OUTPUT_MAX_VOLTAGE_CFG[i];
        CURRENT_OUTPUT_SETUP[i].condition_callback = OUTPUT_CONDITION_CFG[i];

        CURRENT_OUTPUT_CONTROL[i].output_state = FALSE;
        CURRENT_OUTPUT_CONTROL[i].fault = FALSE;
        CURRENT_OUTPUT_CONTROL[i].fault_buffer = FALSE;
        CURRENT_OUTPUT_CONTROL[i].current_reading = 0.0;
        CURRENT_OUTPUT_CONTROL[i].voltage_reading = 0.0;
        CURRENT_OUTPUT_CONTROL[i].current_setpoint = 0.0;
        CURRENT_OUTPUT_CONTROL[i].inrush_timer = 0;
        CURRENT_OUTPUT_CONTROL[i].retry_attempts = 0;
    }
}

uint8_t isOutputEnable(PDMHAL_OutputType output_addr){
	return CURRENT_OUTPUT_SETUP[output_addr].output_enable;
}

PDMHAL_OutputType getNextEnabledOutput(PDMHAL_OutputType current_output){
	for(PDMHAL_OutputType i = current_output+1; i < NUM_OF_OUTPUTS; i++){
		if(isOutputEnable(i)) return i;
	}
	for(PDMHAL_OutputType i = 0; i <= current_output; i++){
		if(isOutputEnable(i)) return i;
	}
	return 0;
}

void SVC_OUTPUT_UpdateVoltageAndCurrentSense(void){
	static PDMHAL_AnalogInputType reading_index = 0;
	static uint32_t reading = 0;
	static uint32_t moving_average_data_voltage[NUM_OF_AD_INPUTS][VOLTAGE_WINDOW_SIZE] = {0};
	static uint32_t moving_average_data_current[NUM_OF_AD_INPUTS][CURRENT_WINDOW_SIZE] = {0};
    static uint8_t reading_voltage = TRUE;

    PDMHAL_AdcStatusType conversion_status;

    conversion_status = PDMHAL_ADC_CheckConversionStatusVoltage();

	/* As  there is only one mux for both voltage and current sense, 
	 * only one can be read at a time */
    if (reading_voltage) {
        switch(conversion_status){
            case (READY):
				reading_index = getNextEnabledOutput(NUM_OF_OUTPUTS);
				PDMHAL_ADC_StartNewVoltageReading(reading_index);
				break;
            case (BUSY):
                return;
            case (CONVERSION_COMPLETE):
				reading = PDMHAL_ADC_ReadOutputVoltage();
            	reading = moving_average(moving_average_data_voltage[reading_index], reading, VOLTAGE_WINDOW_SIZE);
				CURRENT_OUTPUT_CONTROL[reading_index].voltage_reading = reading;

				reading_voltage = FALSE;
				PDMHAL_ADC_StartNewCurrentReading(reading_index);
				return;
        }
    }

	switch(conversion_status){
	case (READY):
		reading_voltage = TRUE;
		return;
	case (BUSY):
		return;
	case (CONVERSION_COMPLETE):
		reading = PDMHAL_ADC_ReadOutputCurrent();
		reading = moving_average(moving_average_data_current[reading_index], reading, CURRENT_WINDOW_SIZE);
		CURRENT_OUTPUT_CONTROL[reading_index].current_reading = reading;

		reading_voltage = TRUE;
		reading_index = getNextEnabledOutput(reading_index);
		PDMHAL_ADC_StartNewVoltageReading(reading_index);
		return;
	}
}



