/*
 * opdm_hal_io.h
 *
 *  Created on: Mar 21, 2023
 *      Author: breno
 */

#ifndef __OPDM_HAL_IO_H_
#define __OPDM_HAL_IO_H_

#include "stm32f1xx_hal.h"
#include "opdm_hal_io_cfg.h"
#include "opdm_output_cfg.h"



//----------------- ENUMS -----------------

// TODO: Is it really necessary to separate the high and low current outputs?
/*
typedef enum{
	HC0_OUTPUT = 0,
	HC1_OUTPUT,
	HC2_OUTPUT,
	HC3_OUTPUT,
	NUM_OF_HC_OUTPUTS
}HIGH_CURRENT_OUTPUT_TYPE;

typedef enum{
	LC0_OUTPUT = 0,
	LC1_OUTPUT,
	LC2_OUTPUT,
	LC3_OUTPUT,
	NUM_OF_LC_OUTPUTS
}LOW_CURRENT_OUTPUT_TYPE;
*/
typedef enum{
	HC0_OUTPUT = 0,
	HC1_OUTPUT,
	HC2_OUTPUT,
	HC3_OUTPUT,
	LC0_OUTPUT,
	LC1_OUTPUT,
	LC2_OUTPUT,
	LC3_OUTPUT,
	NUM_OF_CURRENT_OUTPUTS
}CURRENT_OUTPUT_TYPE;

// #define NUM_OF_CURRENT_OUTPUTS (NUM_OF_HC_OUTPUTS + NUM_OF_LC_OUTPUTS)

// typedef enum{
// 	GENERIC_INPUT_0 = 0,
// 	GENERIC_INPUT_1,
// 	GENERIC_INPUT_2,
// 	GENERIC_INPUT_3,
// 	GENERIC_INPUT_4,
// 	GENERIC_INPUT_5,
// 	GENERIC_INPUT_6,
// 	GENERIC_INPUT_7,
// 	NUM_OF_GENERIC_INPUTS
// }GENERIC_INPUT_TYPE;


typedef enum{
	CURRENT_VOLTAGE_SENSE_MULTIPLEXER_A0 = 0,
	CURRENT_VOLTAGE_SENSE_MULTIPLEXER_A1,
	CURRENT_VOLTAGE_SENSE_MULTIPLEXER_A2,
	CURRENT_VOLTAGE_SENSE_MULTIPLEXER_A3,
	NUM_OF_CURRENT_VOLTAGE_SENSE_MULTIPLEXER
}CURRENT_VOLTAGE_SENSE_MULTIPLEXER_OUTPUT_TYPE;

typedef enum{
	INPUT_MULTIPLEXER_A0 = 0,
	INPUT_MULTIPLEXER_A1,
	INPUT_MULTIPLEXER_A2,
	NUM_OF_INPUT_MULTIPLEXER
}INPUT_MULTIPLEXER_OUTPUT_TYPE;

typedef enum{
	INTERNAL_LED = 0,
	STATUS_LED = 1,
	NUM_OF_LEDS
}LED_OUTPUT_TYPE;

typedef enum{
	CANB_EN = 0,
	CANB_ERR,
	CANB_STB,
	NUM_OF_CANB_PINS
}CANB_PINS_TYPE;

typedef enum{
	CANC_INTERRUPT = 0,
	NUM_OF_CANC_PINS
}CANC_PINS_TYPE;

typedef struct
{
	GPIO_TypeDef *port;
        uint16_t pin;
} OPDM_GPIO_TYPE;


typedef struct{
        OPDM_GPIO_TYPE gpio_addr;

		char output_label[MAX_OUTPUT_LABEL_SIZE];

        uint8_t output_enable;
        uint8_t reset_enable;
        // uint8_t pwm_enable;
        // OPDM_OUTPUT_PWM_TYPE pwm;
        int inrush_time_limit;
        int reset_retry_delay;
        int reset_retry_count;
        
        float current_setpoint;
        float max_current;
        float min_voltage;
        float max_voltage;

        condition_t condition_callback;

}OPDM_CURRENT_OUTPUT_SETUP_STRUCT;



/**
  * @brief  Struct used to store the current output control variables
  *
  * @param  current_reading: 
  * @param  voltage_reading: 
  * @param  current_setpoint: 
  * @param  inrush_timer:
  * @param  retry_attempts_remaining:
  * @param  output_state:
  * @param  fault:
  * @param  fault_buffer:
  */
typedef struct{
        uint8_t output_state;
        uint8_t fault;
        uint8_t fault_buffer;
        float current_reading;
        float voltage_reading;
        float current_setpoint;
        float inrush_timer;
        int retry_attempts;
}OPDM_CURRENT_OUTPUT_CONTROL_STRUCT;

void PDM_SetCurrentOutput(CURRENT_OUTPUT_TYPE output);
void PDM_ResetCurrentOutput(CURRENT_OUTPUT_TYPE output);
void initialize_current_outputs(void);

extern OPDM_CURRENT_OUTPUT_SETUP_STRUCT CURRENT_OUTPUT_SETUP[NUM_OF_CURRENT_OUTPUTS];
extern OPDM_CURRENT_OUTPUT_CONTROL_STRUCT CURRENT_OUTPUT_CONTROL[NUM_OF_CURRENT_OUTPUTS];

/* OPDM_DRIVER_OPDM_HAL_IO_H_ */
#endif 
