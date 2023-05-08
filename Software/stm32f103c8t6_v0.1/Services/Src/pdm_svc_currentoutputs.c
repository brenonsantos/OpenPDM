/*
 * pdm_svc_currentoutputs.c
 *
 *  Created on: 28 de abr de 2023
 *      Author: breno
 */


#include "pdm_svc_currentoutputs.h"
#include <string.h>



PDMHAL_AdcStatusType SVC_GetConversionStatusVoltage(void){
    return PDMHAL_ADC_CheckConversionStatusVoltage();
}

PDMHAL_AdcStatusType SVC_GetConversionStatusCurrent(void){
    return PDMHAL_ADC_CheckConversionStatusCurrent();
}

uint32_t SVC_ReadVoltage(CurrentOutputsTypedef reading_index){
    static uint32_t moving_average_data[NUM_OF_OUTPUTS][VOLTAGE_WINDOW_SIZE] = {0};

    uint32_t reading = PDMHAL_ADC_ReadOutputVoltage();
    reading = moving_average(moving_average_data[reading_index], reading, VOLTAGE_WINDOW_SIZE);
    return reading;
}

uint32_t SVC_ReadCurrent(CurrentOutputsTypedef reading_index){
    static uint32_t moving_average_data[NUM_OF_OUTPUTS][CURRENT_WINDOW_SIZE] = {0};

    uint32_t reading = PDMHAL_ADC_ReadOutputCurrent();
    reading = moving_average(moving_average_data[reading_index], reading, CURRENT_WINDOW_SIZE);
    return reading;
}


