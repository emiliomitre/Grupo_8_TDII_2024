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
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{				//Se definen dos constantes enum para las secuencias y se utiliza typedef para asignarle el alias secuencia
	secuencia_normal=1,
	secuencia_invertida=-1
} secuencia;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 3 //variable N para definir el tamaño del vector LED
int LED[N]={LD1_Pin, LD2_Pin, LD3_Pin}; 	/*Vector de leds*/
secuencia estado_secuencia=secuencia_normal;  //el estado inicial sera la secuencia normal

int estado_boton=0, estado_anterior=GPIO_PIN_RESET;		//Controlar si el boton esta presionado y si es que no mantuvo asi hasta que vuelva a controlarse el estado

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/


/* USER CODE BEGIN PFP */
void encender_leds_normal(void){							/* Funciona para secuencia en orden ascendente del vector (Verde, Azul, Rojo)*/

	writeLedOff_GPIO(LED[N-1]);
	for (int i = 0; i < N; i++)
	{

		writeLedOn_GPIO(LED[i]);
		HAL_Delay(200);
		writeLedOff_GPIO(LED[i]);
		HAL_Delay(200);
	}
}

void encender_leds_invertido(void){							/* Funciona para secuencia en orden descendente del vector (Rojo, Azul, Verde)*/

	writeLedOff_GPIO(LED[0]);
	for (int i=N-1; i>=0; i--){
		writeLedOn_GPIO(LED[i]);
		HAL_Delay(200);
		writeLedOff_GPIO(LED[i]);
		HAL_Delay(200);
	}
}
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
		  	estado_secuencia=-estado_secuencia;								/*	Los valores para las 2 secuencias son 1 y -1*/

	  }
	  estado_anterior=estado_boton;											/* Guarda el si el boton esta pulsado o no cuando se hizo el control*/


	  switch (estado_secuencia){											/* Selecciona cual secuencia se ejecutara*/

	  	  case -1:
	  		  encender_leds_invertido();
	  		  break;
	  	  case 1:
	  		  encender_leds_normal();
	  		  break;
	  }
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
