/*************************************************************************************************************************
 * API_Keypad.h
 *
 *  Created on: -
 *      Author: GRUPO_8_TDII_2024
 *************************************************************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_
/* Includes */
#include "stm32f4xx_hal.h"

// Prototipos de funciones públicas
//char keypad_getkey();
char keypad_scan(uint16_t columnPressed);
void keypad_resetColumn();
extern volatile uint16_t columnPressed;  // Columna detectada en la interrupción

// Definición de pines del teclado
#define ROWS 4
#define COLS 3

#endif /* KEYPAD_H_ */
