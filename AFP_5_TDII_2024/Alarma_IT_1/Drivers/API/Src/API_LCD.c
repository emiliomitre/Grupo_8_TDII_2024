/*****************************************************************************************************************
 * API_LCD.c
 *
 *  Created on: -
 *      Author: GRUPO_8_TDII_2024
 ******************************************************************************************************************/
#include "API_LCD.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
/* Private variables ---------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c2; // Cambia si configuras otro periférico en CubeMX
/* Private define ------------------------------------------------------------*/
#define LCD_ADDR 0x27         // Dirección I2C de la pantalla LCD
/* Private variables ---------------------------------------------------------*/
static uint8_t lcd_backlight = 0x08;
static uint8_t lcd_control = 0x00;

/* Private function prototypes -----------------------------------------------*/
void MX_I2C2_Init(void);
static void lcd_send_command(uint8_t cmd);
static void lcd_send_data(uint8_t data);
static void lcd_send(uint8_t value, uint8_t mode);
static void lcd_write_nibble(uint8_t nibble);
/*****************************************************************************************************************
 * @brief: Inicializar la pantalla LCD
 * @param void
 * @retval void
******************************************************************************************************************/
void lcd_init(void) {
    HAL_Delay(50); // Tiempo de inicio según especificación HD44780
    lcd_send_command(0x30);
    HAL_Delay(5);
    lcd_send_command(0x30);
    HAL_Delay(1);
    lcd_send_command(0x30);
    lcd_send_command(0x20); // Cambiar a modo 4 bits

    lcd_send_command(0x28); // Configuración: LCD 2 líneas, matriz 5x8
    lcd_send_command(0x08); // Apagar display
    lcd_send_command(0x01); // Limpiar pantalla
    HAL_Delay(2);
    lcd_send_command(0x06); // Configurar modo de entrada
    lcd_send_command(0x0C); // Encender display, cursor apagado
}
/*****************************************************************************************************************
 * @brief: Limpiar la pantalla LCD
 * @param void
 * @retval void
******************************************************************************************************************/
void lcd_clear(void) {
    lcd_send_command(0x01); // Limpiar pantalla
    HAL_Delay(2);
}
/*****************************************************************************************************************
 * @brief: Posicionar el cursor en la pantalla LCD
 * @param row: Fila de la pantalla
 * @param col: Columna de la pantalla
 * @retval void
******************************************************************************************************************/
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addresses[] = {0x80, 0xC0}; // Dirección DDRAM para la primera y segunda línea
    lcd_send_command(addresses[row] + col);
}
/*****************************************************************************************************************
 * @brief: Imprimir un texto en la pantalla LCD
 * @param str: Cadena de caracteres a imprimir
 * @retval void
******************************************************************************************************************/
void lcd_print(const char *str) {
    while (*str) {
        lcd_send_data((uint8_t)*str++);
    }
}
/*****************************************************************************************************************
 * @brief: Imprimir un número en la pantalla LCD
 * @param num: Número entero a imprimir
 * @retval void
******************************************************************************************************************/
void lcd_print_num(int num) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d", num);
    lcd_print(buffer);
}
/*****************************************************************************************************************
 * @brief: Enviar un comando a la pantalla LCD
 * @param cmd: Comando a enviar // entero de 8bits sin signo
 * @retval void
******************************************************************************************************************/
static void lcd_send_command(uint8_t cmd) {
    lcd_send(cmd, 0x00);
}
/*****************************************************************************************************************
 * @brief: Enviar un dato a la pantalla LCD
 * @param data: Dato a enviar // Entero sin signo de 8bits
 * @retval void
******************************************************************************************************************/
static void lcd_send_data(uint8_t data) {
    lcd_send(data, 0x01);
}
/*****************************************************************************************************************
 * @brief: Enviar datos a la pantalla LCD
 * @param value: Valor a enviar
 * @param mode: Modo de operación (comando o datos)
 * @retval void
******************************************************************************************************************/
static void lcd_send(uint8_t value, uint8_t mode) {
    lcd_control = lcd_backlight | mode;
    lcd_write_nibble(value & 0xF0);
    lcd_write_nibble((value << 4) & 0xF0);
}
/*****************************************************************************************************************
 * @brief: Escribir un nibble en la pantalla LCD
 * @param nibble: Parte alta o baja del byte a enviar
 * @retval void
******************************************************************************************************************/
static void lcd_write_nibble(uint8_t nibble) {
    uint8_t data = nibble | lcd_control | 0x04; // Habilitar bit Enable
    HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR << 1, &data, 1, HAL_MAX_DELAY);
    data &= ~0x04; // Deshabilitar bit Enable
    HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR << 1, &data, 1, HAL_MAX_DELAY);
}

/*****************************************************************************************************************
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
/******************************************************************************************************************/
void MX_I2C2_Init(void){

	  /* USER CODE BEGIN I2C2_Init 0 */

	  /* USER CODE END I2C2_Init 0 */

	  /* USER CODE BEGIN I2C2_Init 1 */

	  /* USER CODE END I2C2_Init 1 */
	  hi2c2.Instance = I2C2;
	  hi2c2.Init.ClockSpeed = 100000;
	  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	  hi2c2.Init.OwnAddress1 = 0;
	  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	  hi2c2.Init.OwnAddress2 = 0;
	  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE BEGIN I2C2_Init 2 */

	  /* USER CODE END I2C2_Init 2 */

}
