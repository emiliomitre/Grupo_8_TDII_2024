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
  ***************************************************************************************************************************************************************
  */
/* USER CODE END Header */
/* Includes ----------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"
#include "API_Delay.h"
#include "API_Debounce.h"
/* Private includes --------------------------------------------------------------------------------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef ---------------------------------------------------------------------------------------------------------------------------------------------*/
typedef enum{				//Se definen dos constantes enum para las secuencias y se utiliza typedef para asignarle el alias secuencia
	secuencia_1=0,
	secuencia_2=1,
	secuencia_3=2,
	secuencia_4=3
} secuencia;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ----------------------------------------------------------------------------------------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 3 																		// Variable N para definir el tamaño del vector LED
/* USER CODE END PD */

/* Private macro ----------------------------------------------------------------------------------------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ------------------------------------------------------------------------------------------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint16_t 	LED[N]={LD1_Pin, LD2_Pin, LD3_Pin};										//vector de leds
secuencia 	estado_secuencia=secuencia_1;  											//el estado inicial sera la secuencia normal
bool_t	 	estado_boton=0;
delay_t delay1, delay2, delay3, delay4;
/* USER CODE END PV */
/* Private function prototypes ---------------------------------------------------------------------------------------------------------------------------------*/
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
void MX_GPIO_Init(void);

void secuencia1(void);
void secuencia2(void);
void secuencia3(void);
void secuencia4(void);
/* USER CODE END PFP */

/* Private user code -------------------------------------------------------------------------------------------------------------------------------------------*/
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
	delayInit(&delay1, 100);
	delayInit(&delay2, 250);
	delayInit(&delay3, 500);
	delayInit(&delay4, 1000);													//600ms
  /* USER CODE END 1 */

  /* MCU Configuration-------------------------------------------------------------------------------------------------------------------------------------------*/

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
  /*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
  while (1){
	/* Programa para hacer parpadear leds en secuencia cada 200 ms */
	  readButton = readButton_GPIO(); 												// Lee estado actual del boton y lo guarda
	  debounceFSM_update(readButton);
	  if(readKey()){
		 estado_secuencia=(estado_secuencia+1)%4;									// Cambia entre las 4 secuencias
		 writeLedOff_GPIO(LED[0] | LED[1] | LED[2]);								// Se apagan todos los leds antes de comenzar una nueva secuencia
	  }

	  /* Selecciona cual secuencia se ejecutara*/
	  switch (estado_secuencia){

	  	  case 0:
	  		  	  	  secuencia1();
	  		  	  	  break;
	  	  case 1:
	  		  		  secuencia2();
	  		  		  break;
	  	  case 2:
	  		  		  secuencia3();
	  		  		  break;
	  	  case 3:
	  		  		  secuencia4();
	  		  		  break;
	  }
  }
/* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}
/* USER CODE BEGIN 4 */
// Funcion para hacer parpadear simultaneamente todos los leds cada 100ms
void secuencia1(void){
	if(delayRead(&delay1)){
		toggleLed_GPIO( LED[0] | LED[1]| LED[2]);
	}
}

// Funcion para hacer parpadear simultaneamente todos los leds cada 250ms
void secuencia2(void){

	if(delayRead(&delay2)){
		toggleLed_GPIO( LED[0] | LED[1]| LED[2]);
	}
}

// Funcion para hacer parpadear simultaneamente todos los leds cada 500ms
void secuencia3(){

	if(delayRead(&delay3)){
		toggleLed_GPIO( LED[0] | LED[1]| LED[2]);
	}
}

// Funcion para hacer parpadear simultaneamente todos los leds cada 1000ms
void secuencia4(){

	if(delayRead(&delay4)){
		toggleLed_GPIO( LED[0] | LED[1]| LED[2]);
	}
}
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
