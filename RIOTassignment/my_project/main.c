#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <ps.h>
#include <xtimer.h>
//#include <thread.h>

pthread_mutex_t dataMutex;
pthread_cond_t conditionInputReady;

typedef struct AndGate_t {
	int in1;
	int in2;
	int out;
} AndGate_t;

AndGate_t andGate;
int sysInput1 = 0;
int sysInput2 = 0;
int sysOutput = 0;

void setSystemInputs(int aIn1, int aIn2) {
	sysInput1 = aIn1;
	sysInput2 = aIn2;
	printf("System inputs set to %d and %d\n", aIn1, aIn2);
}

void* handleData(void* arg);

void* handleInput(void* arg) {
	(void)arg;
	while(1) {
		pthread_mutex_lock(&dataMutex);
	
		andGate.in1 = sysInput1;
		andGate.in2 = sysInput2;
		printf("Inputs %d and %d loaded into And Gate\n", sysInput1, sysInput2);
		pthread_cond_signal(&conditionInputReady);
		pthread_mutex_unlock(&dataMutex);
		xtimer_sleep(1);
	}
	

}

void* handleData(void* arg) {
	(void)arg;
	while(1) {
		pthread_mutex_lock(&dataMutex);
		pthread_cond_wait(&conditionInputReady, &dataMutex);
		andGate.out = andGate.in1 & andGate.in2;
		xtimer_usleep(250);
		printf("Output computed: %d\n", andGate.out);

		pthread_mutex_unlock(&dataMutex);
	}
}

void* handleOutput(void* arg) {
	(void)arg;
	while(1) {
		sysOutput = andGate.out;
		printf("Load output with %d\n", sysOutput);
		xtimer_sleep(1);
	}	
}

int main(void)
{
	(void) puts("Welcome to RIOT!");

	printf("Running And Gate example!\n");

	setSystemInputs(1, 1);	
	pthread_t threads[3];

	/* Initialize mutex and condition variable objects */
	pthread_mutex_init(&dataMutex, NULL);
	pthread_cond_init (&conditionInputReady, NULL);
	
	int ret = 0;
	
	//pthread_attr_t tattr;
	//pthread_attr_init (&tattr);
	//struct sched_param param;
	//param.sched_priority = 6;
	//pthread_attr_setschedparam (&tattr, &param);

	ret = pthread_create(&threads[0], NULL, handleInput, NULL);
	printf("Thread1 creation return value: %d\n", ret);
	printf("Thread Id: %d\n", threads[0]);
	pthread_create(&threads[1], NULL, handleData, NULL);
	printf("Thread2 creation return value: %d\n", ret);
	printf("Thread Id: %d\n", threads[1]);
	pthread_create(&threads[2], NULL, handleOutput, NULL);
	printf("Thread3 creation return value: %d\n", ret);
	printf("Thread Id: %d\n", threads[2]);

	pthread_cancel(threads[0]);	

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);


	/* Clean up and exit */
	pthread_mutex_destroy(&dataMutex);
	pthread_cond_destroy(&conditionInputReady);
	pthread_exit (NULL);

	return 0;
}
