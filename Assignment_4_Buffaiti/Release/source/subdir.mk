################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Assignment_4_Buffaiti.c \
../source/cap_sensor.c \
../source/led.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/statemachine.c \
../source/switch.c \
../source/temp_systick.c 

OBJS += \
./source/Assignment_4_Buffaiti.o \
./source/cap_sensor.o \
./source/led.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/statemachine.o \
./source/switch.o \
./source/temp_systick.o 

C_DEPS += \
./source/Assignment_4_Buffaiti.d \
./source/cap_sensor.d \
./source/led.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/statemachine.d \
./source/switch.d \
./source/temp_systick.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -DPRODUCTION -I"/home/arpit/studies/pes/Assignment_4_Buffaiti/board" -I"/home/arpit/studies/pes/Assignment_4_Buffaiti/source" -I"/home/arpit/studies/pes/Assignment_4_Buffaiti" -I"/home/arpit/studies/pes/Assignment_4_Buffaiti/drivers" -I"/home/arpit/studies/pes/Assignment_4_Buffaiti/CMSIS" -I"/home/arpit/studies/pes/Assignment_4_Buffaiti/utilities" -I"/home/arpit/studies/pes/Assignment_4_Buffaiti/startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


