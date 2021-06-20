################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board.c \
../src/main.c \
../src/setups.c \
../src/stm32f1xx_it.c \
../src/syscalls.c \
../src/system_stm32f1xx.c \
../src/ultrasounds.c 

OBJS += \
./src/board.o \
./src/main.o \
./src/setups.o \
./src/stm32f1xx_it.o \
./src/syscalls.o \
./src/system_stm32f1xx.o \
./src/ultrasounds.o 

C_DEPS += \
./src/board.d \
./src/main.d \
./src/setups.d \
./src/stm32f1xx_it.d \
./src/syscalls.d \
./src/system_stm32f1xx.d \
./src/ultrasounds.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103RBTx -DNUCLEO_F103RB -DSTM32F103xB -DUSE_HAL_DRIVER -I"C:/Users/piran/workspace/AutonomousRobotProgram/HAL_Driver/Inc/Legacy" -I"C:/Users/piran/workspace/AutonomousRobotProgram/Utilities/STM32F1xx_Nucleo" -I"C:/Users/piran/workspace/AutonomousRobotProgram/inc" -I"C:/Users/piran/workspace/AutonomousRobotProgram/CMSIS/device" -I"C:/Users/piran/workspace/AutonomousRobotProgram/CMSIS/core" -I"C:/Users/piran/workspace/AutonomousRobotProgram/HAL_Driver/Inc" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


