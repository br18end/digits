#include<stdio.h>

void main() {
	int arreglo1[] = {0}, arreglo2[] = {1, 4, 5}, arreglo3[] = {2, 3, 6, 7};
	int *arregloTotal[] = {arreglo1, arreglo2, arreglo3};

	int aux = (sizeof(arregloTotal[0])/sizeof(int));
	printf("Array length %d\n", aux);

	/*for (int i = 0; i < 3; ++i) {
		printf("%d\n", *arregloTotal[i]);
	}*/

	printf("Array elements below\n");
	for (int i = 0; i < (sizeof(arregloTotal)/sizeof(int)); ++i) {
		for (int j = 0; j < (sizeof(arregloTotal[i])/sizeof(int)); ++j) {
			printf("%d\t", *(arregloTotal[j] + i));
		}printf("\n");
	}
}