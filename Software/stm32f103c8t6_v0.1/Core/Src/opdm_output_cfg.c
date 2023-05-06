/*
 * opdm_output_cfg.c
 *
 *  Created on: 31 de mar de 2023
 *      Author: breno
 */

#include "opdm_cfg.h"

/* TODO: this is a temporary solution. Probably it shouldn't receive void, but the CAN messages and the inputs readings.

char OUTPUT_CONDITION(condition_t condition_function, can_msgs, inputs){
    return condition_function(can_msgs, inputs);
}
*/

char OUTPUT_CONDITION(condition_t condition_function){
    return condition_function();
}

char HC0_OUTPUT_CONDITION(void){
    return TRUE;
}

char HC1_OUTPUT_CONDITION(void){
    return TRUE;
}

char HC2_OUTPUT_CONDITION(void){
    return TRUE;
}

char HC3_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC0_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC1_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC2_OUTPUT_CONDITION(void){
    return TRUE;
}

char LC3_OUTPUT_CONDITION(void){
    return TRUE;
}



/* example 
typedef uint8_t (*t_somefunc)(int);

uint8_t product(int u) {
  return u*2;
}



int main(){
    t_somefunc afunc = &product;
    uint8_t x2 = (*afunc)(3);
    printf("%d", x2);

    return 0;
}
*/

/* example 2
#include <stdio.h>
typedef char (*condition_t)(void);
void print_results(void);

char output_condition(condition_t condition_function){
    return condition_function();
}

char hc0_output_condition(void) {
    return 1;
}

char hc1_output_condition(void){
    return 0;
}

char result[2];

int main(){
    condition_t func[2] = {hc0_output_condition, hc1_output_condition};
    for(int i = 0; i < 2; i++){
        result[i] = output_condition(func[i]);
    }
    
    print_results();
    
    return 0;
}

void print_results(void){
    printf("%d", result[0]);
    printf("%d", result[1]);
}
*/
