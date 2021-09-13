// header files ----------------------
#include <sys/socket.h> //socket(3)
#include <sys/types.h> //accept(3), bind(3)
#include <netinet/in.h> //sockaddr_in
#include <strings.h> // bzero(2)
#include <unistd.h> //read(3), write(3)
#include <string.h> //strlen(1)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


//------------------------------------

#define MAXLINE 4096
#define LISTENQ 1024

int main(int argc, char **argv){
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    //client 정보
    socklen_t  len;
    struct sockaddr_in cliaddr;
    //-------
    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
        perror("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        perror("bind error");
    if(listen(listenfd, LISTENQ) < 0)
        perror("listen error");
    for(;;){
        if( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len)) < 0)
            perror("accept error");
        /*
        printf("connection from %s, port %d\n",  inet_pton(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));
        */
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if( write(connfd, buff, strlen(buff)) != strlen(buff) )
            perror("write error");
        
        if( close(connfd) == -1)
            perror("close error");


    }

}