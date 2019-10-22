#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int c, n;    
    srand(time(NULL));
    n = rand() % 6;  // random number between [0,5]    
    printf("Sleeping %d seconds\n", n);
    sleep(n);

    printf("Generating 10 random numbers between [1,150]...\n");
    for (c = 1; c <= 10; c++) {
        n = rand() % 500 + 1;
        printf("%d\n", n);
    }
    return 0;
}
