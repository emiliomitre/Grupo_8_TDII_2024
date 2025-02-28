/*****************************************************************************************************************
 * API_Teclado4x3.c
 *
 *  Adaptado a la estructura del primer código con comentarios explicativos
 *  Created on: Feb 1, 2025
 *      Author: EMILIO
 ******************************************************************************************************************/

#include "API_Teclado4x3.h"
#include "API_Debounce.h"
#include "API_Delay.h"
#include "API_GPIO.h"
#include <string.h>

/******************************************************************************************************************/
#define BUFFER_SIZE 16 // Tamaño del buffer para almacenar teclas presionadas

// Definición de pines para las columnas del teclado
/*#define C1_PIN GPIO_PIN_2
#define C2_PIN GPIO_PIN_4
#define C3_PIN GPIO_PIN_5
#define C_PORT GPIOE*/

// Definición de pines para las filas del teclado
#define R1_PIN GPIO_PIN_6
#define R2_PIN GPIO_PIN_3
#define R3_PIN GPIO_PIN_8
#define R4_PIN GPIO_PIN_7
#define R_PORT GPIOF

#define ROWS 4 // Número de filas del teclado
#define COLS 3 // Número de columnas del teclado

/******************************************************************************************************************/
// Mapeo de teclas del teclado matricial
static char keymap[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

// Arreglos para manejar los pines de filas y columnas de forma conveniente
static uint16_t row_pins[ROWS] = {R1_PIN, R2_PIN, R3_PIN, R4_PIN};
static uint16_t col_pins[COLS] = {C1_PIN, C2_PIN, C3_PIN};

// Buffer para almacenar teclas presionadas
static char key_buffer[BUFFER_SIZE];
static int buffer_head = 0;
static int buffer_tail = 0;

// Delay para debounce
delay_t debounce_delay;

/***********************************************************************************************************************
 * @brief Inicializacion de los pines GPIOs / Habilita las interrupciones para las columnas / Inicializa las filas en 1
 * @param void
 * @retval void
************************************************************************************************************************/
void keypad_init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configuración de los pines de columna como entradas con interrupciones en flanco descendente
    GPIO_InitStruct.Pin = C1_PIN | C2_PIN | C3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(C_PORT, &GPIO_InitStruct); // C_PORT = Puerto de Columnas correspondientes al puerto E (Confuso)

    // Configuración de los pines de fila como salidas push-pull
    GPIO_InitStruct.Pin = R1_PIN | R2_PIN | R3_PIN | R4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(R_PORT, &GPIO_InitStruct);

    // Inicialmente, todas las filas en estado ALTO
    HAL_GPIO_WritePin(R_PORT, R1_PIN | R2_PIN | R3_PIN | R4_PIN, GPIO_PIN_SET);

    // Habilitar interrupciones para las columnas
    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);

    HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    // Inicialización del debounce y delay
    debounceFSM_init();
    delayInit(&debounce_delay, 40);
}
/*****************************************************************************************************************
 * @brief: Agrega una tecla al buffer
 * @param recibe variable tipo caracter para agregar al buffer
 * @retval void
******************************************************************************************************************/
static void buffer_add(char key) {
    key_buffer[buffer_head] = key;
    buffer_head = (buffer_head + 1) % BUFFER_SIZE;
    if (buffer_head == buffer_tail) {
        buffer_tail = (buffer_tail + 1) % BUFFER_SIZE; // Sobrescribe la tecla más antigua si el buffer está lleno
    }
}
/*****************************************************************************************************************
 * @brief: Obtiene una tecla del buffer
 * @param void
 * @retval Devuelve la tecla presionada
******************************************************************************************************************/
char buffer_get(void) {
    if (buffer_head == buffer_tail) return 0; // Si el buffer está vacío
    char key = key_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % BUFFER_SIZE;
    return key;
}
/*****************************************************************************************************************
 * @brief: Verifica si alguna tecla está presionada
 * @param void
 * @retval Devuelve variable booleana para confirmar o no si una tecla se mantiene presionada
******************************************************************************************************************/
bool keypad_key_pressed(void) {
    for (int row = 0; row < ROWS; row++) {
        HAL_GPIO_WritePin(R_PORT, row_pins[row], GPIO_PIN_RESET);
        for (int col = 0; col < COLS; col++) {
            if (HAL_GPIO_ReadPin(C_PORT, col_pins[col]) == GPIO_PIN_RESET) {
                HAL_GPIO_WritePin(R_PORT, row_pins[row], GPIO_PIN_SET);
                return true;
            }
        }
        HAL_GPIO_WritePin(R_PORT, row_pins[row], GPIO_PIN_SET);
    }
    return false;
}
/*****************************************************************************************************************
 * @brief: Escanea el teclado y agrega teclas al buffer usando la FSM de debounce
 * @param: void
 * @retval: void
******************************************************************************************************************/
void scan_keypad(void) {
    for (int row = 0; row < ROWS; row++) {
        HAL_GPIO_WritePin(R_PORT, row_pins[row], GPIO_PIN_RESET);
        for (int col = 0; col < COLS; col++) {
            debounceFSM_update(HAL_GPIO_ReadPin(C_PORT, col_pins[col]));
            if (readKey()) { // Se detectó una pulsación estable
                buffer_add(keymap[row][col]);
            }
        }
        HAL_GPIO_WritePin(R_PORT, row_pins[row], GPIO_PIN_SET);
    }
}
/*****************************************************************************************************************
 * @brief: Obtiene una tecla del buffer
 * @param void
 * @retval void
******************************************************************************************************************/
char keypad_get_key(void) {
    return buffer_get();
}
