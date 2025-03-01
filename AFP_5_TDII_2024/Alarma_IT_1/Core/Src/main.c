/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "API_BT.h"				//Libreria para el manejo de modulo HC-05 USART2
#include "API_GPIO.h"			//Libreria para el manejo de puertos GPIO (Sensores, Sirena y Leds)
#include "API_Debounce.h"		//Libreria para evitar el rebote mecanico en la pulsacion de botones
#include "API_Delay.h"			//Libreria para retardo NO bloqueante
#include "API_Keypad.h"			//Libreria para manejo de teclado matricial 4x3
#include "API_LCD.h"			//Libreria para el manejo de pantalla LCD 2x16 I2C
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;
UART_HandleTypeDef huart2;
/* USER CODE BEGIN PV */
char key;
//extern volatile uint16_t columnPressed = 0;  // Columna detectada en la interrupción
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void DisplayMainMenu();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
  lcd_init();
  DisplayMainMenu();
  debounceFSM_init();  // Inicializa la FSM de debounce
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  while (1) {
		  // Verificar si hay una interrupción pendiente y escanear la tecla
		  key = keypad_scan(columnPressed);
		  if (key != '\0') {
			  //printf("Tecla presionada: %c\n", key);  // Se puede enviar por UART o LCD
			  BT_Test_2();
			  keypad_resetColumn();  // Reiniciar la columna procesada
		  }
	  }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
/* USER CODE BEGIN 4 */
/*****************************************************************************************************************
 * @brief: Función para mostrar el menú principal
 * @param: void
 * @retval: void
******************************************************************************************************************/
void DisplayMainMenu(void) {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("1.Activar *.Mas");
    lcd_set_cursor(1, 0);
    lcd_print("2.Cambiar Pass");
    //currentState = MAIN_MENU;
}
/*****************************************************************************************************************
 * @brief: Callback de interrupción de los pines GPIO.
 *         Maneja interrupciones del teclado matricial y los sensores de la alarma.
 * @param: GPIO_Pin - Pin GPIO que generó la interrupción.
 * @retval: void
******************************************************************************************************************/
/**
 * @brief Callback de interrupción de las columnas
 * @param GPIO_Pin - Pin de la columna que generó la interrupción
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == C1_Pin || GPIO_Pin == C2_Pin || GPIO_Pin == C3_Pin) {
        columnPressed = GPIO_Pin;  // Guardar la columna que generó la interrupción
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
