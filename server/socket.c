#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "socket.h"
#include "mealsys.h"

#define SERVER_PORT 20001

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void daccept(int socket_bind);

int server_init(void)
{
    int sock_server = 0, sock_client = 0;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    int len = 0;


    if ((sock_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        debug("socket error\n");
        exit(1);
    } else {
        debug("socket ok\n");
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if ((bind(sock_server, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
        debug("bind error\n");
        exit(1);
    } else {
        debug("bind ok\n");
    }

    if ((listen(sock_server, 5)) < 0) {
        debug("listen error\n");
        exit(1);
    } else {
        debug("listen ok\n");
    }

    daccept(sock_server);
    return 0;
}

void *thread_handler(struct socket_data *data) //看多线程是不是可以用同一个handler函数。
{
    struct socket_data client_data;
    int len = 0;

    client_data = *data;
    pthread_mutex_unlock(&mutex);

    memset(client_data.buff,0,sizeof(client_data.buff));
    len = read(client_data.socket, client_data.buff, 1);

    printf("this is table :%d\n", client_data.buff[0]);

    memset(client_data.buff,0,sizeof(client_data.buff));

    len = read(client_data.socket, client_data.buff, BUFFER_SIZE);
    //while((len = read(client_data.socket, client_data.buff, BUFFER_SIZE)) > 0)
    //{
        switch(client_data.buff[0])
        {
            case 0:
                break;
                debug("this is the meal list \n");
            case 1:
                break;
                debug("meal ok\n");
            case 2:
                debug("requist server\n");
                break;
            default:
                break;
        }
        //printf("receive client %d :%s\n",client_data.socket, client_data.buff);
        //write(client_data.socket, client_data.buff, len);
        //memset(client_data.buff, 0, len);
   //} while

    printf("the socket is:%d\n", client_data.socket);
    sqlite_read(&client_data);

    debug("this client exit\n");
    close(client_data.socket);

    // 每个线程的handler一样，但传进来的参数不一样。数据结构不一样，每一个线程都有自己的数据结构。
    // 每个线程创建时同时创建它的数据结构，以其线程号为后缀，以参数形式传个handler。
    //每个线程应该做的事。
    //read_data_bass() // 读数据库。
    //sendmsg（） //发送菜单。
    //while(readmsg() > 0) //一直等待client的消息。
    //{
        //switch()  //对消息进行解析，看是点好的菜单，还是呼唤服务员
        //{
        //}
        //}
}

void daccept(int socket_bind)
{
    int socket_client;
    int ret = 0;
    fd_set fds_set;
    int max_fds;
    struct timeval timeout = {3, 0};

    struct socket_data sock_data;
    int i = 0;

    int ret_thread = 0;
    pthread_t tid = 0;
    pthread_attr_t attr;
    int err = 0;

// 初始化sqlite
    sock_data.db = sqlite_init(); 

//初始化attr结构，是创建的线程为分离状态，退出时自动回收线程资源
    err = pthread_attr_init(&attr);
    if( !err ) 
        debug("pthread attr init error");
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if( !err ) 
        debug("pthread attr set detachstate error"); 
    while(1)
    {
        FD_ZERO(&fds_set);
        FD_SET(socket_bind, &fds_set);
        max_fds = socket_bind;

        ret = select(max_fds+1, &fds_set, NULL , NULL, &timeout); //对socketserver进行select，等待链接时不阻塞。
        if(ret < 0) {
            debug("select error\n");
        } else if(ret == 0) {

        } else {
            debug("select ok\n");
            if(FD_ISSET(socket_bind, &fds_set)) {
                debug("accept one client\n");
                if ( (socket_client = accept(socket_bind, NULL, NULL)) < 0) {
                    debug("accept error\n");
                    exit(1);
                } else {
                    debug("accept ok\n");
                    printf("socket:%d\n",socket_client);
                }

                pthread_mutex_lock(&mutex);// 加入互斥锁，在线程中再解锁
                sock_data.socket = socket_client;
                ret_thread = pthread_create(&tid, &attr,(void *)thread_handler, &sock_data);
                if(ret_thread != 0) {
                    debug("pthread create error\n");
                } else {
                    debug("pthread create ok");
                }
                /* 新建线程，与client通信
                    pthread_creat(); //当有连接时，新建线程
                 *
                 *
                 *
                 */
            }
        }

        //if ( (sock_client = accept(sock_server, NULL, NULL)) < 0) {
        //printf("accept error\n");
        //exit(1);
        //} else {
        //printf("accept ok\n");
        //}
        //
        //pthread_cancle();  //等待线程结束，也不能阻塞。
    }

    sqlite_close(sock_data.db);

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
