################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/ExampleProtocol.cc \
../src/Pinger.cc \
../src/Ponger.cc \
../src/Top.cc \
../src/TopControllers.cc \
../src/TopMain.cc 

O_SRCS += \
../src/ExampleProtocol.o \
../src/Pinger.o \
../src/Ponger.o \
../src/Top.o \
../src/TopControllers.o \
../src/TopMain.o 

CC_DEPS += \
./src/ExampleProtocol.d \
./src/Pinger.d \
./src/Ponger.d \
./src/Top.d \
./src/TopControllers.d \
./src/TopMain.d 

OBJS += \
./src/ExampleProtocol.o \
./src/Pinger.o \
./src/Ponger.o \
./src/Top.o \
./src/TopControllers.o \
./src/TopMain.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/tamas/Documents/Papyrus-RT/plugins/org.eclipse.papyrusrt.rts_1.0.0.201707181457/umlrts/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


