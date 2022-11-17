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
    while(1){
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        receiveLen=recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        send(forClientSockfd,message,sizeof(message),0);
        printf("Get:%s\nreceiveLen:%d\n",inputBuffer,receiveLen);
        
        // memset(inputBuffer, 0, sizeof(inputBuffer));
        printf("Get: %s\n",inputBuffer);
        recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        printf("Get: %s\n",inputBuffer);
        if(inputBuffer[0]=='y'){
            char msg[]="nah, I'm not ready";
            send(forClientSockfd,msg,sizeof(msg),0);
        }
        else{
            char msg[]="what a shame, bye";
            send(forClientSockfd,msg,sizeof(msg),0);

        }
        char disconnect[]={"disconnect"};
        printf("%s\n",disconnect);
        send(forClientSockfd,disconnect,sizeof(disconnect),0);

    }
    return 0;
}