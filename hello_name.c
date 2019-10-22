#include <stdio.h>

main() {
	char name[20];
	printf("Write your name: \n");
	scanf("%s", name);
	
	printf("Hello %s!\n", name);
}