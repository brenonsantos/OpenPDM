

#include "pdm_svc_adinputs.h"
#include <string.h>


PDMHAL_AdcStatusType SVC_GetConversionStatusInput(void){
    return PDMHAL_ADC_CheckConversionStatusInput();
}

uint32_t SVC_ReadInput(AnalogDigitalInputType reading_index){
    static uint32_t moving_average_data[NUM_OF_AD_INPUTS][ADINPUT_WINDOW_SIZE] = {0};

    uint32_t reading = PDMHAL_ADC_ReadInput();
    reading = moving_average(moving_average_data[reading_index], reading, ADINPUT_WINDOW_SIZE);
    return reading;
}
