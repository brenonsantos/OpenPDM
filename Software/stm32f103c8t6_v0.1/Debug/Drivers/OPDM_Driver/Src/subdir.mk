################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/OPDM_Driver/Src/opdm_hal_io.c 

OBJS += \
./Drivers/OPDM_Driver/Src/opdm_hal_io.o 

C_DEPS += \
./Drivers/OPDM_Driver/Src/opdm_hal_io.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/OPDM_Driver/Src/%.o Drivers/OPDM_Driver/Src/%.su Drivers/OPDM_Driver/Src/%.cyclo: ../Drivers/OPDM_Driver/Src/%.c Drivers/OPDM_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/OPDM_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-OPDM_Driver-2f-Src

clean-Drivers-2f-OPDM_Driver-2f-Src:
	-$(RM) ./Drivers/OPDM_Driver/Src/opdm_hal_io.cyclo ./Drivers/OPDM_Driver/Src/opdm_hal_io.d ./Drivers/OPDM_Driver/Src/opdm_hal_io.o ./Drivers/OPDM_Driver/Src/opdm_hal_io.su

.PHONY: clean-Drivers-2f-OPDM_Driver-2f-Src

