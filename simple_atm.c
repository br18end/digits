#include<stdio.h>

main(){
	int n = 0, i, cantbilletes[2] = {0}, cantmonedas[4] = {0};
	int billetes[] = {50,20}, monedas[] = {10,5,2,1};

	printf("Ingrese cantidad: ");
	scanf("%d",&n);

	while(n != 0){
        if(n >= 50){
			n = n - 50;
			++cantbilletes[0];
		} else {
		    if(n >= 20){
			n = n -20;
			++cantbilletes[1];
		} else {
		    if(n >= 10){
			n = n - 10;
			++cantmonedas[0];
		} else {
		    if(n >= 5){
			n = n -5;
			++cantmonedas[1];
		} else {
		    if(n >= 2){
			n = n -2;
			++cantmonedas[2];
		} else {
			n = n - 1;
			++cantmonedas[3];
		}}}}}}	
	for(i = 0; i < 2; i++){
		printf("Cantidad de billetes de %d: %d\n",billetes[i],cantbilletes[i]);
	}

	for(i = 0; i < 4; i++){
		printf("Cantidad de monedas de %d: %d\n",monedas[i],cantmonedas[i]);
	}
}
