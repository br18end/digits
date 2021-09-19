#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "timespec-add.c"
#include "fifo.c"

void append(char* s, char c);
void *funcion_hilo2(int *num);
void *funcion_hilo3(int *num);

pthread_mutex_t numero_m; // Protege a la variable numero
int numero=0;

// Definicion de tiempos de cada hilo
struct timespec initialTime; 
struct timespec periodo_hilo1 = {0,1000000000};
struct timespec periodo_hilo2 = {0,2000000000};
struct timespec periodo_hilo3 = {0,3000000000};


int main(){
    /* Iniciar el reloj para medir los tiempos de ejecucion */
    clock_t start = clock();

    /*Semaforo*/
    pthread_mutexattr_t  mutex_attr; // Create mutex attribute
    pthread_mutexattr_init(&mutex_attr); // Initialize mutex attribute
    pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_INHERIT); // Set Priority inheritance protocol

    if(pthread_mutex_init(&numero_m, NULL) != 0) {perror("MUTEX ERROR");exit(EXIT_FAILURE);}

    /* Creacion de hilos*/
    pthread_t hilo2,hilo3;
    pthread_create(&hilo2,NULL,(void *)funcion_hilo2,NULL);
    pthread_create(&hilo3,NULL,(void *)funcion_hilo3,&numero);

    /*Datos de puerto*/
    int num_puerto=0;
    printf("Especifica el puerto ttyUSB:\n");
    scanf("%d", &num_puerto);
    char puerto[15] = "/dev/ttyUSB";  /*PUERTO*/
    sprintf(puerto, "/dev/ttyUSB%d",num_puerto); /* Preguntar el puerto*/
    
    /*Configuracion y apertura de velocidad del puerto*/
    int fd;
    //Open port
    fd = open(puerto, O_RDWR | O_NOCTTY);
    /* ttyS0 is the serial port   */
    /* O_RDWR   - Read/Write access to serial port */
    /* O_NOCTTY - No terminal will control the process */
    /* O_NONBLOCK - The file is opened in nonblocking mode */
    /* Open in blocking mode,read will wait */

    //Check errors
    if (fd == -1)
        printf("Opening port: %s(Code:%d)\n", strerror(errno), errno);
    else 
        printf("Opening port: %s(Code:%d)\n", strerror(errno), errno);

    /* Setting the Attributes of the serial port using termios structure */
    // Create the structure
    struct termios SerialPortSettings;
    // Get the current attributes of the Serial port 
    tcgetattr(fd, &SerialPortSettings);

    /* Setting the Baud rate */
    // Set Read  Speed as 9600
    cfsetispeed(&SerialPortSettings,B9600);
     
    // Set Write Speed as 9600 
    cfsetospeed(&SerialPortSettings,B9600);
     
    //cfmakeraw() sets the terminal to something like the "raw" mode of the old Version 7 terminal driver: input is available character by character, echoing is disabled, and all special processing of terminal input and output characters is disabled. 
    cfmakeraw(&SerialPortSettings);
    /* 8N1 Mode */
    // Disables the Parity Enable bit(PARENB),So No Parity
    SerialPortSettings.c_cflag &= ~PARENB;
    // CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit
    SerialPortSettings.c_cflag &= ~CSTOPB;
    // Clears the mask for setting the data size
    SerialPortSettings.c_cflag &= ~CSIZE;
    // Set the data bits = 8
    SerialPortSettings.c_cflag |= CS8;
    // No Hardware flow Control
    SerialPortSettings.c_cflag &= ~CRTSCTS;
    // Enable receiver,Ignore Modem Control lines
    SerialPortSettings.c_cflag |= (CREAD | CLOCAL);
    // Disable XON/XOFF flow control both i/p and o/p
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
    // Non Cannonical mode
    SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ISIG);  
    // No Output Processing
    SerialPortSettings.c_oflag &= ~OPOST;

    /* Setting Time outs */
    // Read at least 1 characters
    SerialPortSettings.c_cc[VMIN] = 1;
    // Wait indefinetly 
    SerialPortSettings.c_cc[VTIME] = 0;

    /* Set the attributes to the termios structure*/
    if((tcsetattr(fd, TCSANOW, &SerialPortSettings)) == -1) 
        printf("Setting attributes: %s(Code:%d)\n", strerror(errno), errno);
    else
        printf("Setting attributes: %s(Code:%d) \nBaudRate = 9600 \nStopBits = 1 \nParity = none\n", strerror(errno), errno);

    /* Read data from serial port */
    // Discards old data in the rx buffer
    tcflush(fd, TCIFLUSH);
 
    /* Alguritmo de extraccion de informacion de serial */
    char separador=',';
    char cadena_envio[80];
    memset(cadena_envio, 0, sizeof(cadena_envio)); 

    struct timespec siguienteActivacion = initialTime;
    siguienteActivacion = timespec_add(siguienteActivacion, periodo_hilo1);
    while (1){
        int u=0,i=0;
        unsigned char buf[80];
 	memset(buf, 0, sizeof(buf)); 
        for(u=0;u<80;u++) buf[u]=0;
        read(fd, buf, sizeof(buf) - 1);
        for(i=0;i<80;i++){
            if(buf[i]!=0){
                if(buf[i]!=separador)
                    append(cadena_envio, buf[i]);
                if(buf[i]==separador){
                    int condicion=0;
                    pthread_mutex_lock(&numero_m); // Lock numero
                    sscanf(cadena_envio, "%d", &numero);
                    // Numero es la variable compartida
                    if(numero>90||numero<-90){
                        condicion=1;
                        write(fd,"1",1);
                    }
                    printf("%d\t%d\n",numero,condicion);
                    pthread_mutex_unlock(&numero_m); // Unlock numero
                    for(u=0;u<80;u++){
                        cadena_envio[u]=0;
                    }
                }
            }
        }
        nanosleep(&siguienteActivacion, &periodo_hilo1);
	printf("Tiempo transcurrido: %f\n", ((double)clock() - start));
    }//while

    pthread_exit(NULL);
    return 0;
}



/*Este hilo solo generara un arreglo aleatorio y lo ordenara mediante metodo burbuja*/
void *funcion_hilo2(int *num){
    struct timespec siguienteActivacion = initialTime;
    siguienteActivacion = timespec_add(siguienteActivacion, periodo_hilo2);
    while(1){
        /*creacion de lista*/
        int TAM=20;
        int lista[TAM];
        int u=0;
        printf("\n");
        for(u=0;u<TAM;u++){
            lista[u]=rand() % 101;
            //printf("%d\t",lista[u]);
        }
        printf("\n");

        /*ordenamiento burbuja*/
        int i=0, j=0, temp=0;
        for(i=1;i<TAM;i++)
            for(j=0;j<TAM-1;j++)
                if (lista[j] > lista[j+1]){
                    temp = lista[j];
                    lista[j] = lista[j+1];
                    lista[j+1] = temp;
                }
        //for(u=0;u<TAM;u++)printf("%d\t",lista[u]);
        nanosleep(&siguienteActivacion, &periodo_hilo2);
    }
    pthread_exit(NULL);
}



void *funcion_hilo3(int *num){
    struct timespec siguienteActivacion = initialTime;
    siguienteActivacion = timespec_add(siguienteActivacion, periodo_hilo3);
    while(1){
        pthread_mutex_lock(&numero_m); //lock numero
        insert(*num);
        display();
        pthread_mutex_unlock(&numero_m); //unlock numero
        nanosleep(&siguienteActivacion, &periodo_hilo2);
    }
    pthread_exit(NULL);
}



/*Funcion de concatenado*/
void append(char* s, char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

