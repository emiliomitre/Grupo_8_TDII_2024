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
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{				//Se definen dos constantes enum para las secuencias y se utiliza typedef para asignarle el alias secuencia
	secuencia_1=1,
	secuencia_2=2,
	secuencia_3=3,
	secuencia_4=4
} secuencia;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 3 //variable N para definir el tamaño del vector LED
int LED[N]={LD1_Pin, LD2_Pin, LD3_Pin}; 	/*Vector de leds*/
secuencia estado_secuencia=secuencia_1;  //el estado inicial sera la secuencia normal

int estado_boton=0, estado_anterior=GPIO_PIN_RESET;		//Controlar si el boton esta presionado y si es que no mantuvo asi hasta que vuelva a controlarse el estado

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
void secuencia1(void);
void secuencia2(void);
void secuencia3(void);
void secuencia4(void);
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Secuencia de parpadeo de leds que se alterna cada vez que se presiona el boton de usuario en la placa */

	  estado_boton=readButton_GPIO();		//Compruebo si el boton esta presionado

	  if(estado_boton==GPIO_PIN_SET && estado_anterior==GPIO_PIN_RESET){	/*	-Cambia el estado de la secuencia
		  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 	- Evita que alterne una y otra vez si se lo mantiene presionado*/
		  	estado_secuencia=estado_secuencia+1; 							/*	Los valores para las 4 secuencias de 1 a 4*/

		  	if(estado_secuencia==5){
		  		estado_secuencia=1;											/* Cuando termina la secuencia 4 vuelve a la secuencia 1*/
		  	}
		  	writeLedOff_GPIO(LED[0] | LED[1]| LED[2]);
	  }
	  estado_anterior=estado_boton;											/* Guarda el si el boton esta pulsado o no cuando se hizo el control*/

	  /* Selecciona cual secuencia se ejecutara*/
	  switch (estado_secuencia){

	  	  case 1:
	  		  	  	  secuencia1();
	  		  	  	  break;
	  	  case 2:
	  		  		  secuencia2();
	  		  		  break;
	  	  case 3:
	  		  		  secuencia3();
	  		  		  break;
	  	  case 4:
	  		  		  secuencia4();
	  		  		  break;
	  }

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
/* USER CODE BEGIN 4 */
void secuencia1(void){							/* Funcion para encender en orden ascendente el vector de leds (Verde, Azul, Rojo)*/

	writeLedOff_GPIO(LED[N-1]);
	for (int i = 0; i < N; i++)
	{
		writeLedOn_GPIO(LED[i]);
		HAL_Delay(200);
		writeLedOff_GPIO(LED[i]);
		HAL_Delay(200);
	}
}

/* Funcion para hacer parpadear los 3 leds de manera simultanea cada 300ms*/
void secuencia2(void){

	writeLedOn_GPIO(LED[0] | LED[1]| LED[2]);
	HAL_Delay(300);
	writeLedOff_GPIO(LED[0] | LED[1]| LED[2]);
	HAL_Delay(300);

}
// Funcion para hacer parpadear el LED1 cada 100ms, LED2 cada 300ms, LED3 cada 600ms
void secuencia3(){
	toggleLed_GPIO(LED[0] | LED[1]| LED[2]);
	HAL_Delay(100);
	toggleLed_GPIO(LED[0]);
	HAL_Delay(100);
	toggleLed_GPIO(LED[0]);
	HAL_Delay(100);
	toggleLed_GPIO(LED[0] | LED[1]);				// !!Verificar que el funcionamiento de los LEDS sea el correcto para todos los casos, llamando a la funcion de esta manera
	HAL_Delay(100);									// Recordar que la funcion toggle espera 1 sola variable LDx...
	toggleLed_GPIO(LED[0]);
	HAL_Delay(100);
	toggleLed_GPIO(LED[0]);
	HAL_Delay(100);
}

// Funcion para hacer parpadear simultaneamente el LED1 y LED3
void secuencia4(){
	writeLedOff_GPIO(LED[2]);
	toggleLed_GPIO(LED[0] | LED[2]);
	HAL_Delay(150);
	toggleLed_GPIO(LED[0] | LED[1] | LED[2]);
	HAL_Delay(150);
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
