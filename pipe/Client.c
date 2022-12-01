#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //import inet_addr()

int main(int argc , char *argv[]){

    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
        exit(1);
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8700);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
        exit(1);
    }


    //Send a message to server
    char message[] = {"Hi there"};
    char msg[]={"Hi it's me again"};
    char receiveMessage[1024] = {};
    send(sockfd,message,sizeof(message),0);
    recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
    printf("%s",receiveMessage);

    char userCommand[256];
    while(1){
        int num;
        printf("Please enter a command: ");
        scanf("%s",userCommand);
        send(sockfd,userCommand,sizeof(userCommand),0);

        // memset(receiveMessage, 0, sizeof(receiveMessage));
        recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
        printf("%s\n",receiveMessage);

        send(sockfd,receiveMessage,sizeof(receiveMessage),0);

        recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
        printf("%s\n",receiveMessage);
        
        // printf("%s , %s\n",playGame,receiveMessage);
        if(strcmp(receiveMessage,"disconnect")==0){
            send(sockfd,"k",sizeof("k"),0);
            break;
        }
        
        printf("%s\n",receiveMessage);
    }
    printf("close Socket\n");

    close(sockfd);
    return 0;
}