#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string.h>

int main(){
    int ssock,csock;
    struct sockaddr_in server,client;
    int len;

    ssock=socket(AF_INET,SOCK_STREAM,0);
    if(ssock==-1){
        perror("Socket not created\n");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(10000);
    server.sin_addr.s_addr=INADDR_ANY;
    bzero(&server.sin_zero,0);

    len=sizeof(struct sockaddr_in);

    if(bind(ssock,(struct sockaddr*)&server,len)==-1){
        perror("Binding not possible\n");
        exit(-1);
    }
    if(listen(ssock,5)==-1){
        perror("Not listening\n");
        exit(-1);
    }

    csock=accept(ssock,(struct sockaddr*)&client,&len);
    if(csock==-1){
        perror("Client not listening\n");
        exit(-1);
    }

    char s[100];
    char t[100]="Hello World";
    recv(csock,&s,sizeof(s),0);
    printf("%s\n",s);
    send(csock,&t,sizeof(t),0);

}
