/*
 * opdm_hal_adc.h
 *
 *  Created on: 26 de abr de 2023
 *      Author: breno
 */

#ifndef PDM_ABSTRACTION_INC_OPDM_HAL_ADC_H_
#define PDM_ABSTRACTION_INC_OPDM_HAL_ADC_H_


#include <pdm_hal_def.h>


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
}PDMHAL_CurrentSenseMapType;

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
}PDMHAL_VoltageSenseMapType;

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

void PDMHAL_ADC_StartNewInputReading(AnalogDigitalInputType new_input);
void PDMHAL_ADC_StartNewVoltageReading(PDMHAL_VoltageSenseMapType new_sense);
void PDMHAL_ADC_StartNewCurrentReading(PDMHAL_CurrentSenseMapType new_sense);

void PDMHAL_ADC_StartInputADC(void);
void PDMHAL_ADC_ContinueReadingVoltage(void);
void PDMHAL_ADC_ContinueReadingCurrent(void);


void hal_adc_teste(void);

#endif /* PDM_ABSTRACTION_INC_OPDM_HAL_ADC_H_ */
