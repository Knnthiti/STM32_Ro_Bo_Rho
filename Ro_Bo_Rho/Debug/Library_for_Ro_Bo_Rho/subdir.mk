################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library_for_Ro_Bo_Rho/Encoder_Motor.c \
../Library_for_Ro_Bo_Rho/Forward_Kinematics.c \
../Library_for_Ro_Bo_Rho/Game_Play.c \
../Library_for_Ro_Bo_Rho/Inverse_Kinematics.c \
../Library_for_Ro_Bo_Rho/MPU6050.c \
../Library_for_Ro_Bo_Rho/Ramp_Robot.c \
../Library_for_Ro_Bo_Rho/app_ros_comm.c 

OBJS += \
./Library_for_Ro_Bo_Rho/Encoder_Motor.o \
./Library_for_Ro_Bo_Rho/Forward_Kinematics.o \
./Library_for_Ro_Bo_Rho/Game_Play.o \
./Library_for_Ro_Bo_Rho/Inverse_Kinematics.o \
./Library_for_Ro_Bo_Rho/MPU6050.o \
./Library_for_Ro_Bo_Rho/Ramp_Robot.o \
./Library_for_Ro_Bo_Rho/app_ros_comm.o 

C_DEPS += \
./Library_for_Ro_Bo_Rho/Encoder_Motor.d \
./Library_for_Ro_Bo_Rho/Forward_Kinematics.d \
./Library_for_Ro_Bo_Rho/Game_Play.d \
./Library_for_Ro_Bo_Rho/Inverse_Kinematics.d \
./Library_for_Ro_Bo_Rho/MPU6050.d \
./Library_for_Ro_Bo_Rho/Ramp_Robot.d \
./Library_for_Ro_Bo_Rho/app_ros_comm.d 


# Each subdirectory must supply rules for building sources it contributes
Library_for_Ro_Bo_Rho/%.o Library_for_Ro_Bo_Rho/%.su Library_for_Ro_Bo_Rho/%.cyclo: ../Library_for_Ro_Bo_Rho/%.c Library_for_Ro_Bo_Rho/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Users/Knnn/STM32CubeIDE/workspace_1.15.1/mark_1.zip_expanded/Ro_Bo_Rho/Library_for_Ro_Bo_Rho" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library_for_Ro_Bo_Rho

clean-Library_for_Ro_Bo_Rho:
	-$(RM) ./Library_for_Ro_Bo_Rho/Encoder_Motor.cyclo ./Library_for_Ro_Bo_Rho/Encoder_Motor.d ./Library_for_Ro_Bo_Rho/Encoder_Motor.o ./Library_for_Ro_Bo_Rho/Encoder_Motor.su ./Library_for_Ro_Bo_Rho/Forward_Kinematics.cyclo ./Library_for_Ro_Bo_Rho/Forward_Kinematics.d ./Library_for_Ro_Bo_Rho/Forward_Kinematics.o ./Library_for_Ro_Bo_Rho/Forward_Kinematics.su ./Library_for_Ro_Bo_Rho/Game_Play.cyclo ./Library_for_Ro_Bo_Rho/Game_Play.d ./Library_for_Ro_Bo_Rho/Game_Play.o ./Library_for_Ro_Bo_Rho/Game_Play.su ./Library_for_Ro_Bo_Rho/Inverse_Kinematics.cyclo ./Library_for_Ro_Bo_Rho/Inverse_Kinematics.d ./Library_for_Ro_Bo_Rho/Inverse_Kinematics.o ./Library_for_Ro_Bo_Rho/Inverse_Kinematics.su ./Library_for_Ro_Bo_Rho/MPU6050.cyclo ./Library_for_Ro_Bo_Rho/MPU6050.d ./Library_for_Ro_Bo_Rho/MPU6050.o ./Library_for_Ro_Bo_Rho/MPU6050.su ./Library_for_Ro_Bo_Rho/Ramp_Robot.cyclo ./Library_for_Ro_Bo_Rho/Ramp_Robot.d ./Library_for_Ro_Bo_Rho/Ramp_Robot.o ./Library_for_Ro_Bo_Rho/Ramp_Robot.su ./Library_for_Ro_Bo_Rho/app_ros_comm.cyclo ./Library_for_Ro_Bo_Rho/app_ros_comm.d ./Library_for_Ro_Bo_Rho/app_ros_comm.o ./Library_for_Ro_Bo_Rho/app_ros_comm.su

.PHONY: clean-Library_for_Ro_Bo_Rho

