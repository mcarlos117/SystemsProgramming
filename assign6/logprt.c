#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include "logprt.h"

struct pcap_file_header pfh;
struct timev tmev;
struct my_pkthdr phdr;

int main(int argc, char *argv[]){
    int n,fd,count = 0;
    int b_usec,c_usec;
    char body [4096];
    unsigned int b_sec,c_sec;
    int firsttime = 1;
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
        printf("Actual Packet Length = %d\n\n", phdr.len);
        if(read(fd, body, phdr.caplen) != phdr.len)
            exit(-1);
    }
}
