/*
 * API_Teclado4x3.h
 *
 *  Created on: Feb 1, 2025
 *      Author: EMILIO
 *      Libreria para manejo de teclado matricial adaptable
 */

#ifndef API_INC_API_TECLADO4X3_H_
#define API_INC_API_TECLADO4X3_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "API_Delay.h"

#define ROWS 4
#define COLS 3

// Definición de pines para las columnas del teclado
#define C1_PIN GPIO_PIN_2
#define C2_PIN GPIO_PIN_4
#define C3_PIN GPIO_PIN_5
#define C_PORT GPIOE  // Puerto donde están conectadas las columnas

// Prototipos de funciones
void keypad_init(void);         // Inicializa el teclado matricial
char keypad_get_key(void);      // Obtiene la última tecla presionada
bool keypad_key_pressed(void);	// Verifica si hay una tecla presionada

void scan_keypad(void); 		// Se expone scan_keypad() para ser usada en API_GPIO.c
extern delay_t debounce_delay;	// Se expone debounce_delay para ser usado en API_GPIO.c


#endif /* API_INC_API_TECLADO4X3_H_ */
