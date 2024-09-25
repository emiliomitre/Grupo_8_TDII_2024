/*
 * API_GPIO.h
 *
 *  Created on: Aug 29, 2024
 *      Author: tomas
 */
#include <stdint.h>
#include <stdbool.h>

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

typedef uint16_t led_t;
typedef bool buttonStatus_t;


void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART3_UART_Init(void);
void MX_USB_OTG_FS_PCD_Init(void);

void writeLedOn_GPIO(led_t LDx);
void writeLedOff_GPIO(led_t LDx);
void toggleLed_GPIO(led_t LDx);
buttonStatus_t readButton_GPIO(void);



#endif /* API_INC_API_GPIO_H_ */
