#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

struct cmd {
    int redirect_in;
    int redirect_out;
    int redirect_append;
    int background;
    int piping;
    char *infile;
    char *outfile;
    char *argv1[10];
    char *argv2[10];
};

int main(void){
    char buff[1024];
    struct cmd command;

    printf("\n>> ");
    while ( (gets(buff) != NULL && strcmp(buff, "exit")) != 0){
        if(cmdscan(buff, &command)){
            printf("Illegal Format: \n");
            continue;
        }

        int fdin, fdout, fd[2];

        switch(fork()){
            case -1:
                perror("Fork Error");
                exit(-1);
            case 0:
                switch(fork()){
                    case -1:
                        perror("Fork Error");
                        exit(-1);
                    case 0:
                        if (command.redirect_in){
                            if( (fdin = open(command.infile, O_RDONLY)) == -1){
                                perror("Open error");
                                exit(-1);
                            }
                        }
                        int perms = O_WRONLY | O_CREAT | O_TRUNC;
                        if(command.redirect_append)
                            perms = O_WRONLY | O_CREAT | O_APPEND;
                        if(command.redirect_out){
                            if( (fdout = open(command.outfile,perms, 0600)) == -1){
                                perror("Open error");
                                exit(-1);
                            }
                        }
                        if(command.piping){
                            if(pipe(fd) == -1){
                                perror("Pipe error");
                                exit(-1);
                            }
                            switch(fork()){
                                case -1:
                                    perror("Fork error");
                                    exit(-1);
                                case 0:
                                    if(command.redirect_in){
                                        dup2(fdin, STDIN_FILENO);
                                        close(fdin);
                                    }
                                    if(dup2(fd[1],STDOUT_FILENO) == -1){
                                        perror("Dup error");
                                        exit(-1);
                                    }
                                    close(fd[1]);
                                    close(fd[0]);
                                    execvp(command.argv1[0],command.argv1);
                                    perror("Exec error");
                                    exit(-1);
                                default:
                                    if(command.redirect_out){
                                        dup2(fdout,STDOUT_FILENO);
                                        close(fdout);
                                    }
                                    if(dup2(fd[0], STDIN_FILENO) == -1){
                                        perror("Dup error");
                                        exit(-1);
                                    }
                                    close(fd[1]);
                                    close(fd[0]);
                                    execvp(command.argv2[0],command.argv2);
                                    perror("Exec error");
                                    exit(-1);
                            }
                        }
                        if(command.redirect_in){
                            dup2(fdin, STDIN_FILENO);
                            close(fdin);
                        }
                        if(command.redirect_out){
                            dup2(fdout, STDOUT_FILENO);
                            close(fdout);
                        }
                        execvp(command.argv1[0],command.argv1);
                        perror("Exec error");
                        exit(-1);
                    default:
                        if(command.background)
                            exit(0);
                        wait(NULL);
                        exit(0);
                }
                break;
            default:
                printf("\n>> ");
                wait(NULL);
        }
    }
    return(0);
}
