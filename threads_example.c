#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define WORK_SIZE 1024

void *thread_function(void *arg);

pthread_mutex_t counter;  
int r,n1,n2,x;


int main() {
   
   int i = 0, j = 0;
   int res;
   scanf("%d %d\n",&n1,&n2);
   pthread_t a_thread;
   void *thread_result;
   res = pthread_mutex_init(&counter, NULL);
   if (res != 0) {
      perror("Error Mutex initialization");
      exit(EXIT_FAILURE);
   }
   res = pthread_create(&a_thread, NULL, thread_function, NULL);
   if (res != 0) {
      perror("Error create Thread");
      exit(EXIT_FAILURE);
   }
   pthread_mutex_lock(&counter);
   
   for (i=0; i<10000; i++){
	for (j=0; j<i; j++){
		x = i - j;
	}
   }r = n1 + n2;
   
   pthread_mutex_unlock(&counter);
   res = pthread_join(a_thread, &thread_result);
   if (res != 0) {
      perror("Error join Thread");
      exit(EXIT_FAILURE);
   }
   printf("R: %d\n",r);
   pthread_mutex_destroy(&counter);
   exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
   int j = 0, i = 0;
   sleep(1);
   pthread_mutex_lock(&counter);

   for (i=0; i<10000; i++){
	for (j=0; j<i; j++){
		x = i - j;
	}
   }r = n1 - n2;
   pthread_mutex_unlock(&counter);
   pthread_exit(0);
}
