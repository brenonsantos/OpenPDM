/*
 * opdm_hal_adc.h
 *
 *  Created on: 26 de abr de 2023
 *      Author: breno
 */

#ifndef OPDM_DRIVER_INC_OPDM_HAL_ADC_H_
#define OPDM_DRIVER_INC_OPDM_HAL_ADC_H_


#include "opdm_hal_def.h"


typedef enum{
	READY = 0,
	BUSY,
	CONVERSION_COMPLETE
}PDMHAL_AdcStatusType;

typedef enum{
	INPUT_MUX_A0 = 0,
	INPUT_MUX_A1,
	INPUT_MUX_A2,
	NUM_OF_INPUT_MULTIPLEXER
}PDMHAL_InputMuxOutputType;

typedef enum{
	CV_SENSE_MUX_A0 = 0,
	CV_SENSE_MUX_A1,
	CV_SENSE_MUX_A2,
	CV_SENSE_MUX_A3,
	NUM_OF_CURRENT_VOLTAGE_SENSE_MULTIPLEXER
}PDMHAL_CVMuxOutputType;

typedef enum{
	ANALOG_DIGITAL_INPUT_0 = 0,
	ANALOG_DIGITAL_INPUT_1,
	ANALOG_DIGITAL_INPUT_2,
	ANALOG_DIGITAL_INPUT_3,
	ANALOG_DIGITAL_INPUT_4,
	ANALOG_DIGITAL_INPUT_5,
	ANALOG_DIGITAL_INPUT_6,
	ANALOG_DIGITAL_INPUT_7,
	NUM_OF_AD_INPUTS
}PDMHAL_AnalogInputType;


/* The order of the CurrentSenseType and VoltageSenseType are defined by the order
 * of activation on the multiplexer IC
*/
typedef enum{
	CURRENT_SENSE_HC3 = 0,
	CURRENT_SENSE_HC2,
	CURRENT_SENSE_HC1,
	CURRENT_SENSE_HC0,
	CURRENT_SENSE_LC0,
	CURRENT_SENSE_LC1,
	CURRENT_SENSE_LC2,
	CURRENT_SENSE_LC3,
	NUM_OF_CURRENT_SENSES
}PDMHAL_CurrentSenseType;

typedef enum{
	VOLTAGE_SENSE_LC0 = 0,
	VOLTAGE_SENSE_LC1,
	VOLTAGE_SENSE_LC2,
	VOLTAGE_SENSE_LC3,
	VOLTAGE_SENSE_HC0,
	VOLTAGE_SENSE_HC1,
	VOLTAGE_SENSE_HC2,
	VOLTAGE_SENSE_HC3,
	NUM_OF_VOLTAGE_SENSES
}PDMHAL_VoltageSenseType;

typedef enum{
	OUTPUT_HC0 = 0,
	OUTPUT_HC1,
	OUTPUT_HC2,
	OUTPUT_HC3,
	OUTPUT_LC0,
	OUTPUT_LC1,
	OUTPUT_LC2,
	OUTPUT_LC3,
	NUM_OF_OUTPUTS
}PDMHAL_OutputType;

typedef enum{
	VOLTAGE_WINDOW_SIZE = 10,
	CURRENT_WINDOW_SIZE = 10,
	ADINPUT_WINDOW_SIZE = 10
}MOVING_AVERAGE_WINDOW_SIZE;

void PDMHAL_ADC_Init(void);

PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatusInput(void);
PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatusCurrent(void);
PDMHAL_AdcStatusType PDMHAL_ADC_CheckConversionStatusVoltage(void);

uint32_t PDMHAL_ADC_ReadInput(void);
uint32_t PDMHAL_ADC_ReadOutputVoltage(void);
uint32_t PDMHAL_ADC_ReadOutputCurrent(void);

void PDMHAL_ADC_StartNewInputReading(PDMHAL_AnalogInputType new_input);
void PDMHAL_ADC_StartNewVoltageReading(PDMHAL_VoltageSenseType new_sense);
void PDMHAL_ADC_StartNewCurrentReading(PDMHAL_CurrentSenseType new_sense);

void PDMHAL_ADC_StartInputADC(void);
void PDMHAL_ADC_ContinueReadingVoltage(void);
void PDMHAL_ADC_ContinueReadingCurrent(void);


void hal_adc_teste(void);

#endif /* OPDM_DRIVER_INC_OPDM_HAL_ADC_H_ */
