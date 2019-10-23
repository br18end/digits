#include<stdio.h>

main(){
	int n = 0, i, cantbil[2] = {0}, cantcoins[4] = {0};
	int bil[] = {50,20}, coins[] = {10,5,2,1};

	printf("Enter quantity: ");
	scanf("%d",&n);

	while(n != 0){
        if(n >= 50){
			n = n - 50;
			++cantbil[0];
		} else {
		    if(n >= 20){
			n = n -20;
			++cantbil[1];
		} else {
		    if(n >= 10){
			n = n - 10;
			++cantcoins[0];
		} else {
		    if(n >= 5){
			n = n -5;
			++cantcoins[1];
		} else {
		    if(n >= 2){
			n = n -2;
			++cantcoins[2];
		} else {
			n = n - 1;
			++cantcoins[3];
		}}}}}}	
	for(i = 0; i < 2; i++){
		printf("Number of bil of %d: %d\n",bil[i],cantbil[i]);
	}

	for(i = 0; i < 4; i++){
		printf("Number of coins of %d: %d\n",coins[i],cantcoins[i]);
	}
}
