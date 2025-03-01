/***********************************************************************************************************************
 * API_BT.h
 *
 *  Created on: -
 *      Author: GRUPO_8_TDII_2024
 *
 *  Libreria para el manejo de modulo bluetooth HC-05 utilizando USART2, configurado a los pines PD6 (RX) y PD5 (TX)
 ************************************************************************************************************************/
/*Includes*/
#include "main.h"
#include <stdint.h>
#include <stdbool.h>


#ifndef API_INC_API_BT_H_
#define API_INC_API_BT_H_

typedef uint8_t msj_t;												//variable para los mensajes a enviar o recibir

void BT_TX(const msj_t *Mx_TX); 									//Transmitir un mensaje
void BT_RX(msj_t *Mx_RX);											//Recibir un mensaje
void BT_TX_IT(const msj_t *Mx_TX);									//Transmitir utilizando interrupciones
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void MX_USART2_UART_Init(void);
void BT_SendMessage(char *message);
char BT_ReceiveMessage();
void BT_Test();
void BT_Test_2();
#endif /* API_INC_API_BT_H_ */
