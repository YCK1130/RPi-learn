#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main() {
    // 建立子行程
    char userCommand[256];
    while(1){
        printf("Please enter a file path to exec: ");
        scanf("%s",userCommand);
        if(strcmp(userCommand,"quit")==0)break;
        pid_t pid_c=fork();
        if(pid_c==0){
            if(strcmp(userCommand,"ls")==0)execl("/bin/ls","ls",NULL);
            if(strcmp(userCommand,"ll")==0)execl("/bin/ls","ls","-l",NULL);
            if(strcmp(userCommand,"pwd")==0)execl("/bin/pwd","pwd",NULL);
            if(strcmp(userCommand,"sh")==0)execl("/bin/sh","sh",NULL);
            else return execl(userCommand,"",NULL);
        }
        int status;
        waitpid(pid_c,&status,0);
        printf("Child return : %d\n\n",status);
    }


  return 0;
}