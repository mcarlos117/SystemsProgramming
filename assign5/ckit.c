#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 5000

int main(int argc, char *argv[]){
    int n,fdin1,fdin2,fdout;
    char buf[BUFSIZE];

    if (argc == 3){
        if (((strcmp(argv[1],"-"))==0) && ((strcmp(argv[2],"-"))==0)){
            write(STDERR_FILENO,"Invalid\n",8);
            exit(1);
        }else if(strcmp(argv[1],"-")==0 ){
            fdin2 = open(argv[2],O_RDONLY);
            if(fdin2 == -1){
                perror(argv[2]);
                exit(1);
            }
            while(((n = read(STDIN_FILENO, buf, BUFSIZE))>0) || ((n = read(fdin2,buf,BUFSIZE))>0) ) {
                write(STDOUT_FILENO,buf,n);
            }
        }else if(strcmp(argv[2],"-")==0){
            fdin1 = open(argv[1],O_RDONLY);
            if(fdin1 == -1){
                perror(argv[1]);
                exit(1);
            }
            while( ((n=read(fdin1,buf,BUFSIZE))>0) || ((n = read(STDIN_FILENO, buf, BUFSIZE)) >0) ) {
                write(STDOUT_FILENO,buf,n);
            }
        }else if (((strcmp(argv[1],"-"))==0) && ((strcmp(argv[2],"-"))==0)){
            write(STDERR_FILENO,"Invalid",7);
            exit(1);
        }else{
            fdin1 = open(argv[1],O_RDONLY);
            if(fdin1 == -1){
                perror(argv[1]);
                exit(1);
            }
            fdin2 = open(argv[2],O_RDONLY);
            if(fdin2 == -1){
                perror(argv[2]);
                exit(1);
            }
            while(((n = read(fdin1,buf,BUFSIZE))>0) || ((n = read(fdin2,buf,BUFSIZE))>0) ){
                write(STDOUT_FILENO,buf,n);
            }
            if(n < 0){
                perror("read error");
                exit(1);
            }
        }
    }
    else if(argc == 4){
        if (((strcmp(argv[1],"-"))==0) && ((strcmp(argv[2],"-"))==0)){
            write(STDERR_FILENO,"Invalid\n",8);
            exit(1);
        }else if(strcmp(argv[1],"-")==0 ){
            fdin2 = open(argv[2],O_RDONLY);
            if(fdin2 == -1){
                perror(argv[2]);
                exit(1);
            }
            fdout = open(argv[3],O_WRONLY|O_CREAT|O_APPEND,0600);
            if(fdout == -1){
                perror(argv[3]);
                exit(1);
            }
            while(((n=read(STDIN_FILENO, buf, BUFSIZE))>0) || ((n=read(fdin2,buf,BUFSIZE))>0) ) {
                write(fdout,buf,n);
            }
        }else if(strcmp(argv[2],"-")==0){
            fdin1 = open(argv[1],O_RDONLY);
            if(fdin1 == -1){
                perror(argv[1]);
                exit(1);
            }
            fdout = open(argv[3],O_WRONLY|O_CREAT|O_APPEND,0600);
            if(fdout == -1){
                perror(argv[3]);
                exit(1);
            }
            while( ((n=read(fdin1,buf,BUFSIZE))>0) || ((n=read(STDIN_FILENO, buf, BUFSIZE)) >0) ) {
                write(fdout,buf,n);
            }
        }else{
            fdin1 = open(argv[1],O_RDONLY);
            if(fdin1 == -1){
                perror(argv[1]);
                exit(1);
            }
            fdin2 = open(argv[2],O_RDONLY);
            if(fdin2 == -1){
                perror(argv[2]);
                exit(1);
            }
            fdout = open(argv[3],O_WRONLY|O_CREAT|O_APPEND,0600);
            if(fdout == -1){
                perror(argv[3]);
                exit(1);
            }
            while( ((n = read(fdin1,buf,BUFSIZE))>0) || ((n = read(fdin2,buf,BUFSIZE))>0) ){
                write(fdout,buf,n);
            }
            if(n<0){
                perror("read error");
                exit(1);
            }
        }
    }else{
        write (STDERR_FILENO,"Usage: ", 7);
        write (STDERR_FILENO,argv[0],strlen(argv[0]));
        write(STDERR_FILENO," <input file> <input file> or <input file> <input file> <output file>\n", 72);
        exit(1);
        }
    exit(0);
}
