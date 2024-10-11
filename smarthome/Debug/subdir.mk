################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../Buzzer.c \
../DCmotor.c \
../LCD.c \
../LDR.c \
../LED.c \
../PWM.c \
../flamesensor.c \
../gpio.c \
../lm35_sensor.c \
../main.c \
../smarthome.c 

OBJS += \
./ADC.o \
./Buzzer.o \
./DCmotor.o \
./LCD.o \
./LDR.o \
./LED.o \
./PWM.o \
./flamesensor.o \
./gpio.o \
./lm35_sensor.o \
./main.o \
./smarthome.o 

C_DEPS += \
./ADC.d \
./Buzzer.d \
./DCmotor.d \
./LCD.d \
./LDR.d \
./LED.d \
./PWM.d \
./flamesensor.d \
./gpio.d \
./lm35_sensor.d \
./main.d \
./smarthome.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


