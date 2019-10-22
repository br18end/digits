#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define WORK_SIZE 1024

void *thread_function(void *arg);

pthread_mutex_t contador;  
int r,n1,n2,x;


int main() {
   
   int i = 0, j = 0;
   int res;
   scanf("%d %d\n",&n1,&n2);
   pthread_t a_thread;
   void *thread_result;
   res = pthread_mutex_init(&contador, NULL);
   if (res != 0) {
      perror("Fallo al iniciar el Mutex initialization");
      exit(EXIT_FAILURE);
   }
   res = pthread_create(&a_thread, NULL, thread_function, NULL);
   if (res != 0) {
      perror("Fallo en la creacion del Thread");
      exit(EXIT_FAILURE);
   }
   pthread_mutex_lock(&contador);
   
   for (i=0; i<10000; i++){
	for (j=0; j<i; j++){
		x = i - j;
	}
   }r = n1 + n2;
   
   pthread_mutex_unlock(&contador);
   res = pthread_join(a_thread, &thread_result);
   if (res != 0) {
      perror("Fallo en el join del Thread");
      exit(EXIT_FAILURE);
   }
   printf("R: %d\n",r);
   pthread_mutex_destroy(&contador);
   exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
   int j = 0, i = 0;
   sleep(1);
   pthread_mutex_lock(&contador);

   for (i=0; i<10000; i++){
	for (j=0; j<i; j++){
		x = i - j;
	}
   }r = n1 - n2;
   pthread_mutex_unlock(&contador);
   pthread_exit(0);
}
