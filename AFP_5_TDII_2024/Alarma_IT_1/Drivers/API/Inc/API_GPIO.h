/*************************************************************************************************************************
 * API_GPIO.c
 *
 *  Created on: -
 *      Author: GRUPO_8_TDII_2024
 *************************************************************************************************************************/
#ifndef API_GPIO_H
#define API_GPIO_H

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>


typedef uint16_t led_t;
typedef bool buttonStatus_t;

buttonStatus_t readButton_GPIO(void);
void writeLedOn_GPIO(led_t LDx);
void writeLedOff_GPIO(led_t LDx);
void toggleLed_GPIO(led_t LDx);
void SystemClock_Config(void);
void MX_GPIO_Init(void);

// Inicializa un pin GPIO
void GPIO_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed);

// Escribe en un pin GPIO
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

// Lee el estado de un pin GPIO
GPIO_PinState GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif /* API_GPIO_H */
