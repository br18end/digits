#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define PORT 4949         // port number
#define MAXDATASIZE 200   // data size (bytes)

int main(int argc, char *argv[])
{
  int sockfd, numbytes;
  char buf[MAXDATASIZE], result[20];
  struct hostent *he;
  struct sockaddr_in their_addr;
  int n, m, odds;
  memset(result, '\0', sizeof(result));

  if (argc != 2) {
    fprintf(stderr,"must be used like: SumaClientTP hostname\n");
    exit(1);
  }
  if ((he=gethostbyname(argv[1])) == NULL) {  // get server info
    herror("gethostbyname");
    exit(1);
  }
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  their_addr.sin_family = AF_INET;    // sockets family (TCP/IP v4)
  their_addr.sin_port = htons(PORT); // convert to network byte order
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(their_addr.sin_zero), '\0', 8);
  
  scanf("%d %d", &n, &m);

  // get connection
  if (connect(sockfd, (struct sockaddr *)&their_addr,
	      sizeof(struct sockaddr)) == -1) {
    perror("connect");
    exit(1);
  }

  printf("Client: sending data...\n");
  memset(buf, '\0', sizeof(buf));
  sprintf(buf, "%d\t%d\n", n, m);
  if (send(sockfd, buf, strlen(buf),0) == -1)
     perror("send");

 // server receives message
  memset(buf, '\0', sizeof(buf));
  printf("Client: receiving data...\n");
  
  /*if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
    perror("recv");
    exit(1);
  }
  sscanf(buf, "%s\n",&result);*/

  if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
    perror("recv");
    exit(1);
  }
  //sscanf(buf, "%d\n", &odds);

  printf("Client: %s\n",buf);  // print result
  close(sockfd);
  return 0;
}
