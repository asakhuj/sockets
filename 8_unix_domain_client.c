#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#include <sys/un.h>
#define SOCKET_PATH "/home/sumit/sockets/socket_file"
int main()
{
    struct sockaddr client_addr;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;
    struct in_addr* addr;
    char ipv4str[INET_ADDRSTRLEN];
    int sockfd, new_fd, yes=1;
    char buf[256];
    int bytes;
    
    if((sockfd = socket(AF_UNIX, SOCK_STREAM,0)) == -1)
    {
        printf("socket creation failed errno%d sockfd %d", errno,sockfd);
        return 0;
    }
    else
    {
        printf("socket creation passed sockfd %d\n", sockfd);
    }
    
    //unlink(SOCKET_PATH);
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));    
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path,SOCKET_PATH);
    
    
    if(connect(sockfd, (struct sockaddr*) &server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        printf("Couldn't connect errno %d to %s", errno, server_sockaddr.sun_path);
        perror("Failure");
        return 0;
    }
    else
    {
        printf("Connect to socket passed\n");
    }
    
    
    printf("Sending data to server\n");
    memset(buf, 0, sizeof(buf));    
    strcpy(buf,"Hello Server, Hope you serve me well");
    
    if(send(sockfd, buf, strlen(buf), 0) == -1)
    {
        printf("error in sending data, errno %d\n", errno);
    }
    
    printf("waiting to receive data from server\n");
    memset(buf, 0, sizeof(buf));

    bytes = recv(sockfd, buf, sizeof(buf), 0);
    if (bytes == -1){
        perror("RECV ERROR: \n");
        close(new_fd);
        close(sockfd);
        exit(1);
    }
    else {
        printf("DATA RECEIVED = %s\n", buf);
    }

    sleep(1);        
    close(sockfd);
    return 0;
}
/********* Outpue ************
 * socket creation passed sockfd 3
 * Connect to socket passed
 * Sending data to server
 * waiting to receive data from server
 * DATA RECEIVED = Hello Client, you just got served :)
 * /
