/*
 * opdm_output_cfg.h
 *
 *  Created on: Mar 30, 2023
 *      Author: breno
 */

#ifndef __OPDM_OUTPUT_CFG_H_
#define __OPDM_OUTPUT_CFG_H_

#define TRUE 1
#define FALSE 0

//----------------- OUTPUT CONFIGURATION -----------------

// Global limits apply to all outputs. If a specific output has a greater limit than the global one, the global one will be used.
#define HC_GLOBAL_MAX_CURRENT 20.0
#define LC_GLOBAL_MAX_CURRENT 10.0
#define GLOBAL_MAX_VOLTAGE 15.5
#define GLOBAL_MIN_VOLTAGE 9.0
#define GLOBAL_INRUSH_TIME_LIMIT 2000
#define GLOBAL_TOTAL_CURRENT_LIMIT 50.0

#define MAX_OUTPUT_LABEL_SIZE 4

#define HC0_EN TRUE
#define HC0_LABEL "HC0"
#define HC0_RESET_ENABLE FALSE
#define HC0_RESET_RETRY_COUNT 3
#define HC0_RESET_RETRY_DELAY 2000
#define HC0_CURRENT_SETPOINT 5.0
#define HC0_INRUSH_TIME_LIMIT 1000
#define HC0_MAX_VOLTAGE 15.5
#define HC0_MIN_VOLTAGE 9.0
#define HC0_MAX_CURRENT 10.0

#define HC1_EN TRUE
#define HC1_LABEL "HC1"
#define HC1_RESET_ENABLE FALSE
#define HC1_RESET_RETRY_COUNT 3
#define HC1_RESET_RETRY_DELAY 2000
#define HC1_CURRENT_SETPOINT 5.0
#define HC1_INRUSH_TIME_LIMIT 1000
#define HC1_MAX_VOLTAGE 15.5
#define HC1_MIN_VOLTAGE 9.0
#define HC1_MAX_CURRENT 10.0

#define HC2_EN TRUE
#define HC2_LABEL "HC2"
#define HC2_RESET_ENABLE FALSE
#define HC2_RESET_RETRY_COUNT 3
#define HC2_RESET_RETRY_DELAY 2000
#define HC2_CURRENT_SETPOINT 5.0
#define HC2_INRUSH_TIME_LIMIT 1000
#define HC2_MAX_VOLTAGE 15.5
#define HC2_MIN_VOLTAGE 9.0
#define HC2_MAX_CURRENT 10.0

#define HC3_EN TRUE
#define HC3_LABEL "HC3"
#define HC3_RESET_ENABLE FALSE
#define HC3_RESET_RETRY_COUNT 3
#define HC3_RESET_RETRY_DELAY 2000
#define HC3_CURRENT_SETPOINT 5.0
#define HC3_INRUSH_TIME_LIMIT 1000
#define HC3_MAX_VOLTAGE 15.5
#define HC3_MIN_VOLTAGE 9.0
#define HC3_MAX_CURRENT 10.0

#define LC0_EN TRUE
#define LC0_LABEL "LC0"
#define LC0_RESET_ENABLE FALSE
#define LC0_RESET_RETRY_COUNT 3
#define LC0_RESET_RETRY_DELAY 2000
#define LC0_CURRENT_SETPOINT 5.0
#define LC0_INRUSH_TIME_LIMIT 1000
#define LC0_MAX_VOLTAGE 15.5
#define LC0_MIN_VOLTAGE 9.0
#define LC0_MAX_CURRENT 10.0

#define LC1_EN TRUE
#define LC1_LABEL "LC1"
#define LC1_RESET_ENABLE FALSE
#define LC1_RESET_RETRY_COUNT 3
#define LC1_RESET_RETRY_DELAY 2000
#define LC1_CURRENT_SETPOINT 5.0
#define LC1_INRUSH_TIME_LIMIT 1000
#define LC1_MAX_VOLTAGE 15.5
#define LC1_MIN_VOLTAGE 9.0
#define LC1_MAX_CURRENT 10.0

#define LC2_EN TRUE
#define LC2_LABEL "LC2"
#define LC2_RESET_ENABLE FALSE
#define LC2_RESET_RETRY_COUNT 3
#define LC2_RESET_RETRY_DELAY 2000
#define LC2_CURRENT_SETPOINT 5.0
#define LC2_INRUSH_TIME_LIMIT 1000
#define LC2_MAX_VOLTAGE 15.5
#define LC2_MIN_VOLTAGE 9.0
#define LC2_MAX_CURRENT 10.0

#define LC3_EN TRUE
#define LC3_LABEL "LC3"
#define LC3_RESET_ENABLE FALSE
#define LC3_RESET_RETRY_COUNT 3
#define LC3_RESET_RETRY_DELAY 2000
#define LC3_CURRENT_SETPOINT 5.0
#define LC3_INRUSH_TIME_LIMIT 1000
#define LC3_MAX_VOLTAGE 15.5
#define LC3_MIN_VOLTAGE 9.0
#define LC3_MAX_CURRENT 10.0


typedef char (*condition_t)(void);

char HC0_OUTPUT_CONDITION(void);
char HC1_OUTPUT_CONDITION(void);
char HC2_OUTPUT_CONDITION(void);
char HC3_OUTPUT_CONDITION(void);

char LC0_OUTPUT_CONDITION(void);
char LC1_OUTPUT_CONDITION(void);
char LC2_OUTPUT_CONDITION(void);
char LC3_OUTPUT_CONDITION(void);











#endif /* __OPDM_OUTPUT_CFG_H_ */
