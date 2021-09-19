#include <stdio.h>

void insertion(int v[], int n);

void main() {
	//GET NUMBER OF ELEMENTS
	printf("Insert number of elements ");
	int n;
	scanf("%d", &n);
	//CREATE ARRAY
	int v[n];
	//GET ELEMENTS
	printf("Insert %d elements\n", n);
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
	//ORDER ELEMENTS USING INSERTION SORT
	insertion(v, n);
	//PRINT LIST OF ELEMENTS
	printf("Elements in order\n");
	for (int i = 0; i < n; i++)
		printf("%d\n", v[i]);
}

void insertion(int v[], int n) {
	int i, j, aux;

	for (i = 2; i < n; i++) {
		aux = v[i];
		j = i-1;
		while(j >= 0 && v[j] > aux){
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = aux;
	}
}