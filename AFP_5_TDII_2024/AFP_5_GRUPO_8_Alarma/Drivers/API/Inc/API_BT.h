/*
 * API_BT.h
 *
 *  Created on: Jan 31, 2025
 *      Author: Tomas Jorrat
 *
 *  Libreria para el manejo de modulo bluetooth HC-05 utilizando USART2, configurado a los pines PD6 (RX) y PD5 (TX)
 */

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

#ifndef API_INC_API_BT_H_
#define API_INC_API_BT_H_

typedef uint8_t msj_t;												//variable para los mensajes a enviar o recibir

void MX_USART2_UART_Init(void);										//Incializacion USART2

char BT_ReceiveMessage();											//Recibir un mensaje
void BT_SendMessage(char *message);									//Enviar una cadena de caracteres
void BT_Test();														//Mensaje de prueba

void BT_TX(const msj_t *Mx_TX); 									//Transmitir un mensaje
void BT_RX(msj_t *Mx_RX);											//Recibir un mensaje
void BT_TX_IT(const msj_t *Mx_TX);									//Transmitir utilizando interrupciones
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);


#endif /* API_INC_API_BT_H_ */
