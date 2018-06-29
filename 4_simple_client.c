#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#define MAXSIZE 128
int main()
{
    struct addrinfo hints;
    struct addrinfo *res, *p;
    struct sockaddr_in* sain;
    struct sockaddr client_addr;
    
    struct in_addr* addr;
    char buf[MAXSIZE];
    int sockfd, num_bytes;
    
    memset(&hints, 0, sizeof(hints));
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo("127.0.0.1", "3409", &hints, &res) != 0)
    {
        perror("get_addrinfo failed");
        return -1;        
    }

    /*
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
    */
    if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
    {
        printf("socket creation failed errno%d sockfd %d", errno,sockfd);
        perror("Failure");
        
        return;        
    }


    if(connect(sockfd, res->ai_addr, res->ai_addrlen) == -1)
    {
        printf("Couldn't connect errno %d", errno);
        perror("Failure");
        close(sockfd);
        return;        
    }
    printf("Connected to server\n");
    
    if((num_bytes = recv(sockfd, buf, MAXSIZE, 0)) == -1)
    {
        printf("error in receiving data, errno %d", errno);
        perror("Failure");
        return;
        
    }
    buf[num_bytes] = '\0';
    printf("bytes received %s\n", buf);
    close(sockfd);    
    return 0;
}
