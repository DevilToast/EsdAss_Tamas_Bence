#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <ps.h>
#include <xtimer.h>
#include <thread.h>
#include "periph/gpio.h"

pthread_mutex_t dataMutex;
pthread_cond_t conditionInputReady;

typedef struct pipeInputBridge_t {
	int in1;
	int in2;
} pipeInputBridge_t;

typedef int pipeOutputBridge_t;

pipeInputBridge_t inputBridge;
pipeOutputBridge_t outputBridge;

xtimer_t inputTimer;
xtimer_t outputTimer;

void handleInput(void* arg) {
	(void)arg;
	xtimer_set(&inputTimer, 500);

	//static uint32_t oldTime = 0;
	//uint32_t newTime = xtimer_now_usec();
	//printf("Handle input period: %d", newTime - oldTime);
	//oldTime = newTime;	
	
	pthread_mutex_lock(&dataMutex);

	inputBridge.in1 = gpio_read(GPIO_PIN(PORT_A, 1));
	inputBridge.in2 = gpio_read(GPIO_PIN(PORT_A, 5));

	pthread_cond_signal(&conditionInputReady);
	pthread_mutex_unlock(&dataMutex);
}

void handleData() {
	pthread_mutex_lock(&dataMutex);
	pthread_cond_wait(&conditionInputReady, &dataMutex);
	outputBridge = inputBridge.in1 || inputBridge.in2;
	xtimer_usleep(250);
	pthread_mutex_unlock(&dataMutex);
}

void handleOutput(void* arg) {
	(void)arg;
	xtimer_set(&outputTimer, 500);

	if (outputBridge) {
		gpio_clear(GPIO_PIN(PORT_A, 4));
	} else {
		gpio_set(GPIO_PIN(PORT_A, 4));
	}
}

void initGPIO() {
	gpio_init(GPIO_PIN(PORT_A, 1), GPIO_IN_PU); 
	gpio_init(GPIO_PIN(PORT_A, 5), GPIO_IN_PU);
	gpio_init(GPIO_PIN(PORT_A, 4), GPIO_OUT);
}

void initTimers() {
	inputTimer.callback = handleInput;
	inputTimer.target = 0;
	inputTimer.long_target = 0;
	
	outputTimer.callback = handleOutput;
	outputTimer.target = 0;
	outputTimer.long_target = 0;
}

int main(void)
{
	initGPIO();
	initTimers();
	xtimer_init();
	
	pthread_mutex_init(&dataMutex, NULL);
	pthread_cond_init (&conditionInputReady, NULL);	

	printf("Running And Gate example!\n");

	xtimer_set(&inputTimer, 0);
	xtimer_set(&outputTimer, 0);

	while(1) {
		handleData();
	}	
	
	return 0;
}
