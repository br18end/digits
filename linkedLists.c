#include<stdio.h>
#include<stdlib.h>

//CREATE STRUCTURE
struct element {
	int velement;
	struct element *next;
};

//INSERT ELEMENT
struct element * list_insert (struct element *pointer, int value){
	struct element * p = pointer;

    if (pointer != NULL) {
    	//FIND LAST ELEMENT
		while (pointer -> next != NULL) {
		    pointer = pointer -> next;
		}
		//RESERVE MEMORY
		pointer -> next = (struct element  *) malloc (sizeof (struct element));
		//SET POINTER
		pointer = pointer -> next;
		pointer -> next = NULL;
		//INSERT DATA
		pointer -> velement = valor;
		printf("-  Element added  -\n");
		return p;
    }
    else {
    	//RESERVE MEMORY
		puntero = (struct element  *) malloc (sizeof (struct element));
		//SET POINTER
		pointer -> next = NULL;
		//INSERT DATA
		pointer -> velement = value;
		printf("-  Element added  -\n");
		return pointer;
    }
}

//REMOVE ELEMENT
struct element * list_remove (struct element *pointer, int value){
	struct element * tempp;

	//FIND ELEMENT
	while ((pointer -> velement != value) && (pointer -> next != NULL)) {
		pointer = pointer -> next;
	}
    //SHOW ELEMENT AND POINTER
    if (pointer -> velement == value) {
    	//SET NEW POINTER
    	tempp = pointer -> next;
    	printf ("Element deleted\n");
    }
    else {
    	printf("-  Elemente not found  -\n");
    }
    return tempp;
}

//FIND ELEMENT
struct element * list_find (struct element *pointer, int value){

	//FIND ELEMENT
	while ((pointer -> velement != value) && (pointer -> next != NULL)) {
		pointer = pointer -> next;
	}
    //SHOW ELEMENT AND POINTER
    if (pointer -> velement == value) {
    	printf ("-  Element found  -\n");
    	printf("Value: %d pointer: %p\n", pointer -> velement, pointer);
    }
    else {
    	printf("-  Element not found  -\n");
    }
    return pointer;
}

//PRINT LIST
void list_print (struct element *pointer){
	//PRINT ALL ELEMENTS UNTIL NULL
	while (pointer != NULL) {
	    printf ("%d\n", pointer -> velement);
	    pointer = pointer -> next;
	}
}

void main() {
	//CREATE ELEMENTS AND POINTERS
	struct element member, *pointer;
	int value, option;
	//INITIALIZE POINTER
	pointer = NULL;

	//SHOW MENU
	do {
		printf("Menu\n");
		printf("1.Add element\n");
		printf("2.Delete element\n");
		printf("3.Search element\n");
		printf("4.Print list\n");
		printf("5.Exit\n");
		//GET OPTION
		printf("Select option: ");
		scanf("%d", &option);

		//CHECK OPTION
		switch(option) {
			case 1:
	    		//GET ELEMENT
	    		printf("Element to add: ");
				scanf("%d", &value);
				//CALL INSERT FUNCTION
				pointer = list_insert(pointer, value);
			break;

			case 2:
				//CHECK IF LIST EMPTY
				if (pointer == NULL) {
					printf("-  Empty list  -\n");
				}
				else {
					//GET ELEMENT
					printf("Element to delete: ");
					scanf("%d", &value);
					//CALL REMOVE FUNCTION
					pointer = list_remove(pointer, value);	
				}
			break;

			case 3:
				//CHECK IF LIST EMPTY
				if (pointer == NULL) {
					printf("-  Empty list  -\n");
				}
				else {
					//GET ELEMENT
	    			printf("Element to search: ");
					scanf("%d", &value);
					//CALL FIND FUNCTION
					pointer = list_find(pointer, value);
				}
			break;

			case 4:
				//CHECK IF LIST EMPTY
				if (pointer == NULL) {
					printf("-  Empty list  -\n");
				}
				else {
					//CALL PRINT FUNCTION
					list_print(pointer);
				}
			break;

			case 5:
			break;
		}
	} while (option != 5);
}
