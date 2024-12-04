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
  * Descripcion App4.1: Originalmente la app1.1 no hace uso del boton de usuario
  * de la placa de desarrollo, unicamente tiene 1 secuencia. Para poder implemen
  * tar la API Antirebote agregaremos una secuencia 2 donde el LED_2 se mantenga
  * encendido continuamente.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"
#include "API_Delay.h"
#include "API_Debounce.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 3 																		// Variable N para definir el tamaño del vector LED
#define LED_DELAY 200																// Retardo
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint16_t LED[N]={LD1_Pin, LD2_Pin, LD3_Pin};										//vector de leds
int led_actual=0;
delay_t delay;
uint8_t estado_boton=0;
uint8_t secuencia=0;																//Numero de secuencia
/* USER CODE END PV */
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool_t readButton = true;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	delayInit(&delay, LED_DELAY);		//200ms
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
  writeLedOff_GPIO(LED[0] | LED[1] | LED[2]);
  debounceFSM_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* ---------------------------------------------------------------------------*/
  while (1){
	/* Programa para hacer parpadear leds en secuencia cada 200 ms */
	  readButton = readButton_GPIO(); 												// Lee estado actual del boton y lo guarda
	  debounceFSM_update(readButton);
	  if(readKey()){
		 secuencia=(secuencia+1)%2;													//cambia entre las 4 secuencias
		 writeLedOff_GPIO(LED[0] | LED[1] | LED[2]);								//Se apagan todos los leds antes de comenzar una nueva secuencia
	  }
	  	  switch (secuencia)
	 	  {
	 	  	  case 0:																//Secuencia 1 Parpadean en secuencia cada 200ms (verde, azul, rojo)

	 	          if (delayRead(&delay)){
	 	        	  toggleLed_GPIO(LED[led_actual]);
	 	          	  led_actual=(led_actual+1)%N;
	 	          }
	 	  	  	  break;

	 	        case 1:																//Secuencia 2 Parpadean los tres en simultaneo cada 300ms
	 	  	  		if (delayRead(&delay)){
	 	  	  			 toggleLed_GPIO(LED[1]);
	 	  	  		}
	 	  	  		break;

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
void Error_Handler(void){
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1){

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
