#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

int timespec_cmp(struct timespec *a, struct timespec *b);
void crear_archivos(int padre, int hijo, int nieto);
void calcular_tiempo();
void leer_arreglo(int padre,int hijo, int nieto);
int get_random(int max, int min);
int calc_time(struct timespec now, struct timespec after);

int main(){
	int ciclo_padre;
	int ciclo_hijo;
	int ciclo_nieto;

	for(ciclo_padre=1;ciclo_padre<=10;ciclo_padre++){
		for(ciclo_hijo=1;ciclo_hijo<=10;ciclo_hijo++){
			for(ciclo_nieto=1;ciclo_nieto<=ciclo_padre*100;ciclo_nieto++){
				crear_archivos(ciclo_padre*100,ciclo_hijo*100,ciclo_nieto);
			}
		}
	}
	calcular_tiempo();
}

void crear_archivos(int padre,int hijo, int nieto){
	//CREATE ROUTE
	char ruta_completa[100];
	sprintf(ruta_completa, "archivos/%d/%d/%d.dat", padre, hijo, nieto);
	printf("%s\n",ruta_completa);
	//CREATE FILE
	FILE* file_ptr = fopen(ruta_completa, "w");
	//WRITE RANDOM NUMBERS
	int ih = 0;
	for(ih; ih < hijo; ih++){
		int aleatorio = get_random(100,-100);
		fprintf(file_ptr, "%d\n", aleatorio);
	}
	//CLOSE FILE
    fclose(file_ptr);
}

void calcular_tiempo() {
	int ciclo_padre;
	int ciclo_hijo;
	int ciclo_nieto;
	//INITIALIZE TIME
	struct timespec now, after, res;
	//CREATE AND OPEN TIMES FILE
	FILE* file_ptr = fopen("archivos/times.dat", "w");

	// Code for gnuplot pipe
	FILE *pipe = popen("gnuplot -persist", "w");
	fprintf(pipe, "\n");

	for(ciclo_padre=1;ciclo_padre<=10;ciclo_padre++){
		for(ciclo_hijo=1;ciclo_hijo<=10;ciclo_hijo++){
			for(ciclo_nieto=1;ciclo_nieto<=ciclo_padre*100;ciclo_nieto++){
				//GET TIME NOW
				clock_gettime(CLOCK_MONOTONIC, &now);
				//READ ARRAY
				leer_arreglo(ciclo_padre*100,ciclo_hijo*100,ciclo_nieto);
				//GET TIME AFTER
				clock_gettime(CLOCK_MONOTONIC, &after);
				//CALC TIMES
				if(now.tv_nsec > after.tv_nsec){
					res.tv_sec = after.tv_sec - now.tv_sec - 1;
					res.tv_nsec = now.tv_nsec - after.tv_nsec;
				}
				else if (now.tv_sec == after.tv_sec) {
					res.tv_sec = 0;
					res.tv_nsec = after.tv_nsec - now.tv_nsec;
				}
				else {
					res.tv_sec = after.tv_sec - now.tv_sec;
					res.tv_nsec = after.tv_nsec - now.tv_nsec;
				}
				int tiemposec = res.tv_sec;
				int tiemponsec = res.tv_nsec;
				//WRITE TIMES
				fseek(file_ptr, 0, SEEK_END);
				fprintf(file_ptr, "%d.%.2d %d\n", tiemposec, tiemponsec, ciclo_padre*100);
				fprintf(pipe,"set title \"tarea52_gnuplot\n");
				fprintf(pipe,"set xlabel \"time\"\n");
				fprintf(pipe,"set ylabel \"files\"\n");
				fprintf(pipe,"plot \"archivos/times.dat\" using 1:2 with lines\n");
				fflush(pipe);
			}
		}
	}
	//CLOSE FILE
    fclose(file_ptr);

	fclose(pipe);
}

void leer_arreglo(int padre,int hijo, int nieto) {
	//CREATE ROUTE
	char ruta_completa[100];
	sprintf(ruta_completa, "archivos/%d/%d/%d.dat", padre, hijo, nieto);
	//CREATE FILE
	FILE* file_ptr = fopen(ruta_completa, "r");
	//WRITE FILE INTO ARRAY
    int numberArray[hijo];
	int ih = 0;
	for(ih; ih < hijo; ih++){
		fscanf(file_ptr, "%d\n", &numberArray[ih]);
	}
	//GET COMBINATIONS
	int n = sizeof(numberArray);
	int count = 0;
	for (int i = 0; i < n; i++)   
    	for (int j = i+1; j < n; j++)
      		for (int k = j+1; k < n; k++)
        		if (numberArray[i] + numberArray[j] + numberArray[k] == 50) {
          			count++;
          			printf("Verified %s\n", ruta_completa);
        		}
	//CLOSE FILE
    fclose(file_ptr);
}

int get_random(int max, int min) {
	int random;
	if((max - min) == 0) {
		random = 1;
	}
	else {
		random = rand() % (max - min);
	}
	return random + min;
}