/*
by: Ing. Alfonso Medina Duran
    4lfonsomedina@gmail.com

Descripcion:

Crea tres hilos. 
funcion de hilos:
1.- Generará un número aleatorio entre 0 y 5.
2.- Se "dormirá" el periodo de tiempo indicado en el número generado en el paso anterior
3.- Al despertar genere numero aleatorio [1,500] y si n=0 guardarlo en n de lo contrario esperar a que n=0
4.- Regresará al paso 1 (debe repetirse 50 veces)

Funcion main:
1.- Ejecutar los 3 hilos
2.- Verificar constantemente si n!=0 
    en caso de que n!=0:
    2.1.- calcula e imprime si 'n' es palindromo o no lo es
    2.2.- igualar n=0

Nota: la variable 'n' es compartida por el main y los 3 hilos (Implementar semaforo mutex de posix).

Adicional:
Colocare una variable contadora para verificar que se generen 150 numeros (50 x hilo) y de esta forma asegurar que funcione correctamente el semaforo ya que ningun hilo utilizara n si se encuentra en uso y no abra sobre-escritura

Observacion: El ejercicio original dice que las variables 'n' y 'palindromo' son compartidas, sin embargo al analizar el problema se dedujo que solo 'n' es compartido y 'palindromo' solo es utilizada por el main , por lo cual se omitio el uso de semaforo para esta variable ya que no es necesario y no afecta el funcionamiento del ejercicio.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

void *funcion_hilo(int *n);
int Comprobar_palindromo(int num);

//Creacion de semaforo POXIS
pthread_mutex_t numero; // protege a la variable n 

//Variables
int n=0,palindromo=0;

int main() {
    //Inicializacion de semaforo
    if(pthread_mutex_init(&numero, NULL) != 0) {perror("MUTEX ERROR");exit(EXIT_FAILURE);}

    //creacion de hilos (main-1)
    pthread_t hilo1,hilo2,hilo3;
    pthread_create(&hilo1,NULL,&funcion_hilo,&n);
    pthread_create(&hilo2,NULL,&funcion_hilo,&n);
    pthread_create(&hilo3,NULL,&funcion_hilo,&n);

    int contador=0;
    //verificar el valor de n (main-2)
    printf("\n  #\tn\tpalindromo\n");
    while(1){
        pthread_mutex_lock(&numero); //lock n
        if(n!=0){
            contador++;
            palindromo = Comprobar_palindromo(n);           //verificar si n es palindromo
            printf("  %d\t%d\t%d\n",contador,n,palindromo); //Imprimir resultado
            n=0; //regresar n a 0
        }
        pthread_mutex_unlock(&numero); //unlock n
    }

    pthread_exit(NULL);
    return 0;
}


/* Funcion HILO*/
void *funcion_hilo(int *n){
    
    srand(time(NULL)); //semilla para random

    // Tarea que debe ejecutar 50 veces
    int repeticiones;
    for(repeticiones=50;repeticiones>0;repeticiones--){
        
        int aleatorio = rand() % 6;  //[0,5] (hilos-1)
        sleep(aleatorio); //dormir (hilos-2)

        //seccion critica (se repetira hasta que n=0) (hilos-4)
        int salir_while=1;
        while(salir_while){
            pthread_mutex_lock(&numero); //lock n
            if(*n==0){
                *n = rand() % 500 + 1; //[1,500] (hilos-3)
                salir_while=0;
            }
            pthread_mutex_unlock(&numero); //unlock n
        }
    }
    pthread_exit(NULL);
}

/* Funcion Para comprobar si es palindromo */
int Comprobar_palindromo (int num){
    // Convertir entero a cadena
    int n = log10(num) + 1;
    char frase[n];
    sprintf(frase, "%d", num);

    // Comprobar palindromo de "cadena"
    int longitud=strlen(frase);
    int i=0;
    while (i<=longitud/2 && frase[i]==frase[longitud-1-i]){i++;}

    // retorna 1 para palindromo y 0 para no palindromo
    if (i>longitud/2) return 1;
    else return 0;
}