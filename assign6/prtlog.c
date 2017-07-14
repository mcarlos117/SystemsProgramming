#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include "pcap.h"
#include "dnet.h"
#include "prtlog.h"
#define BUFSIZE 66000

struct pcap_file_header pfh;
struct timev tmev;
struct my_pkthdr phdr;

struct eth_hdr ethdr;
struct arp_hdr aphdr;
struct ip_hdr iphdr;

int main(int argc, char *argv[]){
    int n,fd;
    int count = 0;
    int b_usec,c_usec;
    int x,y,z;
    unsigned int b_sec,c_sec;
    int firsttime = 1;
    char body[66000];
    fd = open (argv[1], O_RDONLY);
    if(fd == -1){
        perror(argv[1]);
        exit(1);
    }
    read(fd, &pfh ,24);

    if(pfh.magic == PCAP_MAGIC){
        printf("PCAP_MAGIC\n");
        printf("Version major number = %u\n",pfh.version_major );
        printf("Version minor number = %u\n",pfh.version_minor );
        printf("GMT to local correction = %u\n",pfh.thiszone );
        printf("Timestamp accuracy= %u\n",pfh.sigfigs );
        printf("Snaplen = %u\n",pfh.snaplen );
        printf("Linktype = %u\n\n",pfh.linktype );
   }

    while( (n = read(fd, &phdr, sizeof(struct my_pkthdr))) == sizeof(struct my_pkthdr)){
        x = 0;
        y = 0;
        z = 0;
        printf("Packet %d\n",count++);

        if(firsttime){
            firsttime = 0;
            b_sec = phdr.ts.tv_sec;
            b_usec = phdr.ts.tv_usec;
        }
        c_sec = (unsigned) phdr.ts.tv_sec - b_sec;
        c_usec = (unsigned) phdr.ts.tv_usec - b_usec;
        while(c_usec < 0){
            c_usec += 1000000;
            c_sec--;
        }
        printf("%05u.%06u\n", (unsigned)c_sec, (unsigned)c_usec);
        printf("Captured Packet Length = %d\n", phdr.caplen);
        printf("Actual Packet Length = %d\n", phdr.len);
        printf("Ethernet Header\n");

        if( (x = read(fd,&ethdr,sizeof(struct eth_hdr))) == sizeof(struct eth_hdr) ) {
            if(ntohs(ethdr.eth_type) == ETH_TYPE_IP){
                printf("   IP\n");
                if( (z = read(fd, &iphdr, sizeof(struct ip_hdr))) == sizeof(struct ip_hdr) ){
                    if(iphdr.ip_p ==  IP_PROTO_ICMP){
                        printf( "      ICMP\n\n" );
                    }
                    else if(iphdr.ip_p ==  IP_PROTO_IGMP){
                        printf( "      IGMP\n\n" );
                    }
                    else if(iphdr.ip_p ==  IP_PROTO_TCP){
                        printf( "      TCP\n\n" );
                    }
                    else if(iphdr.ip_p ==  IP_PROTO_UDP){
                        printf( "      UDP\n\n" );
                    }else{
                        printf("       UNRECOGNIZED\n\n");
                    }
                }
            }else if (ntohs(ethdr.eth_type) == ETH_TYPE_ARP){
                printf("   ARP\n");
                if( (y = read(fd, &aphdr, sizeof(struct arp_hdr))) == sizeof(struct arp_hdr) ){
                    if(ntohs(aphdr.ar_op) == ARP_OP_REQUEST){
                        printf("      arp operation = Arp Request \n\n");
                    }
                    else if(ntohs(aphdr.ar_op) == ARP_OP_REPLY){
                        printf("      arp operation = Arp Reply \n\n");
                    }
                    else if(ntohs(aphdr.ar_op) == ARP_OP_REVREQUEST){
                        printf("      arp operation = Arp Revrequest \n\n");
                    }
                    else if(ntohs(aphdr.ar_op) == ARP_OP_REVREPLY){
                        printf("      arp operation = Arp Revreply \n\n");
                    }else{
                        printf("      UNRECOGNIZED\n\n");
                    }
                }
            }

        }
        if((read(fd, body, phdr.caplen - x - y - z) != phdr.len - x - y -z))
            exit(-1);
    }
}
