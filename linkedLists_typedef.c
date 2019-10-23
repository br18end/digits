#include<stdio.h>
#include<stdlib.h>

typedef struct nodeT {
	int value;
	struct nodeT *next;
}node;

void main() {
	int i;
	node *ptr, *ptrPrev;
	ptr = malloc(sizeof(node));
	struct ptrPrev;

	for (i = 0; i < 10; ++i){
		node *ptr2 = malloc(sizeof(node));
		
		if (i==0){
			ptr->value=i;
			ptr->next = (struct nodeT *)ptr2;
			ptr2->value=i+1;
		}
		else{
			ptr2->value=i+1;
			ptrPrev->next = (struct nodeT *)ptr2;
		}
		ptrPrev = ptr2;
	}

	for (int i = 0; i < 11; ++i)
	{
		printf("%d\n", ptr->value);
		ptr=ptr->next;
	}
}