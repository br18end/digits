#include<stdio.h>

int main(){
	int n = 1,m = 1, aux = 0, i, j, p, odds, cont, res;
	int position = 0;
	int array[10] = {0};
	
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
	} else {
		cont = 0;
		for (i = n; i <= m; i++) {
			odds = 1;
			for (j=2; j<i; j++) {
				res = i % j;
				if (res == 0) {
					odds = 0;
					j=i;
					}
			}
			if (odds) {
				cont++;
				}
		}printf("odds between %d and %d inclusive: %d\n", n, m, cont);
	}
}