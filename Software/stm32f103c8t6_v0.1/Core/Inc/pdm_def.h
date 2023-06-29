/*
 * pdm_def.h
 *
 *  Created on: 6 de mai de 2023
 *      Author: breno
 */

#ifndef __PDM_DEF_H
#define __PDM_DEF_H

typedef uint8_t (*condition_t)(void);

#define TRUE 1
#define FALSE 0
#define USE_USB_OVER_CANB 1

typedef enum{
	HC0,
	HC1,
	HC2,
	HC3,
	LC0,
	LC1,
	LC2,
	LC3,
	NUM_OF_OUTPUTS
}CurrentOutputsTypedef;

typedef enum{
	INPUT_00 = 0,
	INPUT_01,
	INPUT_02,
	INPUT_03,
	INPUT_04,
	INPUT_05,
	INPUT_06,
	INPUT_07,
	NUM_OF_AD_INPUTS
}AnalogDigitalInputType;

typedef enum{
  CAN_IN_00,
  CAN_IN_01,
  CAN_IN_02,
  NUM_OF_CAN_RECEIVERS
}CanBusReceiverType;

typedef enum{
  CAN_OUT_00,
  CAN_OUT_01,
  NUM_OF_CAN_TRANSMITERS
}CanBusTransmiterType;

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

#endif /* PDM_DEF*/
