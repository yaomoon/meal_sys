
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 20000
#define BUFFER_SIZE 256


int socket_init()
{

    return 1;
    int sock_server = 0, sock_client = 0;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    int len = 0;

    if ((sock_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error\n");
        exit(1);
    } else {
        printf("socket ok\n");
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if ((bind(sock_server, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
        printf("bind error\n");
        exit(1);
    } else {
        printf("bind ok\n");
    }

    if ((listen(sock_server, 5)) < 0) {
        printf("listen error\n");
        exit(1);
    } else {
        printf("listen ok\n");
    }

    daccept();

    return 0;
}

void daccept()
{

    select();
    
    //if ( (sock_client = accept(sock_server, NULL, NULL)) < 0) {
    //printf("accept error\n");
    //exit(1);
    //} else {
    //printf("accept ok\n");
    //}

}

void recv_meg()
{

    //while ((len = read(sock_client, buffer, BUFFER_SIZE)) > 0)
    //{
    //if ((write(sock_client, buffer, len)) < 0) {
    //printf("send messages error\n");
    //continue;
    //} else {
    //printf("send messages ok, the message is:%s\n", buffer);
    //}
    //}

    //return 0;
}
