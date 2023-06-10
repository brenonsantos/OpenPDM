/*
 * opdm_output_cfg.c
 *
 *  Created on: 31 de mar de 2023
 *      Author: breno
 */

#include "opdm_cfg.h"

//extern CANBusReceiverTypedef CANBUS_RECEIVER_FRAMES[];
extern CANBusReceiverTypedef CANBUS_RECEIVER_FRAMES[NUM_OF_CAN_RECEIVERS];
extern CANBusTransmiterTypedef CANBUS_TRANSMITER_FRAMES[NUM_OF_CAN_TRANSMITERS];


/* TODO: this is a temporary solution. Probably it shouldn't receive void, but the CAN messages and the inputs readings.

char OUTPUT_CONDITION(condition_t condition_function, can_msgs, inputs){
    return condition_function(can_msgs, inputs);
}
*/

/**
 ===============================================================================
                      ##### OUTPUT Configuration #####
 ===============================================================================

	 Each output has a "condition" function that determines when and how to
   turn it on or off.  Returning a FALSE statement will turn off the output,
   while returning a TRUE statement will request the output to turn on. If
   there are no faults detected in this output, it will remain turned on.

	 You can use the following (every) global variables:
	 - ANALOG_DIGITAL_INPUT[NUM_OF_INPUTS]
	 - CURRENT_OUTPUT_SETUP[NUM_OF_OUTPUTS]
	 - CURRENT_OUTPUT_CONTROL[NUM_OF_OUTPUTS]
	 - CANBUS_RECEIVER_FRAMES[NUM_OF_CAN_RECEIVERS]
	 - CANBUS_TRANSMITER_FRAMES[NUM_OF_CAN_TRANSMITERS]
 * */

uint8_t OUTPUT_CONDITION(condition_t condition_function){
    return condition_function();
}

uint8_t HC0_OUTPUT_CONDITION(void){
	if (ANALOG_DIGITAL_INPUT[INPUT_00].value > 1000)
		return TRUE;
	return FALSE;
}

uint8_t HC1_OUTPUT_CONDITION(void){
    return FALSE;
}

uint8_t HC2_OUTPUT_CONDITION(void){
    return FALSE;
}

uint8_t HC3_OUTPUT_CONDITION(void){
    return FALSE;
}

uint8_t LC0_OUTPUT_CONDITION(void){
	if (ANALOG_DIGITAL_INPUT[INPUT_00].value > 500)
		return TRUE;
	return FALSE;
}

uint8_t LC1_OUTPUT_CONDITION(void){
    return FALSE;
}

uint8_t LC2_OUTPUT_CONDITION(void){
    return FALSE;
}

uint8_t LC3_OUTPUT_CONDITION(void){
    return FALSE;
}

uint8_t CAN0_OUTPUT_FRAME(void){
  CAN_OUTPUT_Transmit_CurrentSense(LC0);
  return TRUE;
//  CAN_OUTPUT_Transmit_32to16bits();
//  CAN_OUTPUT_Transmit_32to32bits();

//  uint8_t dlc = 8;
//  uint8_t data[dlc];
//  uint32_t voltage = 2534;
//  data[0] = voltage;
//
//  CANBUS_TRANSMITER_FRAMES[CAN_OUT_00].frame->data = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
}



InputConfigTypedef ANALOG_DIGITAL_INPUT[] ={
		[INPUT_00] = {
				.enable = TRUE,
				.label = "IN0",
				.input_type = DIGITAL_ACTIVE_H,
                .value = 0,
		},
        [INPUT_01] = {
                .enable = FALSE,
                .label = "IN1",
				.input_type = DIGITAL_ACTIVE_H,
                .value = 0,
		},
        [INPUT_02] = {
                .enable = TRUE,
                .label = "IN2",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [INPUT_03] = {
                .enable = TRUE,
                .label = "IN3",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [INPUT_04] = {
                .enable = FALSE,
                .label = "IN4",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [INPUT_05] = {
                .enable = TRUE,
                .label = "IN5",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [INPUT_06] = {
                .enable = TRUE,
                .label = "IN6",
                .input_type = DIGITAL_ACTIVE_H,
                .value = 0,
        },
        [INPUT_07] = {
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



void CONFIG_CAN_RECEIVERS(void){
  CANBUS_RECEIVER_FRAMES[CAN_IN_00] = (CANBusReceiverTypedef){
    .label = "iCAN0",
    .status = CAN_MSG_NOT_RECEIVED,
    .size = CAN_MSG_SIZE_1FRAME,
    .timeout_ms = 1000,
    .frame = {
      .frame.CANBus = CAN_C,
      .frame.idType = CAN_Standard,
      .frame.id = 0x40,
    }
  };

  CANBUS_RECEIVER_FRAMES[CAN_IN_01] = (CANBusReceiverTypedef){
    .label = "iCAN1",
    .status = CAN_MSG_NOT_RECEIVED,
    .size = CAN_MSG_SIZE_1FRAME,
    .timeout_ms = 1000,
    .frame = {
      .frame.CANBus = CAN_B,
      .frame.idType = CAN_Standard,
      .frame.id = 0x35,
    }
  };

  CANBUS_RECEIVER_FRAMES[CAN_IN_02] = (CANBusReceiverTypedef){
    .label = "iCAN2",
    .status = CAN_MSG_NOT_RECEIVED,
    .size = CAN_MSG_SIZE_1FRAME,
    .timeout_ms = 1000,
    .frame = {
      .frame.CANBus = CAN_B,
      .frame.idType = CAN_Standard,
      .frame.id = 0x35,
    }
  };
}



void CONFIG_CAN_TRANSMITER(void){
  CANBUS_TRANSMITER_FRAMES[CAN_OUT_01] = (CANBusTransmiterTypedef){
    .label = "oCAN0",
    .timeout_ms = 1000,
	.frequency_hz = 2,
    .frame = {
      .frame.CANBus = CAN_C,
      .frame.idType = CAN_Standard,
      .frame.id = 0x40,
      .frame.dataLengthCode = 8,
//      .frame.data = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48}
    }
  };

  CANBUS_TRANSMITER_FRAMES[CAN_OUT_01] = (CANBusTransmiterTypedef){
    .label = "oCAN1",
    .timeout_ms = 1000,
	.frequency_hz = 1,
    .frame = {
      .frame.CANBus = CAN_B,
      .frame.idType = CAN_Standard,
      .frame.id = 0x35,
      .frame.dataLengthCode = 8,
//      .frame.data = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}
    }
  };
}


