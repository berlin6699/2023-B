################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tjc_usart/tjc_usart_hmi.c 

OBJS += \
./tjc_usart/tjc_usart_hmi.o 

C_DEPS += \
./tjc_usart/tjc_usart_hmi.d 


# Each subdirectory must supply rules for building sources it contributes
tjc_usart/%.o tjc_usart/%.su tjc_usart/%.cyclo: ../tjc_usart/%.c tjc_usart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../CMSIS_DSP/Include -I../ADS8688 -I../tjc_usart -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-tjc_usart

clean-tjc_usart:
	-$(RM) ./tjc_usart/tjc_usart_hmi.cyclo ./tjc_usart/tjc_usart_hmi.d ./tjc_usart/tjc_usart_hmi.o ./tjc_usart/tjc_usart_hmi.su

.PHONY: clean-tjc_usart

