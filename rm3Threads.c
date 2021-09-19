/*
 * main.c
 *
 *  Created on: 2014
 *      Author: Vidblain
 *
 *  gcc monotonicThreads.c -o monotonicThreads.o -lrt -lpthread
 *  ./monotonicThreads.o
 */

#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "times.h"

#define MAX_SAFE_STACK (8*1024) /* The maximum stack size which is
                                   guranteed safe to access without
                                   faulting */

struct timespec initialTime;

void setaffinity(int cpu);
void * inThread(void *args);
void * prThread(void *args);
void * ouThread(void *args);
void stack_prefault(void);
void timespec_add_us(struct timespec *t, long us);
int timespec_cmp(struct timespec *a, struct timespec *b);
	
int main(int argc, char **argv) {
	/*Declare variables*/
	pthread_t in,  pr, out;
	pthread_attr_t inAttr, prAttr, ouAttr;
	int fifo_min_priority, fifo_max_priority;

	struct sched_param param1, param2, param3;
	int status;
	
	struct timespec t = {0,0};
	struct timespec clock_resolution = {-1,-1};

	clock_gettime(CLOCK_MONOTONIC,&clock_resolution);
	printf("Clock resolution is %ld seconds, %06ld nanoseconds\n",clock_resolution.tv_sec, clock_resolution.tv_nsec);
	
	/* Lock memory */
	if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
		perror("mlockall failed");
       	exit(-2);
   	}
   	/* Pre-fault our stack */
   	stack_prefault();

	status = pthread_attr_init(&inAttr);
	if (status != 0) {
		perror("Init attr1");
		exit(2);
	}
	status = pthread_attr_setinheritsched(&inAttr,PTHREAD_EXPLICIT_SCHED);
	if (status != 0) {
		perror("EXPLICIT attr1");
		exit(2);
	}
	
	status = pthread_attr_init(&prAttr);
	if (status != 0) {
		perror("Init attr2");
		exit(2);
	}
	status = pthread_attr_setinheritsched(&prAttr,PTHREAD_EXPLICIT_SCHED);
	if (status != 0) {
		perror("EXPLICIT attr2");
		exit(2);
	}
	
	status = pthread_attr_init(&ouAttr);
	if (status != 0) {
		perror("Init attr3");
		exit(2);
	}
	status = pthread_attr_setinheritsched(&ouAttr,PTHREAD_EXPLICIT_SCHED);
	if (status != 0) {
		perror("EXPLICIT attr3");
		exit(2);
	}
	

#if defined (_POSIX_THREAD_PRIORITY_SCHEDULING) && !defined (sun)
	status = pthread_attr_setschedpolicy(&inAttr, SCHED_FIFO);
	if (status != 0) {
		perror("Unable to set SCHED_FIFO policy to Thread 1.\n");
		exit(1);
	}
	
	status = pthread_attr_setschedpolicy(&prAttr, SCHED_FIFO);
	if (status != 0) {
		perror("Unable to set SCHED_FIFO policy to Thread 2.\n");
		exit(1);
	}
	
	status = pthread_attr_setschedpolicy(&ouAttr, SCHED_FIFO);
	if (status != 0) {
		perror("Unable to set SCHED_FIFO policy to Thread 3.\n");
		exit(1);
	} else {
		fifo_min_priority = sched_get_priority_min(SCHED_FIFO);
		if (fifo_min_priority == -1) {
			perror("Get SCHED_FIFO min priority");
			exit(1);
		}
		fifo_max_priority = sched_get_priority_max(SCHED_FIFO);
		if (fifo_max_priority == -1) {
			perror("Get SCHED_FIFO max priority");
			exit(1);
		}
		
		printf("MAX: %d\nMIN: %d\n",fifo_max_priority,fifo_min_priority);

		param1.sched_priority = 97;
		param2.sched_priority = 98;
		param3.sched_priority = 99;
		
		//t.tv_nsec = 700000000;
		//param1.sched_rel_deadline = t;
		status = pthread_attr_setschedparam(&inAttr, &param1);
		if (status != 0) {
			perror("Unable to set params to Thread 1.\n");
		}
		printf("SCHED_PARAM 1\n");
		
		//t.tv_nsec = 600000000;
		//param2.sched_rel_deadline = t;
		status = pthread_attr_setschedparam(&prAttr, &param2);
		if (status != 0) {
			perror("Unable to set params to Thread 2.\n");
		}
		printf("SCHED_PARAM 2\n");
		
		//t.tv_nsec = 400000000;
		//param3.sched_rel_deadline = t;
		status = pthread_attr_setschedparam(&ouAttr, &param3);
		if (status != 0) {
			perror("Unable to set params to Thread 3.\n");
		}
		printf("SCHED_PARAM 3\n");
	}
#else
	printf("Priority scheduling not supported\n");
#endif

	printf("--------------------------\n");

	//setaffinity(0);
	
	initialTime = clock_resolution;
	initialTime.tv_sec = initialTime.tv_sec + 2;
	
	/* Create threads*/
	printf("THREAD CREATE BEFORE\n");
	pthread_create(&in, &inAttr, (void *) &inThread, NULL);
	printf("THREAD CREATE 1\n");
	pthread_create(&pr, &prAttr, (void *) &prThread, NULL);
	printf("THREAD CREATE 2\n");
	pthread_create(&out, &ouAttr, (void *) &ouThread, NULL);
	printf("THREAD CREATE 3\n");
	pthread_join(in, NULL);
	pthread_join(pr, NULL);
	pthread_join(out, NULL);
	printf("MAIN THREAD FINISHED 2\n");
	pthread_exit(NULL);
}

void stack_prefault(void) {
	unsigned char dummy[MAX_SAFE_STACK];
    memset(&dummy, 0, MAX_SAFE_STACK);
    return;
}

void setaffinity(int cpu) {
	struct sched_param sched_param;
	//struct timespec rel={0,0};
	cpu_set_t mask;

	CPU_ZERO(&mask);
	CPU_SET(cpu, &mask);
	printf("AFFINITY BEFORE\n");
	if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
		perror("Coult not set affinity");
	}
	printf("AFFINITY LATER\n");
	//printf("--------------------------\n");
	//if (sched_getparam(0, &sched_param) < 0) {
		//printf("Scheduler getparam failed...\n");
		//return;
	//}
	//sched_param.sched_priority = priority;
	//sched_param.sched_rel_deadline = rel;
	//if (!sched_setscheduler(0, SCHED_FIFO, &sched_param)) {
		//printf("Scheduler set to FIFO with priority %i...\n",
				//sched_param.sched_priority);
		//return;
	//}
	//printf("!!!Scheduler set to FIFO with priority %i FAILED!!!\n",
			//sched_param.sched_priority);
}

void timespec_add_us(struct timespec *t, long us) {
	t->tv_nsec += us*1000;
	if (t->tv_nsec > 1000000000) {
		t->tv_nsec = t->tv_nsec - 1000000000;// + ms*1000000;
		t->tv_sec += 1;
	}
}

int timespec_cmp(struct timespec *a, struct timespec *b) {
	if (a->tv_sec > b->tv_sec) return 1;
		else if (a->tv_sec < b->tv_sec) return -1;
		else if (a->tv_sec == b->tv_sec) {
			if (a->tv_nsec > b->tv_nsec) return 1;
			else if (a->tv_nsec == b->tv_nsec) return 0;
			else return -1;
		}
}

void * inThread(void *args) {
	/* Entry for inThread */
	/* Create variables */
	struct timespec periodActivation, nextActivation, now;
	int period_time,i,j,k,x;
	int count=0;
	double y;
	
	period_time=700000000;
	periodActivation.tv_sec = 0;
	periodActivation.tv_nsec = period_time;
	
	//clock_gettime(CLOCK_MONOTONIC, &nextActivation);
	//nextActivation.tv_sec++;
	nextActivation = initialTime;
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextActivation, NULL);	
	
	for (i=0; i<=700; i++)
		  for (j=i; j<=550; j++)
		    for (k=1; k<=500; k++){
		       x=5000+700+600;
			}
	count++;

	while (count<24) {
		clock_gettime(CLOCK_MONOTONIC, &now);
		//timespec_add_us(&nextActivation, &periodActivation);
		timespec_add(&nextActivation, &periodActivation);
		//if (timespec_cmp(&now, &nextActivation) > 0) {
			//fprintf(stderr, "Thread 1 now: %d sec %ld nsec next: %d sec %ldnsec \n",
			//now.tv_sec, now.tv_nsec, nextActivation.tv_sec, nextActivation.tv_nsec);
			//exit(-1);
		//}
		/*
		 * Se "desactiva" al thread hasta el siguiente periodo
		 */
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextActivation, NULL);
		
		for (i=0; i<=700; i++)
		  for (j=i; j<=550; j++)
		    for (k=1; k<=500; k++){
		       x=5000+700+600;
		   }
		/*
		 * Incrementamos contador
		 */
		count++;
		/*
		 * Se define el instante de la siguiente activacion: tiempo de la activacion mas periodo
		 */
		//timespec_add(&nextActivation, &periodActivation);
	}
	
	pthread_exit(NULL);
}

void * prThread(void *args) {
	/* Entry for prThread */
	/* Create variables */
	struct timespec periodActivation, nextActivation, now;
	int period_time,i,j,k,x;
	int count=0;
	
	period_time=600000000;
	periodActivation.tv_sec = 0;
	periodActivation.tv_nsec = period_time;
	
	//clock_gettime(CLOCK_MONOTONIC, &nextActivation);
	//nextActivation.tv_sec++;
	nextActivation = initialTime;
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextActivation, NULL);
	
	for (i=0; i<=500; i++)
		  for (j=i; j<=400; j++)
		    for (k=1; k<=300; k++)
		       x=5000+700+600;
	count++;

	while (count<28) {
		clock_gettime(CLOCK_MONOTONIC, &now);
		//timespec_add_us(&nextActivation, &periodActivation);
		timespec_add(&nextActivation, &periodActivation);
		//if (timespec_cmp(&now, &nextActivation) > 0) {
			//fprintf(stderr, "Thread 2 now: %d sec %ld nsec next: %d sec %ldnsec \n",
			//now.tv_sec, now.tv_nsec, nextActivation.tv_sec, nextActivation.tv_nsec);
			//exit(-1);
		//}
		/*
		 * Se "desactiva" al thread hasta el siguiente periodo
		 */
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextActivation, NULL);
		
		for (i=0; i<=500; i++)
		  for (j=i; j<=400; j++)
		    for (k=1; k<=300; k++)
		       x=5000+700+600;
		/*
		 * Incrementamos contador
		 */
		count++;
		/*
		 * Se define el instante de la siguiente activacion: tiempo de la activacion mas periodo
		 */
		//timespec_add(&nextActivation, &periodActivation);
	}
	
	pthread_exit(NULL);
}

void * ouThread(void *args) {
	/* Entry for inThread */
	/* Create variables */
	struct timespec periodActivation, nextActivation, now;
	int period_time,i,j,k,x;
	int count=0;
	
	period_time=400000000;
	periodActivation.tv_sec = 0;
	periodActivation.tv_nsec = period_time;
	
	//clock_gettime(CLOCK_MONOTONIC, &nextActivation);
	//nextActivation.tv_sec++;
	nextActivation = initialTime;
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &initialTime, NULL);
	
	for (i=0; i<=700; i++)
		  for (j=i; j<=600; j++)
		    for (k=1; k<=500; k++)
		       x=5000+700+600;
	count++;
	
	while (count<42) {
		clock_gettime(CLOCK_MONOTONIC, &now);
		//timespec_add_us(&nextActivation, &periodActivation);
		timespec_add(&nextActivation, &periodActivation);
		//if (timespec_cmp(&now, &nextActivation) > 0) {
			//fprintf(stderr, "now: %d sec %ld nsec next: %d sec %ldnsec \n",
			//now.tv_sec, now.tv_nsec, nextActivation.tv_sec, nextActivation.tv_nsec);
			//exit(-1);
		//}
		/*
		 * Se "desactiva" al thread hasta el siguiente periodo
		 */
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextActivation, NULL);
		
		for (i=0; i<=700; i++)
		  for (j=i; j<=600; j++)
		    for (k=1; k<=500; k++)
		       x=5000+700+600;
		/*
		 * Incrementamos contador
		 */
		count++;
		/*
		 * Se define el instante de la siguiente activacion: tiempo de la activacion mas periodo
		 */
		//timespec_add(&nextActivation, &periodActivation);
	}
	
	pthread_exit(NULL);
}
