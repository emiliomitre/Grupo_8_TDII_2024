/*************************************************************************************************************************
 * API_GPIO.c
 *
 *  Created on: -
 *      Author: GRUPO_8_TDII_2024
 *************************************************************************************************************************/

/* Includes */
#include "main.h"
#include "API_GPIO.h"


/*Declaracion de variables*/
led_t LDx; 					/*Valores esperadors de LDx: LD1_Pin|LD3_Pin|LD2_Pin*/

extern UART_HandleTypeDef huart2;
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
void MX_GPIO_Init(void){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOE, R2_Pin|R1_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOF, R4_Pin|R3_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(LED_Encendido_GPIO_Port, LED_Encendido_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOE, LED_Alerta_Pin|LED_Estado_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : C1_Pin C2_Pin C3_Pin */
	  GPIO_InitStruct.Pin = C1_Pin|C2_Pin|C3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	  /*Configure GPIO pins : R2_Pin R1_Pin  */
	  GPIO_InitStruct.Pin = R2_Pin|R1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	  /*Configure GPIO pins : R4_Pin R3_Pin */
	  GPIO_InitStruct.Pin = R4_Pin|R3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	  /*Configure GPIO pin : USER_Btn_Pin */
	  GPIO_InitStruct.Pin = USER_Btn_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LED_Encendido__Pin */
	  GPIO_InitStruct.Pin = LED_Encendido_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	  /*Configure GPIO pins :LED_Alerta__Pin LED_Estado__Pin */
	  GPIO_InitStruct.Pin = LED_Alerta_Pin|LED_Estado_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);


	  /*Configure GPIO pin : Buzzer_Pin */
	  GPIO_InitStruct.Pin = Buzzer_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(Buzzer_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : Sensor_PIR_Pin Sensor_Magnetico_1_Pin */
	  GPIO_InitStruct.Pin = Sensor_PIR_Pin|Sensor_Magnetico_1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
	  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pins : Sensor_Magnetico_2_Pin Sensor_Magnetico_3_Pin */
	  GPIO_InitStruct.Pin = Sensor_Magnetico_2_Pin|Sensor_Magnetico_3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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

	  /* EXTI2_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	  /* EXTI4_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	  /* EXTI9_5_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	  /* USART2_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(USART2_IRQn);
	  /* EXTI15_10_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}





