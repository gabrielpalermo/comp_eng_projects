// Computer Networks I
// Computer Engineering - IME (2017.2)
// Web chat using UDP Socket

#ifdef WIN64
#include <windows.h>
#include <winsock2.h>
#else
#include <sys/socket.h>
#include<sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#endif
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 80
#define PORT 43454
#define SA struct sockaddr

void web_chat(int sockfd)
{
    char buff[MAX];
    int n, clen;
    struct sockaddr_in cli;
    clen = sizeof(cli);
    for(;;)
    {
        bzero(buff,MAX);
        recvfrom(sockfd, buff,  sizeof(buff), 0, (SA *)&cli, &clen);
        printf("From client %s to client", buff);
        bzero(buff, MAX);
        n=0;
        while((buff[n++] = getchar())!='\n');

        sendto(sockfd, buff, sizeof(buff), 0, (SA *)&cli, clen);

        if(strncmp("exit", buff, 4) == 0)
        {
            printf("Server exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1)
    {
        printf("Socket creation failed ...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created ...\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if((bind(sockfd,(SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Socket bind failed ...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded ...\n");
    }

    web_chat(sockfd);
    close(sockfd);
}
