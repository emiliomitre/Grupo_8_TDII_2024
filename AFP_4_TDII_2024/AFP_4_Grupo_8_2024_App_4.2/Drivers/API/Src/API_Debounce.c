/*
 * API_Debounce.c
 *
 *  Created on: Nov 30, 2024
 *      Author: Emilio Javier
 */

/*Includes -------------------------------------------------------------------*/
#include "main.h"
#include "API_Debounce.h"
#include "API_Delay.h"
#include "API_GPIO.h"

/*Defines --------------------------------------------------------------------*/
#define DEBOUNCE_DELAY 40															// Tiempo necesario para considerar como valido la pulsacion del boton

/*Declaracion de variables */
static debounceState_t actualState;													// Representa el estado del boton (BUTTON_UP,BUTTON_FALLING, BUTTON_DOWN, BUTTON_RISING)
static bool_t keyPressed = false;													// fue presionado el boton? Inicializacion en falso
static bool_t flanco_descendente = false;											// Hubo flanco descendente? Inicializacion en falso
bool_t buttonRead;
delay_t debounceDelay;
//bool buttonRead = true;

/*Define functions -----------------------------------------------------------*/
bool_t readKey(void){																// Devuelve true si la tecla fue presionada
	bool_t keyPress = false;
	flanco_descendente = false;														// Re- inicializacion de la variable
	if(keyPressed){
		keyPress = true;
		keyPressed = false; 														// Limpio estado de la variable para evitar lecturas repetidas
	}
	return keyPress;																// Retorna True solo una vez por evento de flanco
}

void debounceFSM_init(void)															// debe cargar el estado inicial
{
	actualState = BUTTON_UP;
	delayInit(&debounceDelay, DEBOUNCE_DELAY);

	//Actualizar salida del estado inicial Leds off
	writeLedOff_GPIO(LD1_Pin|LD3_Pin|LD2_Pin);										// Inicializacion de todos los leds apagados
	buttonRead = true; 																// Boton de usuario no activado
}

void debounceFSM_update(bool buttonRead){
	switch (actualState){
	case BUTTON_UP: 																// Estado inicial 0 | Actualizar salida del estado LEDs off
		if(buttonRead == true){ 													// Chequear condicion de transición | se presionó el boton?
			actualState = BUTTON_FALLING; 											// Pasa al estado siguiente
			delayRead(&debounceDelay);   											// Arranca cuenta de DEBOUNCE_DELAY
		}
	break;

	case BUTTON_FALLING:
		//Chequea si paso el tiempo de 40 ms
		if(delayRead(&debounceDelay)){
			//Chequear condicion de transición
			if(buttonRead == true){													// Se presionó boton de usuario
				buttonPressed();
				keyPressed = true; 													// Indica tecla presionada luego de 2 lecturas en 40 ms
				flanco_descendente = true; 												// Asume que en este estado hubo un flanco decendente
				actualState = BUTTON_DOWN; 											// Pasa al estado siguiente
			}
			else{
				actualState = BUTTON_UP; 											// Regresa al estado anterior
			}
		}
	break;

	case BUTTON_DOWN:
		//Chequear condicion de transición
		if(buttonRead == false){ 													// Se presionó el boton?
			actualState = BUTTON_RISING; 											// Pasa al estado siguiente Deteccion de flanco ascendente
			delayRead(&debounceDelay);   											// Arranca cuenta de DEBOUNCE_DELAY = 40ms
		}
	break;

	case BUTTON_RISING:
		//Chequea si paso el tiempo de 40 ms
		if(delayRead(&debounceDelay)){
			//Chequear condicion de transición
			if(buttonRead == false){												// El boton de usuario regresó a estado inactivo
				buttonReleased();
				keyPressed = false; 												// Indica tecla presionada luego de 2 lecturas en 40 ms
				actualState = BUTTON_UP; 											// Pasa al estado siguiente, el inicial
			}
			else{
				actualState = BUTTON_DOWN; 											// Regresa al estado anterior
			}
		}
	break;

	default:
		Error_Handler();
	break;
	}
}
void buttonPressed(void){
	toggleLed_GPIO(LD1_Pin);
}
void buttonReleased(void){
	toggleLed_GPIO(LD3_Pin);
}
