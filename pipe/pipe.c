#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
char buf[1024];
int main(){
    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid==0){
        
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","./",NULL);
    }
    close(fd[1]);
    read(fd[0],buf,sizeof buf);
    write(1,buf , sizeof buf);
    close(fd[0]);
}