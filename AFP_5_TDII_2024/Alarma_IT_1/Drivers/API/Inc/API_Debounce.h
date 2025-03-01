/*
 * API_Debounce.h
 *
 *  Created on: Nov 30, 2024
 *      Author: GRUPO_8_TDII_2024
 */

#include <stdbool.h>
#include <stdint.h>
#include "API_Delay.h"

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

extern delay_t debounceDelay;
typedef enum{
	BUTTON_UP=0,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
}debounceState_t;

bool readKey(void);
void debounceFSM_init();
void debounceFSM_update(bool buttonRead);


#endif /* API_INC_API_DEBOUNCE_H_ */
