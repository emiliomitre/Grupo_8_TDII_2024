/*
 * API_Debounce.c
 *
 *  Created on: Nov 30, 2024
 *      Author: Emilio Javier
 */

#include "main.h"
#include "API_Debounce.h"

/*Includes -------------------------------------------------------------------*/
#include "main.h"
#include "API_Debounce.h"
#include "API_Delay.h"

/*Defines --------------------------------------------------------------------*/
#define DEBOUNCE_DELAY 40

/*Declaracion de variables */
static debounceState_t actualState;
static bool_t keyPressed = false;
static bool_t fallingEdge = false;
delay_t debounceDelay;
bool buttonRead = true;

/*Define functions -----------------------------------------------------------*/
bool_t readKey(void)	//Devuelve true si la tecla fue presionada
{
	bool_t keyPress = false;
	fallingEdge = false;

	if(keyPressed){
		keyPress = true;
		keyPressed = false; 	//Limpio estado de la variable para evitar lecturas repetidas
	}
	return keyPress;	// Retorna True solo una vez por evento de flanco
}

void debounceFSM_init(void)		// debe cargar el estado inicial
{
	actualState = BUTTON_UP;
	delayInit(&debounceDelay, DEBOUNCE_DELAY);
	//Actualizar salida del estado inicial Leds off
	HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
	buttonRead = true; //USER_Btn_Pin no activado
}

void debounceFSM_update(bool buttonRead){
	switch (actualState){
	case BUTTON_UP: 											//estado inicial 0
																//Actualizar salida del estado LEDs off
																//HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
																//Chequear condicion de transición
		if(buttonRead == true){ 								//se presionó USER_Btn_Pin
			actualState = BUTTON_FALLING; 						//pasa al estado siguiente
			delayRead(&debounceDelay);   						//arranca cuenta de DEBOUNCE_DELAY
		}
	break;

	case BUTTON_FALLING:
		//Chequea si paso el tiempo de 40 ms
		if(delayRead(&debounceDelay))
		{
			//Chequear condicion de transición
			if(buttonRead == true) //se presionó USER_Btn_Pin
			{
				//buttonPressed(); //Dispara funcion buttonPresed()
				keyPressed = true; //Indica tecla presionada luego de 2 lecturas en 40 ms
				fallingEdge = true; //asume que en este estado hubo un flanco decreciente
				actualState = BUTTON_DOWN; //pasa al estado siguiente
			}
			else
			{
				actualState = BUTTON_UP; // regresa al estado anterior
			}
		}
	break;

	case BUTTON_DOWN:
		//Chequear condicion de transición
		if(buttonRead == false) //se presionó USER_Btn_Pin
		{
			actualState = BUTTON_RISING; //pasa al estado siguiente
			delayRead(&debounceDelay);   //arranca cuenta de DEBOUNCE_DELAY
		}
	break;

	case BUTTON_RISING:
		//Chequea si paso el tiempo de 40 ms
		if(delayRead(&debounceDelay))
		{
			//Chequear condicion de transición
			if(buttonRead == false) //se USER_Btn_Pin regresó a estado inactivo
			{
				//buttonReleased(); //Dispara funcion buttonRelaased()
				keyPressed = false; //Indica tecla presionada luego de 2 lecturas en 40 ms
				actualState = BUTTON_UP; //pasa al estado siguiente, el inicial
			}
			else
			{
				actualState = BUTTON_DOWN; // regresa al estado anterior
			}
		}
	break;

	default:
		Error_Handler();
	break;
	}
}

/*void buttonPressed(void){
	HAL_GPIO_TogglePin(GPIOB, LD1_Pin); //Toggle LD1
}

void buttonReleased(void){
	HAL_GPIO_TogglePin(GPIOB, LD3_Pin); //Toggle LD3;
}*/
