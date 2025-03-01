/*****************************************************************************************************************
 * API_LCD.h
 *
 *  Created on: -
 *      Author: GRUPO_8_TDII_2024
 ******************************************************************************************************************/
#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include "stm32f4xx_hal.h"

// Prototipos de funciones públicas
void lcd_init();
void lcd_clear();
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);
void lcd_print_num(int num);
void MX_I2C2_Init(void);

#endif /* LCD_I2C_H_ */
