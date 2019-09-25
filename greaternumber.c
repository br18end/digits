#include <stdio.h>

main(){
	int numbers[10]={0},i,mayor=0;

	//Get 10 numbers
	for(i=0; i<10; i++){
		scanf("%d",&numbers[i]);
	}

	//Compare numbers
	for(i=0; i<10; i++){
		if(greater <= numbers[i]){
			greater=numbers[i];
		}
	}
	printf("Greater number: %d\n",greater);
}
