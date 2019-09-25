/*
List of Armstrong numbers in the range of 0 and 999
0,1,153,370,371,407.
*/

#include<stdio.h>

main() {
	//GET NUMBER
	int number;
	printf("Introduce a number: ");
	scanf("%d", &number);

	//CHECK IF NUMBER IS 0
	if (number == 0) {
		printf("Number %d is an Armstrong number\n", number);
	}
	else {
		int length = 0;
		int aux = number;

		//COUNT NUMBER OF DIGITS
		while (aux != 0) {
    		aux = aux / 10;
    		length++;
		}

		//CREATE ARRAY
		int numberArray[length];

		//EXTRACT EACH DIGIT TO ARRAY
		int position = 0;    
		aux = number;

		while (aux != 0) {
    		numberArray[position] = aux % 10;
    		aux = aux / 10;
    		position++;
		}

		//GET SUM OF CUBIC DIGITS
		int sum = 0;

		for (int i = 0; i < length; ++i) {
			int n = numberArray[i];
			numberArray[i] = n * n * n;
			sum = sum + numberArray[i];
		}

		//CHECK IF NUMBER IS ARMSTRONG
		if (sum == number) {
			printf("Number %d  is an Armstrong number\n", number);
		}
		else {
			printf("Number %d  is NOT an Armstrong number\n", number);
		}
	}
}
