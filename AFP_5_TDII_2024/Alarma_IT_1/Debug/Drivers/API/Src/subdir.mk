################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_BT.c \
../Drivers/API/Src/API_Debounce.c \
../Drivers/API/Src/API_Delay.c \
../Drivers/API/Src/API_GPIO.c \
../Drivers/API/Src/API_Keypad.c \
../Drivers/API/Src/API_LCD.c \
../Drivers/API/Src/API_Teclado4x3.c 

OBJS += \
./Drivers/API/Src/API_BT.o \
./Drivers/API/Src/API_Debounce.o \
./Drivers/API/Src/API_Delay.o \
./Drivers/API/Src/API_GPIO.o \
./Drivers/API/Src/API_Keypad.o \
./Drivers/API/Src/API_LCD.o \
./Drivers/API/Src/API_Teclado4x3.o 

C_DEPS += \
./Drivers/API/Src/API_BT.d \
./Drivers/API/Src/API_Debounce.d \
./Drivers/API/Src/API_Delay.d \
./Drivers/API/Src/API_GPIO.d \
./Drivers/API/Src/API_Keypad.d \
./Drivers/API/Src/API_LCD.d \
./Drivers/API/Src/API_Teclado4x3.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Mis Cosas/Ingenieria/OneDrive - frt.utn.edu.ar/Repos/AFP_5_GRUPO_8_2024/Alarma_IT_1/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_BT.cyclo ./Drivers/API/Src/API_BT.d ./Drivers/API/Src/API_BT.o ./Drivers/API/Src/API_BT.su ./Drivers/API/Src/API_Debounce.cyclo ./Drivers/API/Src/API_Debounce.d ./Drivers/API/Src/API_Debounce.o ./Drivers/API/Src/API_Debounce.su ./Drivers/API/Src/API_Delay.cyclo ./Drivers/API/Src/API_Delay.d ./Drivers/API/Src/API_Delay.o ./Drivers/API/Src/API_Delay.su ./Drivers/API/Src/API_GPIO.cyclo ./Drivers/API/Src/API_GPIO.d ./Drivers/API/Src/API_GPIO.o ./Drivers/API/Src/API_GPIO.su ./Drivers/API/Src/API_Keypad.cyclo ./Drivers/API/Src/API_Keypad.d ./Drivers/API/Src/API_Keypad.o ./Drivers/API/Src/API_Keypad.su ./Drivers/API/Src/API_LCD.cyclo ./Drivers/API/Src/API_LCD.d ./Drivers/API/Src/API_LCD.o ./Drivers/API/Src/API_LCD.su ./Drivers/API/Src/API_Teclado4x3.cyclo ./Drivers/API/Src/API_Teclado4x3.d ./Drivers/API/Src/API_Teclado4x3.o ./Drivers/API/Src/API_Teclado4x3.su

.PHONY: clean-Drivers-2f-API-2f-Src

