
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <socket.h>

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

void thread_handler() //看多线程是不是可以用同一个handler函数。
{
    // 每个线程的handler一样，但传进来的参数不一样。数据结构不一样，每一个线程都有自己的数据结构。
    // 每个线程创建时同时创建它的数据结构，以其线程号为后缀，以参数形式传个handler。
    //每个线程应该做的事。
    //read_data_bass() // 读数据库。
    //sendmsg（） //发送菜单。
    while(readmsg() > 0) //一直等待client的消息。
    {
       switch()  //对消息进行解析，看是点好的菜单，还是呼唤服务员。
       {
       }
    }
}

void daccept()
{

    select(); //对socketserver进行select，等待链接时不阻塞。
    

    pthread_creat(); //当有连接时，新建线程
    //if ( (sock_client = accept(sock_server, NULL, NULL)) < 0) {
    //printf("accept error\n");
    //exit(1);
    //} else {
    //printf("accept ok\n");
    //}
    //
    pthread_cancle();  //等待线程结束，也不能阻塞。

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
