/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define C1_Pin GPIO_PIN_2
#define C1_GPIO_Port GPIOE
#define R2_Pin GPIO_PIN_3
#define R2_GPIO_Port GPIOE
#define C2_Pin GPIO_PIN_4
#define C2_GPIO_Port GPIOE
#define C3_Pin GPIO_PIN_5
#define C3_GPIO_Port GPIOE
#define R1_Pin GPIO_PIN_6
#define R1_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define R4_Pin GPIO_PIN_7
#define R4_GPIO_Port GPIOF
#define R3_Pin GPIO_PIN_8
#define R3_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define Sirena_Pin GPIO_PIN_5
#define Sirena_GPIO_Port GPIOA
#define Sensor_PIR_Pin GPIO_PIN_6
#define Sensor_PIR_GPIO_Port GPIOA
#define Sensor_Magnetico_1_Pin GPIO_PIN_7
#define Sensor_Magnetico_1_GPIO_Port GPIOA
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define Led_Encendido_Pin GPIO_PIN_13
#define Led_Encendido_GPIO_Port GPIOF
#define Led_Alerta_Pin GPIO_PIN_9
#define Led_Alerta_GPIO_Port GPIOE
#define Led_Estado_Pin GPIO_PIN_11
#define Led_Estado_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define Sensor_Magnetico_2_Pin GPIO_PIN_14
#define Sensor_Magnetico_2_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
