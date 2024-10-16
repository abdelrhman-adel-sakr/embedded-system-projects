################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../LED.c \
../gpio.c \
../icu.c \
../lcd.c \
../main.c \
../ultrasonic.c 

OBJS += \
./Buzzer.o \
./LED.o \
./gpio.o \
./icu.o \
./lcd.o \
./main.o \
./ultrasonic.o 

C_DEPS += \
./Buzzer.d \
./LED.d \
./gpio.d \
./icu.d \
./lcd.d \
./main.d \
./ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


