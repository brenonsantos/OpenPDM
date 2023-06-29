/*
 * usb_component.c
 *
 *  Created on: Jun 13, 2023
 *      Author: breno
 */

#include "usb_component.h"
#if USE_USB_OVER_CANB

#include "usbd_cdc_if.h"
#include "string.h"

#define MAX_STRING_SIZE 200
#define MAX_USB_BUFFER_SIZE 1024

char data[MAX_STRING_SIZE];
uint8_t usbConnected = FALSE;

void USB_TransmitOutputsStatus (void);
void USB_TransmitInputStatus (void);
void USB_Println (const char *str);
uint8_t USB_CheckConnection (void);
void USB_TransmitCANMessages(void);
#endif

void USB_TransmitPDMStatus (void) {
#if USE_USB_OVER_CANB
  if (USB_DEVICE_isUSBConnected()) {
	uint32_t send_period = 100;
	static uint32_t previousTick = 0;
	uint32_t currentTick = HAL_GetTick();

	if ((currentTick - previousTick) >= send_period) {
	  previousTick = currentTick;
	  if (!USB_CheckConnection()) {
		return;
	  }
//	  USB_TransmitOutputsStatus();
//	  USB_TransmitInputStatus();
	  USB_TransmitCANMessages();
	}
  }
#endif /* USE_USB_OVER_CANB */
}

#if USE_USB_OVER_CANB
void USB_TransmitOutputsStatus (void) {
  char buffer[MAX_STRING_SIZE];
  const char o_header[MAX_STRING_SIZE] =
	  "LABEL;ENABLE;OUTPUT STATE;POWER STATE;CURRENT LIMIT;CURRENT READING;"
		  "PEAK CURRENT;RETRY ATTEMPTS;RETRY ATTEMPTS MADE;TICK";

  uint32_t tick = HAL_GetTick();
  USB_Println(o_header);
  for (CurrentOutputsTypedef output = HC0; output <= HC3; output++) {
	snprintf(buffer, MAX_STRING_SIZE, "%s;%d;%d;%d;%.4f;%.4f;%.4f;%d;%d;%lu",
			 CURRENT_OUTPUT_SETUP[output].label,
			 CURRENT_OUTPUT_SETUP[output].enable,
			 CURRENT_OUTPUT_CONTROL[output].output_state,
			 CURRENT_OUTPUT_CONTROL[output].power_state,
			 (float) CURRENT_OUTPUT_SETUP[output].current_limit / 186.18f,
			 (float) CURRENT_OUTPUT_CONTROL[output].current_reading / 186.18f,
			 (float) CURRENT_OUTPUT_CONTROL[output].peak_current / 186.18f,
			 CURRENT_OUTPUT_SETUP[output].reset_retry_attempts,
			 CURRENT_OUTPUT_CONTROL[output].retry_attempts, tick);
	USB_Println(buffer);
  }
  for (CurrentOutputsTypedef output = LC0; output < NUM_OF_OUTPUTS; output++) {
	snprintf(buffer, MAX_STRING_SIZE, "%s;%d;%d;%d;%.3f;%.3f;%.3f;%d;%d;%lu",
			 CURRENT_OUTPUT_SETUP[output].label,
			 CURRENT_OUTPUT_SETUP[output].enable,
			 CURRENT_OUTPUT_CONTROL[output].output_state,
			 CURRENT_OUTPUT_CONTROL[output].power_state,
			 (float) CURRENT_OUTPUT_SETUP[output].current_limit / 372.36f,
			 (float) CURRENT_OUTPUT_CONTROL[output].current_reading / 372.36f,
			 (float) CURRENT_OUTPUT_CONTROL[output].peak_current / 372.36f,
			 CURRENT_OUTPUT_SETUP[output].reset_retry_attempts,
			 CURRENT_OUTPUT_CONTROL[output].retry_attempts, tick);
	USB_Println(buffer);
  }

  tick = HAL_GetTick();
}

void USB_TransmitInputStatus (void) {
  char buffer[MAX_STRING_SIZE];
  const char in_header[MAX_STRING_SIZE] = "LABEL;ENABLE;VALUE;TICK";

  uint32_t tick = HAL_GetTick();
  USB_Println(in_header);
  // adc_reading = vin * voltage_divider_ratio * adc_bits / adc_reference_voltage = 269.83
  for (AnalogDigitalInputType input = 0; input < NUM_OF_AD_INPUTS; input++) {
	snprintf(buffer, MAX_STRING_SIZE, "%s;%d;%.2f;%lu",
			 ANALOG_DIGITAL_INPUT[input].label,
			 ANALOG_DIGITAL_INPUT[input].enable,
			 (float) ANALOG_DIGITAL_INPUT[input].value / 269.83f,
			 tick);
	USB_Println(buffer);
  }
  tick = HAL_GetTick();
}

void USB_TransmitCANMessages(void){
  char buffer[MAX_STRING_SIZE];

  for (CanBusReceiverType receiver = 0; receiver < NUM_OF_CAN_RECEIVERS; receiver++){
	if (CANBUS_RECEIVER_FRAMES[receiver].status == CAN_MSG_RECEIVED){
	  CANBUS_RECEIVER_FRAMES[receiver].status = CAN_MSG_NOT_RECEIVED;
	  snprintf(buffer, MAX_STRING_SIZE, "Msg_Label: %s", CANBUS_RECEIVER_FRAMES[receiver].label);
	  USB_Println(buffer);
	  snprintf(buffer, MAX_STRING_SIZE, "id: %d", CANBUS_RECEIVER_FRAMES[receiver].frame.frame.id);
	  USB_Println(buffer);
	  for (uint8_t i = 0; i < 8; i++){
		snprintf(buffer, MAX_STRING_SIZE, "data[%d] = %c", i, (char)CANBUS_RECEIVER_FRAMES[receiver].frame.frame.data[i]);
		USB_Println(buffer);
	  }
	}
  }
}

void USB_Println (const char *str) {
  int strLength = strlen(str);
  int offset = 0;

  while (offset < strLength) {
	char buffer[MAX_USB_BUFFER_SIZE];
	int remainingLength = strLength - offset;
	int length = remainingLength > MAX_USB_BUFFER_SIZE - 2 ?
	MAX_USB_BUFFER_SIZE - 2 : remainingLength;

	strncpy(buffer, str + offset, length);
	buffer[length] = '\r';
	buffer[length + 1] = '\n';

	if (USB_CheckConnection()) {
	  while (CDC_Transmit_FS((uint8_t*) buffer, length + 2) == USBD_BUSY);
	}
	offset += length;
  }
}

void USB_Print (const char *str) {
  int strLength = strlen(str);
  int offset = 0;

  while (offset < strLength) {
	char buffer[MAX_USB_BUFFER_SIZE];
	int remainingLength = strLength - offset;
	int length = remainingLength > MAX_USB_BUFFER_SIZE ?
	MAX_USB_BUFFER_SIZE : remainingLength;

	strncpy(buffer, str + offset, length);
	if (USB_CheckConnection()) {
	  while (CDC_Transmit_FS((uint8_t*) buffer, length) == USBD_BUSY)
		;
	}
	offset += length;
  }
}

uint8_t USB_CheckConnection (void) {
  uint8_t *nullByte = "";
  uint8_t counter = 0;
  while (CDC_Transmit_FS(nullByte, strlen(nullByte)) == USBD_BUSY) {
	if (counter == 10) {
	  PDMHAL_ToggleStatusLed(LED_Internal);
	  return FALSE;
	}
	counter++;
  }
  return TRUE;
}


#endif

