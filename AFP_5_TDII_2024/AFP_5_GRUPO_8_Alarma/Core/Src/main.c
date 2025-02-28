/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "API_BT.h"					// Libreria para el manejo de modulo BT HC-05 USART2
#include "API_Debounce.h"			// Libreria para anti rebote de pulsadores
#include "API_Delay.h"				// Libreria Delay no bloqueante
#include "API_GPIO.h"				// Libreria modulos GPIO
#include "API_Keypad.h"				// Librería para manejar el teclado matricial 4x3
#include "API_LCD.h"				// Librería para manejar una pantalla 2x16 mediante I2C

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
	MAIN_MENU,
	ALARM_MENU,
	CHANGE_PASS_MENU,
	TEST_ALARM_MENU,
	ACTIVE_ALARM
} MenuState;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char currentPassword[5] = "1234";  								// Almacena la contraseña actual (Por defecto 1234)
char newPassword[5];               								// Almacena la contraseña nueva
char key;														// Almacena el valor de la tecla presionada
MenuState currentState = MAIN_MENU;
bool includeMotionSensor = false;								// Inlcluye o no el sensor PIR
bool MotionDetected_1, MotionDetected_2, MotionDectected_PIR;	// Estado de los sensores
bool alarmActivated = false;   									// Estado de la alarma
bool countdownStarted = false; 									// Temporizador interno
char inputBuffer[5];
uint8_t inputIndex = 0;
uint32_t startTime = 0;        									// Momento en que inicia el temporizador interno

delay_t DelayGRAL_1;					// Variables de retardos generales para uso independiente
delay_t DelayGRAL_2;
delay_t	LCD_Muestro;					// Delay para muestreo de mensaje en LCD
delay_t Delay_Sirena;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void DisplayMainMenu();														// Menu Principal
void HandleMainMenuInput(char key);											// Manejo del menu principal
void DisplayAlarmMenu();													// Menu de activacion de alarma
void HandleAlarmMenuInput(char key);										// Manejo del menu de activacion de alarma
void RequestPassword(void (*onSuccess)(void), void (*onFailure)(void));		// Pedir la contraseña
void ActivateAlarm();														// Secuencia de activacion
void DeactivateAlarm();														// Secuencia de desactivacion
void DisplayChangePassMenu();												// Menu de cambio de contraseña
void ConfirmNewPassword();													// Contraseña nueva
void HandleSubMenu();														// Submenu del principal
void TestAlarm();															// Prueba de alarma
extern void AlarmTriggered();												// Disparo de alarma
void IncorrectPassword();													// Contraseña incorrecta
void HandleActiveAlarm(char key);											// Manejo de la activacion de la alarma
void CheckSensors();														// Control del estado de sensores
void CheckAlarmDeactivation(char key);										// Control para desactivar la alarma


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
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  keypad_init();
  BT_Test();
  MX_I2C2_Init();
  HAL_Delay(30);
  lcd_init();

  /* USER CODE END Init */

  /* Configure the system clock */


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(Led_Encendido_GPIO_Port, Led_Encendido_Pin, GPIO_PIN_SET);
  DisplayMainMenu();
  delayInit(&DelayGRAL_1,20000);
  delayInit(&DelayGRAL_2,10000);
  delayInit(&LCD_Muestro,2000);
  delayInit(&Delay_Sirena,500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  key = keypad_getkey(); // Modificacion del if dentro del switch
	  switch (currentState){
		  case MAIN_MENU:
			  	  if (key != '\0') HandleMainMenuInput(key);
			  	  break;
		  case ALARM_MENU:
			  	  if (key != '\0') HandleAlarmMenuInput(key);
			  	  break;
		  case CHANGE_PASS_MENU:
		  case TEST_ALARM_MENU:
		  case ACTIVE_ALARM:
			  	  CheckSensors();
			  	  break;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

// AQUI



/* USER CODE BEGIN 4 */
/*****************************************************************************************************************
 * @brief: Función para mostrar el menú principal
 * @param: void
 * @retval: void
******************************************************************************************************************/
void DisplayMainMenu() {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("1.Activar *.Mas");
    lcd_set_cursor(1, 0);
    lcd_print("2.Cambiar Pass");
    currentState = MAIN_MENU;
}

/*****************************************************************************************************************
 * @brief: Manejo de la entrada del menú principal
 * @param: recibe una variable tipo caracter para entrar en las distintas opciones de menu
 * @retval: void
******************************************************************************************************************/
void HandleMainMenuInput(char key) {
    switch (key) {
        case '1':
            DisplayAlarmMenu();
            break;
        case '2':
            DisplayChangePassMenu();
            break;
        case '*':
            HandleSubMenu();
            break;
    }
}

/*****************************************************************************************************************
 * @brief: Mostrar menú para activar alarma
 * @param: void
 * @retval: void
******************************************************************************************************************/
void DisplayAlarmMenu(void) {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("1.Sist Completo");
    lcd_set_cursor(1, 0);
    lcd_print("2.Sin Sensor Mov");
    currentState = ALARM_MENU;
}

/*****************************************************************************************************************
 * @brief: Manejo de la entrada del menú de alarma
 * @param: Recibe variable tipo caracter
 * @retval:
******************************************************************************************************************/
void HandleAlarmMenuInput(char key) {
    switch (key) {
        case '1':  // Modo "Sistema Completo"
            includeMotionSensor = true;
            HAL_GPIO_WritePin(Led_Estado_GPIO_Port, Led_Estado_Pin, GPIO_PIN_RESET);
            RequestPassword(ActivateAlarm, DisplayAlarmMenu);
            break;
        case '2':  // Modo "Sin Sensor de Movimiento"
            includeMotionSensor = false;
            HAL_GPIO_WritePin(Led_Estado_GPIO_Port, Led_Estado_Pin, GPIO_PIN_SET);
            RequestPassword(ActivateAlarm, DisplayAlarmMenu);
            break;
        case '*':  // Si el usuario presiona "*", volver al menú principal
            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("Operacion");
            lcd_set_cursor(1, 0);
            lcd_print("Cancelada");
            while(!delayRead(&LCD_Muestro)){
            	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
            }
            DisplayMainMenu();  		// Volver al menú principal
            break;
    }
}

/********************************************************************************************************************************
 * @brief: Solicitud de contraseña al usuario
 * @param: Recibe funciones, posibilidades: opc1 =(Activate Alarm, DisplayAlarmMenu), opc2= (DeactivateAlarm, IncorrectPassword)
 * @retval: void
********************************************************************************************************************************/
void RequestPassword(void (*onSuccess)(void), void (*onFailure)(void)) {
    while (1) { 											// Bucle para reintentar si la contraseña es incorrecta
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Contrasena:____");
        memset(inputBuffer, 0, sizeof(inputBuffer));		// Re-incializa la variable en [0000]
        inputIndex = 0;

        uint32_t startTime = HAL_GetTick();  				// Guardar el tiempo de inicio

        while (1) {
            if (HAL_GetTick() - startTime > 20000) { 		// Si pasan más de 20 segundos sin entrada
                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print("Tiempo agotado");
                lcd_set_cursor(1, 0);
                lcd_print("Volviendo...");
                while(!delayRead(&LCD_Muestro)){			//Delay 2 segundos
                	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
                }
                DisplayMainMenu();  						// Volver al menú principal
                return;
            }
            key = keypad_getkey();
            if (key != '\0') {
                if (key == '*') {  							// Si presiona "*", vuelve al menú principal
                    lcd_clear();
                    lcd_set_cursor(0, 0);
                    lcd_print("Operacion");
                    lcd_set_cursor(1, 0);
                    lcd_print("Cancelada");
                    while(!delayRead(&LCD_Muestro)){
                    	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
                    }
                    DisplayMainMenu();  					// Volver al menú principal
                    return;
                }
                if (key >= '0' && key <= '9' && inputIndex < 4) {
                    inputBuffer[inputIndex++] = key;
                    lcd_set_cursor(1, 10 + inputIndex - 1);
                    lcd_print("*");
                }else if (key == '#') { 					//  Cuando se presiona "#", verifica la clave
                    inputBuffer[inputIndex] = '\0';
                    if (strcmp(inputBuffer, currentPassword) == 0) {// strcmp compara 2 cadenas de caractares y devuelve un entero =0 si son iguales
                        onSuccess(); // Si la clave es correcta, sale de la función y retorna a la funcion ActivateAlarm
                        return;
                    } else {
                        //  Si la contraseña es incorrecta, mostrar mensaje y volver a pedirla
                        lcd_clear();
                        lcd_set_cursor(0, 0);
                        lcd_print("Contrasena");
                        lcd_set_cursor(1, 0);
                        lcd_print("Incorrecta");
                        while(!delayRead(&LCD_Muestro)){
                        	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
                        }
                        break;  //  Sale de este while pero vuelve al inicio del while externo dentro de RequestPassword
                    }
                }
            }
        }
    }
}

/*****************************************************************************************************************
 * @brief: Activar la alarma
 * @param: void
 * @retval: void
******************************************************************************************************************/
void ActivateAlarm() {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Alarma Activada");
    lcd_set_cursor(1, 0);
    lcd_print("Corran: 20 seg");

    BT_SendMessage("⚠️ Alarma activada. Corran 20s... \r\n");

    uint32_t countdownStart = HAL_GetTick();
    uint32_t remainingTime = 20;

    while (remainingTime > 0) {
        if (HAL_GetTick() - countdownStart >= 1000) {
            countdownStart = HAL_GetTick();
            remainingTime--;

            lcd_set_cursor(1, 7);
            lcd_print("   ");
            lcd_set_cursor(1, 7);
            char buffer[3];
            sprintf(buffer, "%2lu", (unsigned long)remainingTime);
            lcd_print(buffer);

            // Envía el valor del contador por Bluetooth
              char btBuffer[50];
              snprintf(btBuffer, sizeof(btBuffer), "Corran: %02lu seg restantes\r\n", (unsigned long)remainingTime);
              BT_SendMessage(btBuffer);
        }
    }

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Alarma");
    lcd_set_cursor(1, 0);
    lcd_print("Activa!");

    BT_SendMessage("🚨 Alarma activada! \r\n");

    alarmActivated = true;
    currentState = ACTIVE_ALARM;

    while (alarmActivated) {
        key = keypad_getkey();
        if (key != '\0') {
            CheckAlarmDeactivation(key);  // Nueva función para manejar la desactivación con temporizador
        }
        CheckSensors();
    }
}

/*****************************************************************************************************************
 * @brief: Manejar la alarma activa
 * @param: Recibe variable tipo caracter
 * @retval: void
******************************************************************************************************************/
void HandleActiveAlarm(char key) {
    if (key == '#') { 							// Botón para intentar desactivar
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Ingrese");
        lcd_set_cursor(1, 0);
        lcd_print("Contrasena:");
        RequestPassword(DeactivateAlarm, IncorrectPassword);
    }

    //  Verificar si recibe el código de desactivación por Bluetooth
       char btData;
       if (HAL_UART_Receive(&huart2, (uint8_t *)&btData, 1, 100) == HAL_OK) {
           if (btData == '#') {  // Si el usuario envía "#" desde la app, desactiva la alarma
               RequestPassword(DeactivateAlarm, IncorrectPassword);
           }
       }
}

/*****************************************************************************************************************
 * @brief: Desactivar la alarma si la contraseña es correcta
 * @param: void
 * @retval: void
******************************************************************************************************************/
void DeactivateAlarm(void) {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Alarma");
    lcd_set_cursor(1, 0);
    lcd_print("Desactivada");

    BT_SendMessage("✅ Alarma desactivada. Todo en orden. \r\n"); // 🔹 Notificación de desactivación

    alarmActivated = false;

    // Asegurar que el buzzer se apaga
    HAL_GPIO_WritePin(Sirena_GPIO_Port, Sirena_Pin, GPIO_PIN_RESET);
    while(!delayRead(&LCD_Muestro)){
    	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
    }
    DisplayMainMenu();
}

/*****************************************************************************************************************
 * @brief: Contraseña incorrecta: mensaje y reinicio de intento
 * @param: void
 * @retval: void
******************************************************************************************************************/
void IncorrectPassword(void) {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Contrasena");
    lcd_set_cursor(1, 0);
    lcd_print("Incorrecta");
    while(!delayRead(&LCD_Muestro)){ 	// Mostrar mensaje durante 2 segundos

    // Iniciar temporizador interno si aún no está activo
    if (!countdownStarted) {
        countdownStarted = true;
        startTime = HAL_GetTick(); // Guardar tiempo actual
    }

    /*// Iniciar temporizador de 31 segundos si aún no está activo
    	static delay_t countdownDelay;  // Variable estática para mantener el estado del temporizador
    	static bool countdownStarted = false;

    	if (!countdownStarted) {
    		countdownStarted = true;
    		delayInit(&countdownDelay, 31000); // Iniciar temporizador de 31 segundos
    	}
    	*/
    }
    // Solicitar nuevamente la contraseña
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Ingrese");
    lcd_set_cursor(1, 0);
    lcd_print("Contrasena:");
}

/*****************************************************************************************************************
 * @brief: Activar alarma sonora
 * @param: void
 * @retval: void
******************************************************************************************************************/
void AlarmTriggered(void) {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("ALERTA!!!");
    lcd_set_cursor(1, 0);
    lcd_print("Ingrese clave");

    BT_SendMessage("⚠️ Alarma Disparada! \r\n"); // Enviar mensaje por Bluetooth
    uint32_t lastToggleTime = HAL_GetTick();  // Tiempo de referencia para el buzzer

    while (alarmActivated) {
       // Alternar el buzzer cada 500 ms sin bloquear el sistema
    	if (HAL_GetTick() - lastToggleTime >= 500) {
    	    lastToggleTime = HAL_GetTick();
    	    HAL_GPIO_TogglePin(Sirena_GPIO_Port, Sirena_Pin);
    	    HAL_GPIO_TogglePin(Led_Alerta_GPIO_Port, Led_Alerta_Pin);
    	}
    	/*if (delayRead(&Delay_Sirena)){
    		HAL_GPIO_TogglePin(Sirena_GPIO_Port, Sirena_Pin);
    	}*/

        // Permitir que el usuario intente apagar la alarma
        key = keypad_getkey();
        if (key != '\0') {
            RequestPassword(DeactivateAlarm, IncorrectPassword);
        }
    }

    // Apagar el buzzer cuando la alarma se desactiva
    HAL_GPIO_WritePin(Sirena_GPIO_Port, Sirena_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Led_Alerta_GPIO_Port, Led_Alerta_Pin, GPIO_PIN_RESET);
}

/*****************************************************************************************************************
 * @brief: Cambiar contraseña
 * @param: void
 * @retval: void
******************************************************************************************************************/
void DisplayChangePassMenu() {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Contrasena");
    lcd_set_cursor(1, 0);
    lcd_print("Actual:");

    uint32_t startTime = HAL_GetTick();  // Guardar el tiempo actual
    while (1) {  // Bucle para capturar la tecla antes de solicitar la contraseña
        key = keypad_getkey();

        //  Si pasan más de 20 segundos sin tocar una tecla, vuelve al menú principal
        if (HAL_GetTick() - startTime > 20000){
            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("Tiempo Expirado");
            while(!delayRead(&LCD_Muestro)){		//Delay 2 segundos
            	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
            }
            DisplayMainMenu();
            return;
        }

        if (key == '*') {  //  Si el usuario presiona "*", volver al menú principal
            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("Operacion");
            lcd_set_cursor(1, 0);
            lcd_print("Cancelada");
            while(!delayRead(&LCD_Muestro)){		//Delay 2 segundos
            	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
            }
            DisplayMainMenu();
            return;
        }

        if (key != '\0') {  // 🔹 Si presiona otra tecla, salir del bucle y continuar con la contraseña
            break;
        }
    }

    RequestPassword(ConfirmNewPassword, DisplayChangePassMenu);  // Solicitar la contraseña actual
}

/*****************************************************************************************************************
 * @brief:
 * @param:
 * @retval:
******************************************************************************************************************/
void ConfirmNewPassword(){
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Nueva Clave:");

    memset(inputBuffer, 0, sizeof(inputBuffer));
    inputIndex = 0;
    uint32_t startTime = HAL_GetTick();  // Tiempo de inicio para evitar bucles infinitos

    while (HAL_GetTick() - startTime < 20000) {  // Tiempo límite de 20 segundos
        key = keypad_getkey();

        if (key >= '0' && key <= '9' && inputIndex < 4) {
            inputBuffer[inputIndex++] = key;
            lcd_set_cursor(1, inputIndex - 1);
            lcd_print("*");
        } else if (key == '#') {
            if (inputIndex == 4) {  // Validar que la clave tenga 4 dígitos
                inputBuffer[inputIndex] = '\0';
                strcpy(newPassword, inputBuffer);

                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print("Confirmar: ");
                lcd_set_cursor(1, 0);
                lcd_print("*.Si   #.No");

                uint32_t confirmStart = HAL_GetTick();

                while (HAL_GetTick() - confirmStart < 10000) {  			// Espera 10 segundos para confirmar
                    char confirmKey = keypad_getkey();
                    if (confirmKey == '*') {
                        strcpy(currentPassword, newPassword);
                        lcd_clear();
                        lcd_set_cursor(0, 0);
                        lcd_print("Clave Actualizada");
                        while(!delayRead(&LCD_Muestro)){
                                 // Espacio para ejecutar tareas mientras muestra el mensaje anterior
                        }
                        DisplayMainMenu();
                        return;
                    } else if (confirmKey == '#') {
                        ConfirmNewPassword();  				// Volver a solicitar la clave
                        return;
                    }
                }
            } else {
                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print("Debe ser 4 ");
                lcd_set_cursor(1, 0);
                lcd_print("digitos ");
                while(!delayRead(&LCD_Muestro)){
                                	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
                }
                ConfirmNewPassword();  // Reiniciar el proceso
                return;  // Reiniciar el proceso
            }
        }
    }

    // Si el usuario no ingresa nada en 20 segundos, volver al menú principal
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Tiempo ");
    lcd_set_cursor(1, 0);
    lcd_print("Excedido ");
    while(!delayRead(&LCD_Muestro)){
        	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
    }
    DisplayMainMenu();
}

/*****************************************************************************************************************
 * @brief: Submenú "Más"
 * @param:
 * @retval:
******************************************************************************************************************/
void HandleSubMenu() {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("#.Volver ");
    lcd_set_cursor(1, 0);
    lcd_print("3.Prueba");

    while (1) {
        key = keypad_getkey();

        if (key != '\0') {
            if (key == '#') {
                DisplayMainMenu();
                return;
            } else if (key == '3') {
                TestAlarm();
                return;
            }
        }
    }
}

/*****************************************************************************************************************
 * @brief:
 * @param:
 * @retval:
******************************************************************************************************************/
// Prueba de alarma
void TestAlarm() {
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Prueba de");
    lcd_set_cursor(1, 0);
    lcd_print("Alarma...");

    // Activar el buzzer en PA5
    HAL_GPIO_WritePin(Sirena_GPIO_Port, Sirena_Pin, GPIO_PIN_SET);
    while(!delayRead(&LCD_Muestro)){		//Delay 2 segundos
        	// Espacio para ejecutar tareas mientras muestra el mensaje anterior
    }
    HAL_GPIO_WritePin(Sirena_GPIO_Port, Sirena_Pin, GPIO_PIN_RESET);

    HAL_Delay(1000);  // Pequeña pausa antes de volver al menú
    DisplayMainMenu();
}

/*****************************************************************************************************************
 * @brief: Chequeo de sensores
 * @param: void
 * @retval: void
******************************************************************************************************************/
void CheckSensors(void) {
    if (alarmActivated) {
        // Verificar si se abre una puerta o ventana (Sensor_Magnetico_1)
        bool doorOpened_1 = (HAL_GPIO_ReadPin(GPIOA, Sensor_Magnetico_1_Pin) == GPIO_PIN_RESET);
        MotionDetected_1 = false;

        // Verificar si se abre una puerta o ventana (Sensor_Magnetico_2)
        bool doorOpened_2 = (HAL_GPIO_ReadPin(Sensor_Magnetico_2_GPIO_Port, Sensor_Magnetico_2_Pin) == GPIO_PIN_RESET);
        MotionDetected_2 = false;

        // Verificar el sensor PIR si está activado en "Sist Completo"
        if (includeMotionSensor) {
        	MotionDectected_PIR = HAL_GPIO_ReadPin(GPIOA, Sensor_PIR_Pin);

            // Filtro por software para evitar falsas detecciones
            HAL_Delay(50);
            if (HAL_GPIO_ReadPin(GPIOA, Sensor_PIR_Pin) != MotionDectected_PIR) {
            	MotionDectected_PIR = false; // Ignorar si el estado cambió muy rápido
            }
        }

        // Evaluar si se debe activar la alarma
        if (doorOpened_1 || doorOpened_2 || (includeMotionSensor && MotionDectected_PIR)) {
            AlarmTriggered();
        }
    }
}


/*****************************************************************************************************************
 * @brief:
 * @param:
 * @retval:
******************************************************************************************************************/
void CheckAlarmDeactivation(char key) {
	//static delay_t countdownDelay;
	static bool countdownStarted = false;

	if (!countdownStarted) {
		countdownStarted = true;
		startTime = HAL_GetTick(); // Iniciar temporizador de 31 segundos
	}

	RequestPassword(DeactivateAlarm, IncorrectPassword);

	// Si pasan 31 segundos sin ingresar la clave correcta, activar la alarma
	if (HAL_GetTick() - startTime >= 31000) {
		AlarmTriggered();
	}
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
