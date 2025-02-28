#include "API_Keypad.h"
#include "stm32f4xx_hal.h"

// Definición de pines del teclado
#define ROWS 4
#define COLS 3

static GPIO_TypeDef *rowPorts[ROWS] = {GPIOE, GPIOE, GPIOF, GPIOF};
static uint16_t rowPins[ROWS] = {GPIO_PIN_6, GPIO_PIN_3, GPIO_PIN_8, GPIO_PIN_7};

static GPIO_TypeDef *colPorts[COLS] = {GPIOE, GPIOE, GPIOE};
static uint16_t colPins[COLS] = {GPIO_PIN_2, GPIO_PIN_4, GPIO_PIN_5};

// Mapeo de teclas del teclado 4x3
static char keymap[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

void keypad_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configurar filas como salidas en estado ALTO
    for (int i = 0; i < ROWS; i++) {
        GPIO_InitStruct.Pin = rowPins[i];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(rowPorts[i], &GPIO_InitStruct);
        HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_SET);
    }

    // Configurar columnas como entradas con pull-up
    for (int j = 0; j < COLS; j++) {
        GPIO_InitStruct.Pin = colPins[j];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(colPorts[j], &GPIO_InitStruct);
    }
}

char keypad_getkey() {
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
}
