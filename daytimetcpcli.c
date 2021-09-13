// header files ----------------------
#include <sys/socket.h> //socket(3)
#include <sys/types.h> //accept(3), bind(3)
#include <netinet/in.h> //sockaddr_in
#include <strings.h> // bzero(2)
#include <unistd.h> //read(3), write(3)
#include <string.h> //strlen(1)
#include <time.h>
#include <stdio.h>
#include <arpa/inet.h> // inet_pton(3)
#include <stdlib.h> // exit()



//------------------------------------
#define MAXLINE 4096


int main(int argc, char **argv){
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2)
        perror("usage: a.out <IPaddress>");
        
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("socket error");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        perror("inet_pton error");

    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        perror("connect error");
    
    while((n = read(sockfd, recvline, MAXLINE)) > 0){
        recvline[n] = 0; //null terminate
        if(fputs(recvline, stdout) == EOF)
            perror("fputs error");
    }
    if(n<0)
        perror("read error");

    exit(0);
}