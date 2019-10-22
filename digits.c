#include<stdio.h>
#include<string.h>

int main(){

   int n = 1;
   int m = 1;
   int i = 0; 
   int aux = 0;
   int arreglo[10];
   char salida[200];
   char auxiliar[100];

   //memset(arreglo, '\0', sizeof(arreglo));
   while(n > 0 && m > 0){
      scanf("%d %d", &n, &m);
      if(n > 0 && m > 0){
      
         for(i = n;i <= m;i++){
            aux = i;
            while(aux > 0){
               arreglo[aux % 10]++;
               aux = aux / 10;
            }
         }
      
         for(i = 0;i < 10; i++){
	   sprintf(auxiliar,"%d ",arreglo[i]);
           strcat(salida,auxiliar);         
           arreglo[i] = 0;
         }
         strcat(salida,"\n");
      }
   }
   printf("%s", salida);
}