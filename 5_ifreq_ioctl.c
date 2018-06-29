#include<stdio.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

int main()
{
    struct ifreq ifreq_ip;
    char* interface = "enp5s0";
    int sock_raw;    
    printf("interface %s\n", interface);

    if((sock_raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
    {
        perror("Socket creation failure:");
    }

    memset(&ifreq_ip, 0, sizeof(ifreq_ip));
    strncpy(ifreq_ip.ifr_name, "enp5s0", IFNAMSIZ-1); //giving name of Interface
    
    if(ioctl(sock_raw, SIOCGIFHWADDR, &ifreq_ip) <0 ) //getting IP Address
    {
        perror("error in SIOCGIFADDR ");
        
    }
    
    char mac[ETH_ALEN];
    
    memcpy(mac, ifreq_ip.ifr_hwaddr.sa_data, ETH_ALEN);
    printf("Mac addr of %s is  %x.%x.%x.%x.%x.%x\n", ifreq_ip.ifr_name, mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    close(sock_raw);        
    return 0;

}

    

