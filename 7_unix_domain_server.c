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
#define MAXBACKLOG 2
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
        return;
    }
    else
    {
        printf("socket creation passed sockfd %d\n", sockfd);
    }
    
    unlink(SOCKET_PATH);
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));    
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path,SOCKET_PATH);
    
    
    if(bind(sockfd, (struct sockaddr*) &server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        printf("Couldn't bind errno %d", errno);
        perror("Bind failed");        
        return 0;
    }
    
    if(listen(sockfd, MAXBACKLOG) == -1)
    {
        perror("Couldn't listen\n");
        return;        
    }
    
    while(1)
    {
        int sin_size = sizeof(struct sockaddr);
        
        if((new_fd = accept(sockfd, (struct sockaddr*) &client_addr, &sin_size)) == -1)
        {
            printf("error in accepting connection, errno %d\n", errno);
        }
        else
        {
            printf("new fd after getting connection %d\n", new_fd);
        }

        printf("waiting to read from client\n");

        bytes = recv(new_fd, buf, sizeof(buf), 0);
        if (bytes == -1){
            perror("RECV ERROR: \n");
            close(new_fd);
            close(sockfd);
            exit(1);
        }
        else {
            printf("DATA RECEIVED = %s\n", buf);
        }
        
        printf("Sending data to client\n");
        memset(buf, 0, sizeof(buf));
        strcpy(buf, "Hello Client, you just got served :)");
        
        if(send(new_fd, buf, sizeof(buf), 0) != 0)
        {
            printf("error in sending data, errno %d", errno);
        }
        else
        {
            printf("new fd after getting connection %d", new_fd);
        }

        close(new_fd);
        sleep(1);        
    }
    
    close(sockfd);
    
    return 0;
}
/******* Output **********
 * socket creation passed sockfd 3
 * new fd after getting connection 4
 * waiting to read from client
 * DATA RECEIVED = Hello Server, Hope you serve me well
 * Sending data to client
