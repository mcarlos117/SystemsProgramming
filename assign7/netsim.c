#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define RAND_MAX 2147483647
main(void){
    int n,i,j,rng,num,parent;
    //pid_t  parent;
    int fdin,fdout;
    int fd[10][2];
    int id = 0;

    for(i = 0; i < 10; i++){
        if(pipe(fd[i])){
            perror("pipe error");
            exit(1);
        }
    }
    for(i = 0; i < 9; i++){
        switch(parent=fork()){
            case -1:                    //error case
                perror("fork error");
                exit(-1);
            case 0:                     //child case
                id = i;
                break;
        }
        if(parent)
            break;
    }
    for (i = 0; i < 10; i++){
            if(i == id){
                close(fd[i][1]);
            }//else{
                //close(fd[i][0]);
        //}
    }
    rng = RAND_MAX/10;
    rng *= 10;
    srand(1921739*id);
    for(n=0; n < 10; n++){
        do {
            num = rand();
            j = num%10;
        }
        while( num >= rng || id == j);
        if(write(fd[j][1],&id , sizeof(int)) < 0){
            perror("write error");
            exit(1);
        }
    }
    for(i = 0; i < 10; i++){
        if (id != i){
            close(fd[i][1]);
        }
    }
    while ( (n = read(fd[id][0], &j , sizeof(int)) ) > 0){
       printf("Process%d has recieved a message from process%d\n",id,j);
    }
    if(n == -1){
        perror("read error");
        exit(-1);
    }
    close(fd[id][0]);
    return(0);
}
