#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

// Global variables
int n = 0;
int palindrome;
// Create and initialize semaphores
pthread_mutex_t n_mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function
void * thread_func(void * ptr) {
    for (int i = 0; i < 50; ++i) {
        //sleep(rand() % 6);
        int sw = 1;
        while (sw) {
            // Begin critical section
            pthread_mutex_lock(&n_mutex);
            if (!n){
                n = rand() % 500 + 1;
                sw = 0;
            }
            pthread_mutex_unlock(&n_mutex);
            // End critical section
        }
    }
    pthread_exit(NULL);
}

/* Funcion Para comprobar si es palindromo */
int check_palindrome (int num){
    // Convert int to string
    int n = log10(num) + 1;
    char str[n];
    sprintf(str, "%d", num);

    // Check palindrome
    int lenght = strlen(str);
    int i = 0;
    while (i <= lenght/2 && str[i] == str[lenght-1-i])
        i++;

    // Return 1 if palindrome or 0 if not
    if (i > lenght/2) 
        return 1;
    else 
        return 0;
}

void main() {
    srand(time(NULL));
    // Create threads
    pthread_t th_id1, th_id2, th_id3;
    pthread_create(&th_id1, NULL, &thread_func, NULL);
    pthread_create(&th_id2, NULL, &thread_func, NULL);
    pthread_create(&th_id3, NULL, &thread_func, NULL);

    while (1) {
        // Begin critical section
        pthread_mutex_lock(&n_mutex);
        while (n) {
            int palindrome = check_palindrome(n);
            if (palindrome == 1)
                printf("%d is Palindrome %d\n", n, palindrome);
            else
                printf("%d is not Palindrome %d\n", n, palindrome);
            n = 0;
        }
        pthread_mutex_unlock(&n_mutex);
        // End critical section
    }

    // Destroy semaphores
    pthread_mutex_destroy(&n_mutex);
    pthread_exit(NULL);
}