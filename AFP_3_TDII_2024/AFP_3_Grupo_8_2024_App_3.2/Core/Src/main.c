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
  * App1.2: Desarrolle una aplicacion que utilice el pulsador onboard de la pla
  * ca de desarrollo para alternar entre dos secuencias diferentes. La app ini-
  * cia con la secuencias de la App1.1 y, cuando se presione el pulsador, dicha
  * secuencia debe invertirse y continuar, de manera que, cada vez que se pre-
  * sione el pulsador la secuencia actual se invierta. La app debe ser de carac
  * ter general, por lo que aplica la misma recomendacion para el punto anterior.
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
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 3 				//variable N para definir el tamano del vector LED

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
estado_t estado=ENCENDER_LED0;  // Inicializo el orden de encendido de los LEDs

int estado_boton=0, estado_anterior=GPIO_PIN_RESET;								//Variables auxiliares para determinar el estado actual y el estado anterior
																				//para luego comparar los 2 estados y verificar que no se este pulsando
																				//constantemente el pulsador.
// Define las secuencias de encendido de LEDs
const int secuencia_normal[] = {0, 1, 2};     									// LED Verde, Azul, Rojo
const int secuencia_invertida[] = {2, 1, 0};  									// LED Rojo, Azul, Verde
int estado_secuencia=1;  														//el estado inicial sera la secuencia normal

/* USER CODE BEGIN PV */
uint16_t LED[N]={LD1_Pin, LD2_Pin, LD3_Pin};
delay_t delaySecuencia;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
//void encender_leds_invertido(void);
void control_leds(const int *secuencia);
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
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
/* Programa para prender secuencialmente leds 1,2,3 y de manera invertida 3,2,1. Alternando entre secuencias cuando se presiona el pulsador */
	  estado_boton=readButton_GPIO();		//Compruebo si el boton esta presionado

	  if(estado_boton==GPIO_PIN_SET && estado_anterior==GPIO_PIN_RESET){		//	Cambia el estado de la secuencia - Evita que alterne una y otra vez si se lo mantiene presionado
		  estado_secuencia=-estado_secuencia;									//	Los valores para las 2 secuencias son 1 y -1
		  estado = ENCENDER_LED0;												// Reinicia al primer estado en cada cambio de secuencia
		  writeLedOff_GPIO(LED[0] | LED[1] | LED[2]);
	  }
	  estado_anterior=estado_boton;												// Guarda el estado anterior para asegurar si el boton esta pulsado o no cuando se hizo el control

	  	  switch (estado_secuencia){											// Selecciona cual secuencia se ejecutara
	  	  	  case 1:
	  	  		  control_leds(secuencia_normal);
	  	  		  break;
	  	  	  case -1:
	  	  		  control_leds(secuencia_invertida);
	  	  		  break;
	  	  }
   }
}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */




/* USER CODE BEGIN 4 */
void control_leds(const int* secuencia){		/* Funciona para secuencia en orden ascendente y descendente*/

    if (delayRead(&delaySecuencia)) {
         // Cambiar estado según la máquina de estados
         switch (estado) {
             case ENCENDER_LED0:
            	 toggleLed_GPIO(LED[secuencia[0]]); 						 // Encender LED 0
                 estado = ESPERAR_LED0_OFF;
                 break;

             case ESPERAR_LED0_OFF:
            	 toggleLed_GPIO(LED[secuencia[0]]);  						// Apagar LED 0
                 estado = ENCENDER_LED1;
                 break;

             case ENCENDER_LED1:
            	 toggleLed_GPIO(LED[secuencia[1]]);  						// Encender LED 1
                 estado = ESPERAR_LED1_OFF;
                 break;

             case ESPERAR_LED1_OFF:
            	 toggleLed_GPIO(LED[secuencia[1]]);  						// Apagar LED 1
                 estado = ENCENDER_LED2;
                 break;

             case ENCENDER_LED2:
            	 toggleLed_GPIO(LED[secuencia[2]]); 						// Encender LED 2
                 estado = ESPERAR_LED2_OFF;
                 break;

             case ESPERAR_LED2_OFF:
            	 toggleLed_GPIO(LED[secuencia[2]]);  						// Apagar LED 2
                 estado = ENCENDER_LED0; 									// Reiniciar la secuencia
                 break;
         }

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
