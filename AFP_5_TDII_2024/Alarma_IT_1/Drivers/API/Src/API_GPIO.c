/*
 * API_GPIO.c
 *
 *  Created on: Aug 29, 2024
 *      Author: tomas jorrat
 */

/* Includes */
#include "main.h"
#include "API_GPIO.h"
#include "API_Teclado4x3.h"
#include "API_Delay.h"

/*Declaracion de variables*/
led_t LDx; 					/*Valores esperadors de LDx: LD1_Pin|LD3_Pin|LD2_Pin*/

/* Function Definition *******************************/

/*
 * @brief Encender LED GPIO
 * @param led_t LDx
 * @retval ninguno

 */
void writeLedOn_GPIO(led_t LDx){
	HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_SET);
}

/*
 * @brief Apagar LED GPIO
 * @param led_t LDx
 * @retval ninguno
 */

void writeLedOff_GPIO(led_t LDx){
	HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_RESET);
}

/*
 * @brief Alternar LED GPIO
 * @param led_t LDx
 * @retval ninguno
 */

void toggleLed_GPIO(led_t LDx){
	HAL_GPIO_TogglePin(GPIOB, LDx);
}

buttonStatus_t readButton_GPIO(void){
	return HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin);
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE(); // RCC Puerto E
  __HAL_RCC_GPIOC_CLK_ENABLE();	// RCC Puerto C
  __HAL_RCC_GPIOF_CLK_ENABLE();	// RCC Puerto F
  __HAL_RCC_GPIOH_CLK_ENABLE(); // RCC Puerto H
  __HAL_RCC_GPIOA_CLK_ENABLE();	// RCC Puerto A
  __HAL_RCC_GPIOB_CLK_ENABLE(); // RCC Puerto B
  __HAL_RCC_GPIOD_CLK_ENABLE();	// RCC Puerto D
  __HAL_RCC_GPIOG_CLK_ENABLE();	// RCC Puerto G

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, R2_Pin|R1_Pin, GPIO_PIN_SET);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, R4_Pin|R3_Pin, GPIO_PIN_SET);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Sirena_GPIO_Port, Sirena_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Led_Encendido_GPIO_Port, Led_Encendido_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, Led_Alerta_Pin|Led_Estado_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pins : R2_Pin R1_Pin Led_Alerta_Pin Led_Estado_Pin */
  GPIO_InitStruct.Pin = Led_Alerta_Pin|Led_Estado_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);
  /*Configure GPIO pins : R4_Pin R3_Pin Led_Encendido_Pin */
  GPIO_InitStruct.Pin = Led_Encendido_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  /*Configure GPIO pin : Sirena_Pin */
  GPIO_InitStruct.Pin = Sirena_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Sirena_GPIO_Port, &GPIO_InitStruct);
  /*Configure GPIO pins : Sensor_PIR_Pin Sensor_Magnetico_1_Pin */
  GPIO_InitStruct.Pin = Sensor_PIR_Pin|Sensor_Magnetico_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  /*Configure GPIO pin : Sensor_Magnetico_2_Pin */
  GPIO_InitStruct.Pin = Sensor_Magnetico_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Sensor_Magnetico_2_GPIO_Port, &GPIO_InitStruct);
  /*Configure GPIO pin : Sensor_Magnetico_3_Pin */
  GPIO_InitStruct.Pin = Sensor_Magnetico_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Sensor_Magnetico_3_GPIO_Port, &GPIO_InitStruct);
  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);
  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}
/*****************************************************************************************************************
 * @brief: Habilita las interrupciones en los pines GPIOs correspondientes a las columnas del teclado matricial.
 * @param: void
 * @retval: void
******************************************************************************************************************/
void enableKeypadInterrupts(void) {
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);  // Habilita interrupción para C1_PIN
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);  // Habilita interrupción para C2_PIN
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // Habilita interrupción para C3_PIN
}

/*****************************************************************************************************************
 * @brief: Deshabilita las interrupciones en los pines GPIOs correspondientes a las columnas del teclado matricial.
 * @param: void
 * @retval: void
******************************************************************************************************************/
void disableKeypadInterrupts(void) {
    HAL_NVIC_DisableIRQ(EXTI2_IRQn);  // Deshabilita interrupción para C1_PIN
    HAL_NVIC_DisableIRQ(EXTI4_IRQn);  // Deshabilita interrupción para C2_PIN
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn); // Deshabilita interrupción para C3_PIN
}

/*****************************************************************************************************************
 * @brief: Habilita las interrupciones en los pines GPIOs correspondientes a los sensores.
 * @param: void
 * @retval: void
******************************************************************************************************************/
void enableSensorInterrupts(void) {
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
/*****************************************************************************************************************
 * @brief: Deshabilita las interrupciones en los pines GPIOs correspondientes a los sensores.
 * @param: void
 * @retval: void
******************************************************************************************************************/
void disableSensorInterrupts(void) {
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*****************************************************************************************************************
 * @brief: Callback de interrupción de los pines GPIO.
 *         Maneja interrupciones del teclado matricial y los sensores de la alarma.
 * @param: GPIO_Pin - Pin GPIO que generó la interrupción.
 * @retval: void
******************************************************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    //Caso 1: Sensores de la alarma
    if (currentState == ACTIVE_ALARM) {  // Solo procesar interrupciones si la alarma está activada
        if (GPIO_Pin == Sensor_Magnetico_1_Pin ||
            GPIO_Pin == Sensor_Magnetico_2_Pin ||
            GPIO_Pin == Sensor_Magnetico_3_Pin) {
            AlarmTriggered();  // 🚨 Se detectó la apertura de una puerta o ventana
            return;
        }
        else if (GPIO_Pin == Sensor_PIR_Pin && includeMotionSensor) {
            AlarmTriggered();  // 🚨 Se detectó movimiento con el sensor PIR
            return;
        }
    }

    //Caso 2: Teclado matricial
    if (GPIO_Pin == C1_PIN || GPIO_Pin == C2_PIN || GPIO_Pin == C3_PIN) {
        if (delayRead(&debounce_delay)) {  // Verifica debounce antes de escanear
            scan_keypad();  // Escanear teclado y agregar tecla al buffer
        }
    }
}
