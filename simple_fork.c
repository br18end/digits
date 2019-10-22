#include<stdio.h>

main(){
	int n = 1,m = 1, aux = 0, i, p;
	int posicion = 0;
	int arreglo[10] = {0};
	char auxcad[100];
	char salcad[100];
	
	scanf("%d %d", &n, &m);
	p = fork();
	
	if(p == 0){
		for(i = n; i <= m; i++){
			aux = i;
			while(aux > 0){
				posicion = aux % 10;
				arreglo[posicion] = arreglo [posicion] + 1;
				aux = aux / 10;
			}
		}
		for(i = 0; i < 10; i++){
			printf("%d ", arreglo[i]);
		}printf("\n");
	}
}