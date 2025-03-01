/*****************************************************************************************************************
 * API_Teclado4x3.c
 *
 *  Created on: -
 *      Author: GRUPO_8_TDII_2024
 ******************************************************************************************************************/
/* API_Keypad.c */
#include "main.h"
#include "API_Keypad.h"
#include "API_Delay.h"
#include "API_Debounce.h"
#include <stdbool.h>


static GPIO_TypeDef *rowPorts[ROWS] = {R1_GPIO_Port, R2_GPIO_Port, R3_GPIO_Port, R4_GPIO_Port};
static uint16_t rowPins[ROWS] = {R1_Pin, R2_Pin, R3_Pin, R4_Pin};

static GPIO_TypeDef *colPorts[COLS] = {C1_GPIO_Port, C2_GPIO_Port, C3_GPIO_Port};
static uint16_t colPins[COLS] = {C1_Pin, C2_Pin, C3_Pin};

// Mapeo de teclas del teclado 4x3
static char keymap[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
delay_t debounceDelay1;
volatile uint16_t columnPressed = 0;
/**
 * @brief Función que escanea la fila para detectar la tecla presionada
 * @param columnPressed - Columna que generó la interrupción
 * @retval Carácter de la tecla presionada o '\0' si no se detectó ninguna
 */
char keypad_scan(uint16_t columnPressed) {
    if (columnPressed == 0) return '\0';  // No hay interrupción pendiente

    for (int i = 0; i < ROWS; i++) {
        // Activar solo la fila actual
        HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_SET);

        // Pequeña espera para asegurar estabilidad
        delayInit(&debounceDelay1, 5);
        delayRead(&debounceDelay1);

        // Verificar si la columna sigue en bajo
        for (int j = 0; j < COLS; j++) {
            if (columnPressed == colPins[j] && HAL_GPIO_ReadPin(colPorts[j], colPins[j]) == GPIO_PIN_SET) {
                // Aplicar debounce
                debounceFSM_update(true);
                if (readKey()) {  // Si el debounce confirma la pulsación
                    HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_RESET); // Restaurar la fila
                    keypad_resetColumn();
                    return keymap[i][j];  // Retornar la tecla presionada
                }
            }
        }
        HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_RESET); // Restaurar la fila
    }

    return '\0';  // No se detectó tecla válida
}
/**
 * @brief Función para resetear la columna una vez que se procesó la tecla
 */
void keypad_resetColumn(){
    columnPressed = 0;
}























/*char keypad_getkey() {
    for (int i = 0; i < ROWS; i++) {
        // Poner todas las filas en alto excepto la actual
        for (int k = 0; k < ROWS; k++) {
            HAL_GPIO_WritePin(rowPorts[k], rowPins[k], (i == k) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        }

        // Leer columnas
        for (int j = 0; j < COLS; j++) {
            if (HAL_GPIO_ReadPin(colPorts[j], colPins[j]) == GPIO_PIN_RESET) {
                HAL_Delay(50); // Anti-rebote
                while (HAL_GPIO_ReadPin(colPorts[j], colPins[j]) == GPIO_PIN_RESET);
                return keymap[i][j];
            }
        }
    }
    return '\0'; // No se presionó ninguna tecla
}*/
