/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  * App 1.1: Desarrolle una aplicacion que encienda y apague de manera secuencial los
  *	tres leds onboard de la placa de desarrollo. La secuencia debe encender 200 ms y
  *	apagar 200 ms cada led comenzando por el LED1 (Green), continuando con el LED2
  *	(Blue) y luego el LED3 (Red) para volver a iniciar con el LED1. La aplicacion debe
  *	ser de caracter general, de manera que pueda extenderse a una cantidad mayor de
  *	leds con minimas modificaciones, por este motivo se sugiere que use un vector para
  *	el manejo de los Leds.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"
#include "API_Delay.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
    ENCENDER_LED0,
    ESPERAR_LED0_OFF,
    ENCENDER_LED1,
    ESPERAR_LED1_OFF,
    ENCENDER_LED2,
    ESPERAR_LED2_OFF
} estado_t;

estado_t estado = ENCENDER_LED0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 3 				//variable N para definir el tamano del vector LED
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t LED[N]={LD1_Pin, LD2_Pin, LD3_Pin};
delay_t delaySecuencia;

//delay_t delays[N]={delay_t delayLed1, delayLed2, delayLed3};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/


/* USER CODE BEGIN PFP */

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
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();

  /* USER CODE BEGIN 2 */
  delayInit(&delaySecuencia, 200); //definir el tiempo de retardo
  //delayInit(&delayLed2, 200); //definir el tiempo de retardo
  //delayInit(&delayLed2, 200); //definir el tiempo de retardo
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* Programa para hacer parpadear leds en secuencia cada 200 ms */

	     if (delayRead(&delaySecuencia)) {
	          // Cambiar estado según la máquina de estados
	          switch (estado) {
	              case ENCENDER_LED0:
	                  toggleLed_GPIO(LED[0]);  // Encender LED 0
	                  delayWrite(&delaySecuencia, 200);  // Esperar 200 ms
	                  estado = ESPERAR_LED0_OFF;
	                  break;

	              case ESPERAR_LED0_OFF:
	                  toggleLed_GPIO(LED[0]);  // Apagar LED 0
	                  delayWrite(&delaySecuencia, 200);  // Esperar 200 ms
	                  estado = ENCENDER_LED1;
	                  break;

	              case ENCENDER_LED1:
	                  toggleLed_GPIO(LED[1]);  // Encender LED 1
	                  delayWrite(&delaySecuencia, 200);  // Esperar 200 ms
	                  estado = ESPERAR_LED1_OFF;
	                  break;

	              case ESPERAR_LED1_OFF:
	                  toggleLed_GPIO(LED[1]);  // Apagar LED 1
	                  delayWrite(&delaySecuencia, 200);  // Esperar 200 ms
	                  estado = ENCENDER_LED2;
	                  break;

	              case ENCENDER_LED2:
	                  toggleLed_GPIO(LED[2]);  // Encender LED 2
	                  delayWrite(&delaySecuencia, 200);  // Esperar 200 ms
	                  estado = ESPERAR_LED2_OFF;
	                  break;

	              case ESPERAR_LED2_OFF:
	                  toggleLed_GPIO(LED[2]);  // Apagar LED 2
	                  delayWrite(&delaySecuencia, 200);  // Esperar 200 ms
	                  estado = ENCENDER_LED0;  // Reiniciar la secuencia
	                  break;
	          }

	     }
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}



/* USER CODE BEGIN 4 */

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
