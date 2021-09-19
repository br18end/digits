#include<stdio.h>
#include<time.h>
#include<unistd.h>

int timespec_cmp(struct timespec *a, struct timespec *b) {
	if (a->tv_sec > b->tv_sec) return 1;
	else if (a->tv_sec < b->tv_sec) return -1;
	else if (a->tv_sec == b->tv_sec){
		if (a->tv_nsec > b->tv_nsec) return 1;
		else if (a->tv_nsec == b->tv_nsec) return 0;
		else return -1;
	}
}

main(){
	int a[6] = {30,50,20,10,3,98};
	struct timespec now, after;

	clock_gettime(CLOCK_MONOTONIC, &now);

	//codigo
	int N = 6;
  	int count = 0;
	for (int i = 0; i < N; i++)   
    	for (int j = i+1; j < N; j++)
      		for (int k = j+1; k < N; k++)
        		if (a[i] + a[j] + a[k] == 0)
          			count++;

	
	clock_gettime(CLOCK_MONOTONIC, &after);
	//if (timespec_cmp(&now, &after) > 0) {
		printf("Now %ld secs %ld nsecs\n", now.tv_sec, now.tv_nsec);
		printf("After %ld secs %ld nsecs\n", after.tv_sec, after.tv_nsec);
		int tiemposec = after.tv_sec - now.tv_sec;
		int tiemponsec = after.tv_nsec - now.tv_nsec;
		printf("Tiempo transcurrido %d secs %d nsecs\n", tiemposec,tiemponsec);
	//}
}