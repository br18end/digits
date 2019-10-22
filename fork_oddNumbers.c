#include<stdio.h>

int main(){
	int n = 1,m = 1, aux = 0, i, j, p, primos, cont, res;
	int posicion = 0;
	int arreglo[10] = {0};
	
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
	} else {
		cont = 0;
		for (i = n; i <= m; i++) {
			primos = 1;
			for (j=2; j<i; j++) {
				res = i % j;
				if (res == 0) {
					primos = 0;
					j=i;
					}
			}
			if (primos) {
				cont++;
				}
		}printf("Primos entre %d y %d inclusive: %d\n", n, m, cont);
	}
}

Sharing settings
