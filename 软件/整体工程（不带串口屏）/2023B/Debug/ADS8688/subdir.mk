################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADS8688/ADS8688.c 

OBJS += \
./ADS8688/ADS8688.o 

C_DEPS += \
./ADS8688/ADS8688.d 


# Each subdirectory must supply rules for building sources it contributes
ADS8688/%.o ADS8688/%.su ADS8688/%.cyclo: ../ADS8688/%.c ADS8688/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../CMSIS_DSP/Include -I../ADS8688 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ADS8688

clean-ADS8688:
	-$(RM) ./ADS8688/ADS8688.cyclo ./ADS8688/ADS8688.d ./ADS8688/ADS8688.o ./ADS8688/ADS8688.su

.PHONY: clean-ADS8688

