#include<stdio.h>

main(){
	int n = 1,m = 1, aux = 0, i, p;
	int position = 0;
	int array[10] = {0};
	char auxcad[100];
	char salcad[100];
	
	scanf("%d %d", &n, &m);
	p = fork();
	
	if(p == 0){
		for(i = n; i <= m; i++){
			aux = i;
			while(aux > 0){
				position = aux % 10;
				array[position] = array [position] + 1;
				aux = aux / 10;
			}
		}
		for(i = 0; i < 10; i++){
			printf("%d ", array[i]);
		}printf("\n");
	}
}