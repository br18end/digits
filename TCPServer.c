#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 4949     // port number
#define BACKLOG 10      // pending connections
#define MAXDATASIZE 200   // data size (bytes)


int main(void)
{
    int sockfd, new_fd, numbytes;
    char buf[MAXDATASIZE], auxcad[20], salcad[20], array[10];
    struct sockaddr_in my_addr;  // server address
    struct sockaddr_in their_addr; // remote address
    socklen_t sin_size;
    int n, m, aux, i, j, odds, cont = 0, res, position = 0;
    int yes=1;
    memset(array, '\0', sizeof(array));
    memset(auxcad, '\0', sizeof(auxcad));
    memset(salcad, '\0', sizeof(salcad));

    // create socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // define socket
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    my_addr.sin_family = AF_INET;          // sockets family (TCP/IP v4)
    my_addr.sin_port = htons(MYPORT);      // convert to network byte order
    my_addr.sin_addr.s_addr = INADDR_ANY;  // get local address
    memset(&(my_addr.sin_zero), '\0',8); 
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))
                                                                    == -1) {
        perror("bind");
        exit(1);
    }

    // port able to receive
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    while(1) { // server receives connections
        sin_size = sizeof(struct sockaddr_in);

	// wait until new connection
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,
                                                        &sin_size)) == -1) {
            perror("accept");
            continue;
        }

	// print connection data
        printf("Server: connection from %s\n",
                                            inet_ntoa(their_addr.sin_addr));

        memset(buf, '\0', sizeof(buf));
        if ((numbytes=recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
           perror("recv");
           exit(1);
        }

        sscanf(buf, "%d%d", &n, &m);
        for(i = n; i <= m; i++){
        aux = i;
        while(aux > 0){
          position = aux % 10;
          array[position] = array[position] + 1;
          aux = aux / 10;
	    }
        }
        for(i = 0; i < 10; i++){
          sprintf(auxcad, "%d ", array[i]);
          strcat(salcad, auxcad);
        }
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
        }
        memset(buf, '\0', sizeof(buf));
        printf("Server: sending data...\n");

	/*sprintf(buf, "%s\n", salcad);
        if (send(new_fd, buf, strlen(buf), 0) == -1)
          perror("send");*/
	
	sprintf(buf, "Digits: %s odds: %d\n", salcad, cont);
        if (send(new_fd, buf, strlen(buf), 0) == -1)
            perror("send");


	aux = 0, i = 0, j = 0, odds = 0, cont = 0, res = 0, position = 0;

        close(new_fd); // close connection
    }

  return 0;
}
