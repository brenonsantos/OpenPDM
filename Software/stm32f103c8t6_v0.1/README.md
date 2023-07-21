# Firmware

The firmware for OpenPDM was developed using STM32CubeIDE, and it relies on the STM32 HAL libraries.

## Configuration
To tailor OpenPDM to your specific needs, you can modify the parameters of the power outputs in the following files:

1.  `/Core/Src/pdm_cfg.c`
2.  `/Core/Inc/opdm_cfg.h`

## Current Output
Below is a code example of how to configure an output:
```C
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
```

`CURRENT_OUTPUT_SETUP` is an array that stores the parameters for each output. The array's positioning is as follows: [HC0, HC1, HC2, HC3, LC0, LC1, LC2, LC3], where HCs represent High Current outputs, and LCs represent Low Current outputs.

The parameters you can modify are:

-   `enable` [TRUE, FALSE]: Enable or disable the current output. If disabled, the output won't turn on regardless of other conditions.
-   `label` [any String]: Assign a name to the output for easy identification, especially useful for user interfaces and dataloggers.
-   `reset_enable` [TRUE, FALSE]: Define whether the output is resettable or not.
-   `reset_retry_attempts` [0 to 255]: If reset is enabled, set the number of times the output will attempt to self-reset.
-   `reset_retry_delay_seconds` [0 to 255]: Set the time delay in seconds between each reset retry.
-   `current_limit` [0 to 4095]: Define the desired current limit for this output, similar to choosing a fuse. The `HC_CURRENT_CONVERSION_TO_12BITS` or `LC_CURRENT_CONVERSION_TO_12BITS` functions convert real amperage to a 12-bit value, avoiding the need for conversion with every ADC reading.
-   `inrush_time_limit_miliseconds` [32-bit unsigned]: Set the time limit for detecting inrush current. If the output current exceeds the `current_limit` momentarily, it won't be flagged as a fault if the duration of this signal is lower than the defined time limit.
-   `max_voltage` [0 to 4095]: Define the maximum voltage that should be read when the output is ON. These values depend on the PCB and components used. For PCB version 0.1, components should work within 6.5 to 15 Volts. You can set a rule stricter than this if necessary. Similar to current readings, use the `VOLTAGE_CONVERSION_TO_12BITS` function for the conversion.
-   `min_voltage` [0 to 4095]: Define the minimum voltage expected on the output. Refer to the `max_voltage` for reference.
-   `max_current` [0 to 4095]: Define the maximum current supported by the PCB and components. This redundancy ensures users won't exceed the maximum current supported.
- `condition_callback` [pointer to function]: Define a function where the condition to turn on or off the output is defined. You have the freedom to use any global variable and create any logic you desire here.

The `condition_callback` function determines when an output should be turned on or off based on specific conditions. Here's an example:
```C
uint8_t HC0_OUTPUT_CONDITION(void){
	if (ANALOG_DIGITAL_INPUT[INPUT_00].value > VOLTAGE_CONVERSION_TO_12BITS(5.0))
		return TRUE;
	else if (CANBUS_RECEIVER_FRAMES[CAN_IN_00].frame.frame.data[0] > 127) {
		return TRUE;
	}
	return FALSE;
}
```

In this example, the `HC0_OUTPUT_CONDITION` function determines whether the HC0 output should be turned on based on two conditions:
1.  If a voltage greater than 5 volts is detected on `INPUT00`, the output will be activated.
2.  If the first byte of the CAN message `CAN_IN_00` received is greater than 127, the output will also be activated.
Use various global variables within the `condition_callback` function to create custom conditions, such as:

- `ANALOG_DIGITAL_INPUT[NUM_OF_INPUTS]`
-  `CURRENT_OUTPUT_SETUP[NUM_OF_OUTPUTS]`
 - `CURRENT_OUTPUT_CONTROL[NUM_OF_OUTPUTS]`
 - `CANBUS_RECEIVER_FRAMES[NUM_OF_CAN_RECEIVERS]`
 - `CANBUS_TRANSMITER_FRAMES[NUM_OF_CAN_TRANSMITERS]`

## Generic Input
There isn't much to configure for the inputs. Below is a code example of how to configure a generic input:
```C
InputConfigTypedef ANALOG_DIGITAL_INPUT[] ={
		[INPUT_00] = {
				.enable = TRUE,
				.label = "IN0",
				.input_type = DIGITAL_ACTIVE_H,
                .value = 0,
		},
```

The parameters you can modify for each generic input are:

-   `enable` [TRUE, FALSE]: Enable or disable the generic input. Disabling it will prevent the PDM from reading voltage on this pin.
-   `label` [any String]: Assign a name to the input for easy identification, especially useful for user interfaces and dataloggers.
-   `input_type` [DIGITAL_ACTIVE_H, DIGITAL_ACTIVE_L, LINEAR_ANALOG, CALIBRATED_ANALOG, ROTARY_SWITCH]: Define the type of input. For now, the input functioning remains the same regardless of this value, as every input is considered a linear analog reading.
-   `value` [0 to 4095]: Set the initial value of the reading. Use `VOLTAGE_CONVERSION_TO_12BITS` to ensure proper voltage conversion.

## CAN Transmitter 
Configuring CAN transmitters allows you to communicate and transmit data on the CAN bus. Here's an example of how to configure a CAN transmitter:
```C
void CONFIG_CAN_TRANSMITTER(void){
  CANBUS_TRANSMITER_FRAMES[CAN_OUT_00] = (CANBusTransmiterTypedef){
    .label = "oCAN0",
    .timeout_ms = 1000,
	.frequency_hz = 0.1,
	.callback = CAN0_OUTPUT_CALLBACK,
    .frame = {
      .frame.CANBus = CAN_C,
      .frame.idType = CAN_Standard,
      .frame.id = 0x40,
      .frame.dataLengthCode = 8,
      .frame.data = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48} // OPTIONAL
    }
  };
  ```
Parameters you can modify for each CAN transmitter are:

-   `label` [any String]: Assign a name to the transmitter for easy identification and usage.
-   `timeout_ms` [32-bits unsigned]: Set the timeout value in milliseconds. This determines how long the transmitter will attempt to send the message before giving up. For now, it isn't implemented.
-   `frequency_hz` [float]: Define the transmission frequency in hertz (Hz). This sets how often the message will be transmitted.
-   `callback` [pointer to function]: Specify the function that will be called when a transmission will be send. The message is generated here.
-   `frame`: Configure the CAN message frame with the following parameters:
    -   `frame.CANBus` [CAN_C, CAN_B]: Choose the CAN bus to transmit the message.
    -   `frame.idType`[CAN_Standard, CAN_Extended]: Define the ID type of the message.
    -   `frame.id`: Set the ID of the message. (This is the message identifier used for filtering on the receiving end.)
    -   `frame.dataLengthCode` [0 to 8]: Determine the length of the data in bytes.
    -   `frame.data` [array of maximum 8x1bytes]: Optionally, provide the default data to be transmitted. The data array must match the specified `dataLengthCode`. Note that this should change on the callback.

Here's an example of a CAN transmitter callback function:
```C
uint8_t CAN0_OUTPUT_CALLBACK(PDMHAL_CAN_MessageFrame* frame){
  static uint16_t counter = 0;
  uint16_t values[4] = {(uint16_t)ANALOG_DIGITAL_INPUT[INPUT_00].value,
	  0xAA55,
	  (uint16_t)ANALOG_DIGITAL_INPUT[INPUT_02].value,
	  counter++
  };
  uint8_t dataLength = 8;
  CAN_OUTPUT_Transmit_16bits(frame, values, dataLength);
  return TRUE;
}
```
in this example, the `CAN0_OUTPUT_CALLBACK` function is triggered before sending a message. Within this function:
-   A static `counter` variable is used to keep track of the number of times the callback is invoked.
-   An array `values` is populated with four 16-bit values. In this case:
    -   The first value is taken from `ANALOG_DIGITAL_INPUT[INPUT_00].value`, which is the reading from `INPUT_00`.
    -   The second value is set to `0xAA55`.
    -   The third value is taken from `ANALOG_DIGITAL_INPUT[INPUT_02].value`, which is the reading from `INPUT_02`.
    -   The fourth value is the current value of the `counter` variable, which is incremented each time the callback is called.
-   The `dataLength` variable is set to 8, indicating the length of the data array `values`.
-   The `CAN_OUTPUT_Transmit_16bits` function is called to transmit the data using the provided `frame`.
-   The function returns `TRUE`, indicating a successful callback execution.

Note: I personally didn't like the way this was implemented. I believe the transmission shouldn't be done here, and this function should return the data frame. There must be a easier way to send 16-bit data, allowing to mix data of different sizes.

## CAN Receiver
Configuring CAN receivers allows your OpenPDM to receive data on the CAN bus. Below is an example of how to configure a CAN receiver:
Parameters you can modify for each CAN receiver are:

-   `label` [any String]: Assign a name to the receiver for easy identification and usage.
-   `status` [CAN_MSG_NOT_RECEIVED, CAN_MSG_RECEIVED]: This parameter indicates whether the receiver has received a CAN message or not. Set it as per your application needs.
-   `size` [CAN_MSG_SIZE_1FRAME, CAN_MSG_SIZE_2FRAMES, CAN_MSG_SIZE_4FRAMES]: Determine the size of the CAN message frame (single frame or multi-frame). For now, it isn't implemented.
-  `timeout_ms` [32-bit unsigned]: Set the timeout value in milliseconds. This defines how long the receiver will wait for a CAN message before timing out. For now, it isn't implemented.
-   `frame`: Configure the CAN message frame with the following parameters:
    -   `frame.CANBus`[CAN_B, CAN_C]: Choose the CAN bus to receive the message.
    -   `frame.idType`[CAN_Standard, CAN_Extended]: Define the ID type of the expected message.
    -   `frame.id`: Set the ID of the expected message. The receiver will only process messages with this ID.
    - `frame.data` [array of maximum 8x1bytes]: Default value if a timeout is detected. For now it isn't implemented.
