#include<unistd.h>
#include<stdio.h>
int main()
{
    char hostname[128];
    if(gethostname(hostname, sizeof(hostname)) == 0)        
    {
        printf("hostname: %s\n", hostname);
    }
    else
    {
        printf("couldn't get hostname");
    }   

    printf("username: %s\n", getlogin());
    return 0;
}

/***** Output ****
[sumit@null-38d54710b430 sockets]$ gcc 1_hostname.c -o 1_hostname.o
[sumit@null-38d54710b430 sockets]$ ./1_hostname.o
hostname: null-38d54710b430.us.alcatel-lucent.com
username: sumit
*/
   
            
    
