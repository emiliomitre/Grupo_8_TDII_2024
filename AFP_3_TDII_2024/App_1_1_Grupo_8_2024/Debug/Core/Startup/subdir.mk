################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f413zhtx.s 

OBJS += \
./Core/Startup/startup_stm32f413zhtx.o 

S_DEPS += \
./Core/Startup/startup_stm32f413zhtx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/STM32WorkSpace/App_1_1_Grupo_8_2024/Drivers/API/Inc" -I"D:/STM32WorkSpace/App_1_1_Grupo_8_2024/Drivers/API/Src" -I"D:/STM32WorkSpace/App_1_1_Grupo_8_2024/Drivers" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f413zhtx.d ./Core/Startup/startup_stm32f413zhtx.o

.PHONY: clean-Core-2f-Startup
