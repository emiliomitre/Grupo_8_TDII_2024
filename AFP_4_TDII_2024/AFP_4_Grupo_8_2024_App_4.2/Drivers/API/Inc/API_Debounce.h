/*
 * API_Debounce.h
 *
 *  Created on: Nov 30, 2024
 *      Author: Emilio Javier
 */

#include <stdbool.h>
#include <stdint.h>


#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

typedef enum{
	BUTTON_UP=0,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
}debounceState_t;

bool readKey(void);
void debounceFSM_init();
void debounceFSM_update(bool buttonRead);
void buttonPressed();
void buttonReleased();

#endif /* API_INC_API_DEBOUNCE_H_ */
