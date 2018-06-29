#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include <netdb.h>
int main()
{
    struct addrinfo hints;
    struct addrinfo *res, *p;
    struct sockaddr_in* sain;
    struct in_addr* addr;
    char ipv4str[INET_ADDRSTRLEN];
    
    char url[28];    
    strcpy(url, "www.google.com");
    printf("Url : %s\n", url);
    memset(&hints, 0, sizeof(hints));
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(url, NULL, &hints, &res) != 0)
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
    return 0;
}
/******* Output ******
[sumit@null-38d54710b430 sockets]$ gcc 2_getaddrinfo.c -o 2_getaddrinfo.o
[sumit@null-38d54710b430 sockets]$ ./2_getaddrinfo.o
Url : www.google.com
IPv4 address: 108.177.122.103
IPv4 address: 108.177.122.104
IPv4 address: 108.177.122.99
IPv4 address: 108.177.122.105
IPv4 address: 108.177.122.147
IPv4 address: 108.177.122.106
*/
    
    
