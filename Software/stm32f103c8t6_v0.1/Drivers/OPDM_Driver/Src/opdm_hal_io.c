/*
 * opdm_hal_io.c
 *
 *  Created on: Mar 28, 2023
 *      Author: breno
 */

#include "opdm_hal_io.h"

//-------------------- Defines --------------------

typedef struct
{
        GPIO_TypeDef port;
        uint16_t pin;
} OPDM_GPIO_TYPE;

typedef struct
{
        OPDM_GPIO_TYPE port_n_pin;

        uint8_t enable;
        uint8_t fault;

        float current_reading;
        float voltage_reading;

        float current_setpoint;
        float max_current;
        float min_voltage;
        float max_voltage;


}OPDM_CURRENT_OUTPUT_TYPE;

OPDM_CURRENT_OUTPUT_TYPE CURRENT_OUTPUT[NUM_OF_LC_OUTPUTS + NUM_OF_HC_OUTPUTS];

// TODO: Is it really necessary to separate the high and low current outputs? Same in opdm_hal_io.h
/*
OPDM_GPIO_TYPE HIGH_CURRENT_OUTPUT[NUM_OF_HC_OUTPUTS] = {
        {{GATE_HC0_SIG_GPIO_Port, GATE_HC0_SIG_Pin}},
        {{GATE_HC1_SIG_GPIO_Port, GATE_HC1_SIG_Pin}},
        {{GATE_HC2_SIG_GPIO_Port, GATE_HC2_SIG_Pin}},
        {{GATE_HC3_SIG_GPIO_Port, GATE_HC3_SIG_Pin}},
};

OPDM_GPIO_TYPE LOW_CURRENT_OUTPUT[NUM_OF_LC_OUTPUTS] = {
        {{GATE_LC0_SIG_GPIO_Port, GATE_LC0_SIG_Pin}},
        {{GATE_LC1_SIG_GPIO_Port, GATE_LC1_SIG_Pin}},
        {{GATE_LC2_SIG_GPIO_Port, GATE_LC2_SIG_Pin}},
        {{GATE_LC3_SIG_GPIO_Port, GATE_LC3_SIG_Pin}},
};
*/

OPDM_GPIO_TYPE CURRENT_OUTPUT_GPIO[NUM_OF_CURRENT_OUTPUTS] = {
    {{GATE_HC0_SIG_GPIO_Port, GATE_HC0_SIG_Pin}},
    {{GATE_HC1_SIG_GPIO_Port, GATE_HC1_SIG_Pin}},
    {{GATE_HC2_SIG_GPIO_Port, GATE_HC2_SIG_Pin}},
    {{GATE_HC3_SIG_GPIO_Port, GATE_HC3_SIG_Pin}},
    {{GATE_LC0_SIG_GPIO_Port, GATE_LC0_SIG_Pin}},
    {{GATE_LC1_SIG_GPIO_Port, GATE_LC1_SIG_Pin}},
    {{GATE_LC2_SIG_GPIO_Port, GATE_LC2_SIG_Pin}},
    {{GATE_LC3_SIG_GPIO_Port, GATE_LC3_SIG_Pin}},
};

uint8_t CURRENT_OUTPUT_ENABLE[NUM_OF_CURRENT_OUTPUTS] = {
        HC0_EN,
        HC1_EN,
        HC2_EN,
        HC3_EN,
        LC0_EN,
        LC1_EN,
        LC2_EN,
        LC3_EN,
};


OPDM_GPIO_TYPE CURRENT_VOLTAGE_SENSE_MUTIPLEXER[NUM_OF_CURRENT_VOLTAGE_SENSE_MULTIPLEXER] = {
    {{MUX_CUR_SENSE_A0_GPIO_Port, MUX_CUR_SENSE_A0_Pin}},
    {{MUX_CUR_SENSE_A1_GPIO_Port, MUX_CUR_SENSE_A1_Pin}},
    {{MUX_CUR_SENSE_A2_GPIO_Port, MUX_CUR_SENSE_A2_Pin}},
    {{MUX_CUR_SENSE_A3_GPIO_Port, MUX_CUR_SENSE_A3_Pin}},
};

// OPDM_GPIO_TYPE GENERIC_INPUT[NUM_OF_GENERIC_INPUTS] = {
//         {GENERIC_INPUT_0_GPIO_Port, GENERIC_INPUT_0_Pin},
//         {GENERIC_INPUT_1_GPIO_Port, GENERIC_INPUT_1_Pin},
//         {GENERIC_INPUT_2_GPIO_Port, GENERIC_INPUT_2_Pin},
//         {GENERIC_INPUT_3_GPIO_Port, GENERIC_INPUT_3_Pin},
//         {GENERIC_INPUT_4_GPIO_Port, GENERIC_INPUT_4_Pin},
//         {GENERIC_INPUT_5_GPIO_Port, GENERIC_INPUT_5_Pin},
//         {GENERIC_INPUT_6_GPIO_Port, GENERIC_INPUT_6_Pin},
//         {GENERIC_INPUT_7_GPIO_Port, GENERIC_INPUT_7_Pin}
// };


void initialize_current_outputs(){
        
        initialize_high_current_outputs();
        initialize_low_current_outputs();
}

void initialize_high_current_outputs(){
        for(int i = 0; i < NUM_OF_HC_OUTPUTS; i++){
                CURRENT_OUTPUT[i].port_n_pin = CURRENT_OUTPUT_GPIO[i];
                CURRENT_OUTPUT[i].enable = CURRENT_OUTPUT_ENABLE[i];
                CURRENT_OUTPUT[i].fault = FALSE;
                CURRENT_OUTPUT[i].current_reading = 0.0;
                CURRENT_OUTPUT[i].voltage_reading = 0.0;
                CURRENT_OUTPUT[i].current_setpoint = 0.0;
                CURRENT_OUTPUT[i].max_current = HC_MAX_CURRENT;
                CURRENT_OUTPUT[i].min_voltage = HC_MIN_VOLTAGE;
                CURRENT_OUTPUT[i].max_voltage = HC_MAX_VOLTAGE;
        }
}

void initialize_low_current_outputs(){
        for(int i = NUM_OF_HC_OUTPUTS; i < NUM_OF_LC_OUTPUTS; i++){
                CURRENT_OUTPUT[i].port_n_pin = CURRENT_OUTPUT_GPIO[i];
                CURRENT_OUTPUT[i].enable = CURRENT_OUTPUT_ENABLE[i];
                CURRENT_OUTPUT[i].fault = FALSE;
                CURRENT_OUTPUT[i].current_reading = 0.0;
                CURRENT_OUTPUT[i].voltage_reading = 0.0;
                CURRENT_OUTPUT[i].current_setpoint = 0.0;
                CURRENT_OUTPUT[i].max_current = LC_MAX_CURRENT;
                CURRENT_OUTPUT[i].min_voltage = LC_MIN_VOLTAGE;
                CURRENT_OUTPUT[i].max_voltage = LC_MAX_VOLTAGE;
        }
}


void PDM_SetCurrentOutput(CURRENT_OUTPUT_TYPE output)
{
        HAL_GPIO_WritePin(CURRENT_OUTPUT[output].port, CURRENT_OUTPUT[output].pin, GPIO_PIN_SET);
}

void PDM_ResetCurrentOutput(CURRENT_OUTPUT_TYPE output)
{
        HAL_GPIO_WritePin(CURRENT_OUTPUT[output].port, CURRENT_OUTPUT[output].pin, GPIO_PIN_RESET);
}

