/*
 * API_Delay.c
 *
 *  Created on: Oct 16, 2024
 *      Author: tomas
 */

#include "main.h"
#include "API_Delay.h"

void delayInit(delay_t *delay, tick_t duration){
	delay->startTime=HAL_GetTick();
	delay->duration=duration;				//valor que tomara al definir el tiempo de espera
	delay->running=false;
}
bool_t delayRead(delay_t *delay){
	if(delay->running==false){
		delay->startTime=HAL_GetTick();
		delay->running=true;
		return false;
	}
	if((HAL_GetTick()-delay->startTime)>=delay->duration){
		delay->running=false;
		return true;
	}
	return false;
}
void delayWrite(delay_t *delay, tick_t duration){			//Permite cambiar el tiempo de duracion de un delay existente
	delay->duration=duration;
}

