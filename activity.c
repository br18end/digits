#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CREATE STRUCTURE OF ELEMENTS
typedef struct Node {
	int data;
	struct Node *next;
}node;

//COMPARE ELEMENTS
int comparator(const void * a, const void *b) {
	int ia = ((const node*)a)->data;
	int ib = ((const node*)b)->data;
	if (ia < ib)
		return -1;
	else if (ia > ib)
		return 1;
}

void main() {
	//GET NUMBER OF ELEMENTS
	printf("Insert number of elements ");
	int n;
	scanf("%d", &n);
	//CREATE POINTER
	node* pointer = (node*) malloc(n*sizeof(node));
	//GET ELEMENTS
	printf("Insert %d elements\n", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &pointer[i].data);
	}
	//ORDER ELEMENTS USING QUICKSORT
	qsort(pointer, n, sizeof(node), comparator);
	//PRINT LIST OF ELEMENTS
	printf("Elements in order\n");
	for (int i = 0; i < n; i++) {
		printf("%d\n", pointer[i].data);
	}
	free(pointer);
}