#include<stdio.h>
#include<string.h>

int main(){

   int n = 1;
   int m = 1;
   int i = 0; 
   int aux = 0;
   int array[10];
   char output[200];
   char auxiliar[100];

   //memset(array, '\0', sizeof(array));
   while(n > 0 && m > 0){
      scanf("%d %d", &n, &m);
      if(n > 0 && m > 0){
      
         for(i = n;i <= m;i++){
            aux = i;
            while(aux > 0){
               array[aux % 10]++;
               aux = aux / 10;
            }
         }
      
         for(i = 0;i < 10; i++){
	   sprintf(auxiliar,"%d ",array[i]);
           strcat(output,auxiliar);         
           array[i] = 0;
         }
         strcat(output,"\n");
      }
   }
   printf("%s", output);
}