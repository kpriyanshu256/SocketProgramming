#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    int sock;
    struct sockaddr_in client;

    sock=socket(AF_INET,SOCK_STREAM,0);

    client.sin_family=AF_INET;
    client.sin_port=htons(10000);
    client.sin_addr.s_addr=INADDR_ANY;
    bzero(&client.sin_zero,0);

    int len=sizeof(struct sockaddr_in);

    if(connect(sock,(struct sockaddr*)&client,len)==-1){
        perror("Connection\n");
        exit(-1);
    }
    char s[100]="PF";
    char t[100];
    send(sock,&s,sizeof(s),0);
    recv(sock,&t,sizeof(t),0);
    printf("%s\n",t);

}
