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
uint16_t LED[N]={LD1_Pin, LD2_Pin, LD3_Pin};				//vector de leds
int led_actual=0;

delay_t delay1, delay2, delay3, delay4, delay5;
uint16_t delay[5]={100, 150, 300, 600};						//vector para distintos tiempos de espera funcion delay no bloqueante
int estado_boton=0, estado_anterior=GPIO_PIN_RESET;			//Variables auxiliares para determinar el estado actual y el estado anterior
int secuencia=0;											//Numero de secuencia
bool_t init_4=0;
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
  delayInit(&delay1, delay[0]);		//100ms
  delayInit(&delay2, delay[1]);		//150ms
  delayInit(&delay3, delay[2]);		//300ms
  delayInit(&delay4, delay[3]);		//600ms
  delayInit(&delay5, delay[1]);		//150ms
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  estado_boton=readButton_GPIO();		//Compruebo si el boton esta presionado

	  if (estado_boton==GPIO_PIN_SET && estado_anterior==GPIO_PIN_RESET)
	  {

		  secuencia=(secuencia+1)%4;								//cambia entre las 4 secuencias

		  writeLedOff_GPIO(LED[0] | LED[1] | LED[2]);				//Se apagan todos los leds antes de comenzar una nueva secuencia

		  led_actual=0;
		  init_4=0;
	  }
	  estado_anterior=estado_boton;									//guarda el estado del boton para comparar en el siguiente loop


	  switch (secuencia)
	  {
	  	  case 0:									//Secuencia 1 Parpadean en secuencia cada 150ms (verde, azul, rojo)

	          if (delayRead(&delay2)){
	        	  toggleLed_GPIO(LED[led_actual]);
	          	  led_actual=(led_actual+1)%N;
	          }
	  	  	  break;

	        case 1:									//Secuencia 2 Parpadean los tres en simultaneo cada 300ms
	  	  		if (delayRead(&delay3))
	  	  		{
	  	  			 toggleLed_GPIO(LED[0] | LED[1] | LED[2]);
	  	  		}
	  	  		break;

	        case 2:									//Secuencia 3 Parpadean Led Verde 100ms, Led Azul 300ms y Led Rojo 600ms
	  	  		if (delayRead(&delay1))
	  	  		{
	  	  			toggleLed_GPIO(LED[0]);
	  	  		}
	  	  		if (delayRead(&delay3)){
	  	  			toggleLed_GPIO(LED[1]);
	  	  		}

	  	  		if (delayRead(&delay4)){
	  	  			toggleLed_GPIO(LED[2]);
	  	  		}

	  	  		break;

	        case 3:									//Secuencia 4 Parpadea Verde y Rojo en simultaneo alternado con Azul cada 150ms

	        	if (delayRead(&delay2) && init_4==0)			//en la primera vez que se ingresa a la secuencia se apaga el led2 y se enciende 1 y 3
	  	  		{
	  	  			writeLedOff_GPIO(LED[1]);
	  	  			writeLedOn_GPIO(LED[0] | LED[2]);
	  	  			init_4=1;
	  	  		}

	  	  		if (delayRead(&delay5))
	  	  		{
	  	  			  toggleLed_GPIO(LED[0]	| LED[2]);
	  	  			  toggleLed_GPIO(LED[1]);
	  	  		}

	  	  		break;
	  	}

	 /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
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
