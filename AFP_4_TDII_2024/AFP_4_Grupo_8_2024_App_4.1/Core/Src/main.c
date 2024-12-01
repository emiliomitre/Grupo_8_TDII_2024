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
  *	App4.1: Originalmente la App1.1 no hace uso del pulsador, entonces como para
  *	practicar se modifico el enunciado de manera que al presionar el pulsador,
  *	quede prendido el LED1 de manera permanente y al pulsar nuevamente vuelva a
  *	la secuencia original de la App1.1
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"
#include "API_Delay.h"
#include "API_Debounce.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {				// Simplificacion de codigo para portabilidad
	LED_ON,					// y facilidad de implementacion en futuras practicas
	LED_OFF
} ledestado_t;

typedef struct{
	ledestado_t estado;
	uint8_t ledActual;
	delay_t delaySecuencia;
} controladorLed_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 3 				//variable N para definir el tamaño del vector LED
#define Time 200			// Variable tiempo que va estar prendido o apagado cada LED
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
controladorLed_t LedController;
uint16_t LED[N]={LD1_Pin, LD2_Pin, LD3_Pin};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

bool readButton = true;
bool toggle = false;

void Secuencia_Normal(void) {										// Secuencia que prende leds 1,2,3 repetitivamente
    if (delayRead(&LedController.delaySecuencia)) {
        switch (LedController.estado) {
            case LED_ON:
            	writeLedOn_GPIO(LedController.ledActual);
                LedController.estado = LED_OFF;
                delayWrite(&LedController.delaySecuencia, Time); // Configura el tiempo de espera
                break;

            case LED_OFF:
            	writeLedOff_GPIO(LedController.ledActual);
                LedController.ledActual = (LedController.ledActual + 1) % N; // Pasa al siguiente LED
                LedController.estado = LED_ON;
                delayWrite(&LedController.delaySecuencia, Time); // Configura el tiempo de espera
                break;
        }
    }
}

void initLedController(void){
	LedController.estado = LED_ON;
	LedController.ledActual=0;
	delayInit(&LedController.delaySecuencia, Time);
}

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
  delayRead(&LedController.delaySecuencia);	//Inicia conteo del delay por primera vez que se ejecuta
  writeLedOff_GPIO(LED[0] | LED[1] | LED[2]);
  debounceFSM_init();
  initLedController();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){
	/* Programa para hacer parpadear leds en secuencia cada 200 ms */
	  readButton = readButton_GPIO(); 		// Lee estado actual del boton y lo guarda
	  debounceFSM_update(readButton);


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
