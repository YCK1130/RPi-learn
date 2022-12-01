#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //import inet_addr()

int main(int argc , char *argv[]){
    srand(5);
    //socket的建立
    char inputBuffer[256] = {};
    char message[] = {"Server connected.\n"};
    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
        exit(1);
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    int addrlen = sizeof(clientInfo);
    int PORT = 8700;
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(PORT);
    if(bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo))!=0){
        perror("bind()");
        exit(1);
    }
    if(listen(sockfd,5)!=0){
        perror("listen()");
        exit(1);
    }
    printf("Listening on file descriptor %d, at Port %d.\n",sockfd,serverInfo.sin_port);
    int receiveLen;
    char knownCommand[] = {"add123"};
    while(1){
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        receiveLen=recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        send(forClientSockfd,message,sizeof(message),0);
        printf("Get:%s\nreceiveLen:%d\n",inputBuffer,receiveLen);
        
        // memset(inputBuffer, 0, sizeof(inputBuffer));
        // printf("Get: %s\n",inputBuffer);
        recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        printf("1Get: %s\n",inputBuffer);
        printf("1Get: %s\n",inputBuffer);
        // write(1,"hihihi\n",sizeof"hihihi\n");
        if(strcmp(inputBuffer,knownCommand)==0){
            char buf[1024]={};
            int fd[2];
            pipe(fd);
            pid_t pid_c=fork();
            if(pid_c==0){
                close(fd[0]);
                dup2(fd[1],STDOUT_FILENO);
                // int six = 1+2+3;
                // printf("%d",six);
                execl("./add123",NULL);
                exit(0);
            }
            close(fd[1]);
            read(fd[0],buf,sizeof buf);
            write(1,buf , sizeof buf);
            send(forClientSockfd,buf,sizeof(buf),0);
            int status;
            waitpid(pid_c,&status,0);
            if(status==0)
                write(1,"Child return successfullly",sizeof "Child return successfullly");
            else
                write(1,"something went wrong",sizeof "something went wrong");
            
        }
        else{
            char msg[]="sorry I don't know what you say";
            write(1,msg,sizeof msg);
            send(forClientSockfd,msg,sizeof(msg),0);
        }
        printf("disconnect1\n");
        printf("disconnect2\n");

        send(forClientSockfd,"disconnect",sizeof("disconnect"),0);
        recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        while(strcmp(inputBuffer,"k")!=0){
            printf("disconnect\n");
            send(forClientSockfd,"disconnect",sizeof("disconnect"),0);
            recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        
        }

    }
    return 0;
}