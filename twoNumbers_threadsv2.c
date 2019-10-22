#include<stdio.h>
#include<pthread.h>

int n1, n2, sum;

void * thread_sum(void * arg) {
    sum = n1 + n2;
    pthread_exit(NULL);
}

void main() {
    printf("First number: ");
    scanf("%d", &n1);

    printf("Second number: ");
    scanf("%d", &n2);

    pthread_t th_id;
    printf("The result is ");
    pthread_create(&th_id, NULL, &thread_sum, NULL);
    pthread_join(th_id, NULL);
    printf("%d + %d = %d\n", n1, n2, sum);
    pthread_exit(NULL);
}