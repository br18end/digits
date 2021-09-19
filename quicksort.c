#include <stdio.h>

void quicksort(int v[], int first, int last);

void main() {
	int n, i;

	printf("Insert number of elements ");
	scanf("%d", &n);
	
	int v[n];

	printf("Insert elements\n");
	for (i = 0; i < n; i++)
		scanf("%d", &v[i]);

	quicksort(v, 0, n-1);

	printf("Elements in order\n");
	for (i = 0; i < n; i++)
		printf("%d\n", v[i]);
}

void quicksort(int v[], int first, int last){
	int pivot, j, temp, i;

	if(first < last) {
		pivot = first;
		i = first;
		j = last;

		while(i < j){
			while(v[i] <= v[pivot] && i < last)
				i++;
			while(v[j] > v[pivot])
				j--;
			if(i < j){
				temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}
		}

		temp = v[pivot];
		v[pivot] = v[j];
		v[j] = temp;
		quicksort(v,first,j-1);
		quicksort(v,j+1,last);
	}
}