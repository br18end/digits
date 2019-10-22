#include<unistd.h>
#include<stdio.h>

int main(){
	int n = 1,m = 1, aux = 0, i, j, p, primos, cont, res;
	int posicion = 0;
	int arreglo[10] = {0};
	FILE *entrada, *salida;
	char nombre_archivo[20], linea[20];

	scanf("%d %d", &n, &m);
	sprintf(nombre_archivo,"/tmp/%d", getpid());
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

		salida = fopen(nombre_archivo, "w");
		if (salida == NULL) {
      			fprintf(stderr,"Error al abrir archivo %s\n", nombre_archivo);
			return;
		}

		for(i = 0; i < 10; i++){
			sprintf(linea, "%d ", arreglo[i]);
   			fprintf(salida, linea);
		}fclose(salida);

	} else {
		entrada = fopen(nombre_archivo, "r");
    		
      		if (entrada == NULL) {
			while(entrada == NULL){
      				entrada = fopen(nombre_archivo, "r");
       			}	
     		}

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
		}		
		printf("Primos entre %d y %d inclusive: %d\n", n, m, cont);
		wait();
		fgets(linea, sizeof(linea), entrada);
		printf("Digits: %s Archivo: %s\n",linea,nombre_archivo);
	}
}

Sharing settings
