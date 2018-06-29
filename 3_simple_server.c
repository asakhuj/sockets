#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#define MAXBACKLOG 2
int main()
{
    struct addrinfo hints;
    struct addrinfo *res, *p;
    struct sockaddr_in* sain;
    struct sockaddr client_addr;
    
    struct in_addr* addr;
    char ipv4str[INET_ADDRSTRLEN];
    int sockfd, new_fd, yes=1;
    
    memset(&hints, 0, sizeof(hints));
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo("127.0.0.1", "3409", &hints, &res) != 0)
    {
        printf("get_addrinfo failed");
        return -1;        
    }

    
    p = res;
    while(p)
    {
        if(p->ai_family == AF_INET)
        {
            sain = (struct sockaddr_in*)p->ai_addr;
            addr = &sain->sin_addr;
        }
        inet_ntop(p->ai_family, addr, ipv4str, sizeof(ipv4str));        
        printf("IPv4 address: %s\n", ipv4str);
        p = p->ai_next;        
    }
    free(p);
    
    if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        printf("socket creation failed errno%d sockfd %d", errno,sockfd);
        return;        
    }
    else
    {
        printf("socket creation passed sockfd %d\n errno %d", sockfd, errno);
    }
    
    
    if((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
    {
        perror("couldn't setsockopt ");
        return;        
    }

    if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1)
    {
        printf("Couldn't bind errno %d", errno);
        perror("Bind failed");
        
        return 0;        
    }
    else
    {
        printf("Bind to socket passed");
    }
    
    
    if(listen(sockfd, MAXBACKLOG) == -1)
    {
        perror("Couldn't listen");
        return;        
    }
    
    while(1)
    {
        int sin_size = sizeof(struct sockaddr);
        
        if((new_fd = accept(sockfd, (struct sockaddr*) &client_addr, &sin_size)) == -1)
        {
            printf("error in accepting connection, errno %d", errno);
        }
        else
        {
            printf("new fd after getting connection %d", new_fd);
        }
        
        if(send(new_fd, "Hello Earth", 12, 0) != 0)
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
    free(res);
    
    return 0;
}
