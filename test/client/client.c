
/***************************************************************************
* Module Name   : client.c                                                   
* Identification:                                                  
* Date          : 2010.09.04                                          
*                                                                        
* Author        : Yu Lianqing                                           
*                                                                        
* Copyright (c)                          
* ALL RIGHTS RESERVED                                                
*                                                                         
* Revisions of %M% :                                                    
* #.##   Name         Date          Description                        
* ----   ------------ ------------- ----------------------------------- 
*                                                                         
* Description   : network client demo program in TCP mode.
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE];

//
//
int main(int argc, char *argv[])
{
	int n,len;
	int client_sock;
	socklen_t server_len;
	struct sockaddr_in server;

	if(argc < 2)
	{
		printf("\n");
		printf("Sorry, your type is wrong.\n");
		printf("Usage: %s x.x.x.x(server IP)\n", argv[0]);
		printf("\n");
		exit(EXIT_FAILURE);
	}

	// 1. create socket - create an endpoint for communication 
	// int socket(int domain, int type, int protocol) 
	if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create socket ok!\n");
	}

	// 2. connect - initiate a connection on a socket 
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	bzero(&server, sizeof(server));
//	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(argv[1]);
//	inet_aton(argv[1], &server.sin_addr);

	server_len = sizeof(server);
	if(connect(client_sock, (struct sockaddr *)&server, server_len) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("connect server ok!\n");
	}

	// communication with server
        //if((len = read(client_sock, buffer, len)) > 0)
        //{
        char *ptr = NULL;
        int *len1 = NULL;
        buffer[0] = 23;
        char name[256] = {0};
        char info[256] = {0};

        int err = 0;

		n =	write(client_sock, buffer, 1);

        buffer[0] = 2;
		n =	write(client_sock, buffer, 1);

        printf("hello yaomoon\n");


        //len = read(client_sock, buffer, len);
        //err = errno;

        //printf("len of buffer%d\n",len);
        //printf("error of read%d\n",err);


        //return 0;
        while((len = read(client_sock, buffer, 256)) > 0) {


            ptr = buffer;
            //printf("id = %d\n",*((int *)ptr));
            printf("%d ",*((int *)ptr));
            ptr+=4;

            len1 = (int *)ptr;
            //printf("len of name is :%d \n", *len1);
            ptr+=4;

            strncpy(name, ptr, *len1);
            //printf("name is :%s\n",name);
            printf("%s ",name);
            ptr+=*len1;

            //printf("price = %d\n",*((int *)ptr));
            printf("%d ",*((int *)ptr));
            ptr+=4;

            len1 = (int *)ptr;
            //printf("len of info is :%d \n", *len1);
            ptr+=4;

            strncpy(info, ptr, *len1);
            //printf("info is :%s\n",info);
            printf("%s\n",info);

            memset(buffer, 0, sizeof(buffer));
            memset(name, 0, sizeof(name));
            memset(info, 0, sizeof(info));

        }

            //}

	close(client_sock);

	exit(EXIT_SUCCESS);
}
#if 0
int main(int argc, const char *argv[])
{
    sqlite3 *db;
    char buff[256] = {0};
    char name[100] = {0};
    char info[256] = {0};
    int *len = NULL;

    struct socket_data sock_data;
    char *ptr = sock_data.buff;

    db = sqlite_init();

    sqlite_read(db, &sock_data);

    printf("id = %d\n",*((int *)ptr));
    ptr+=4;

    len = (int *)ptr;
    //printf("len of name is :%d \n", *len);
    ptr+=4;

    strncpy(name, ptr, *len);
    printf("name is :%s\n",name);
    ptr+=*len;

    printf("price = %d\n",*((int *)ptr));
    ptr+=4;

    len = (int *)ptr;
    //printf("len of info is :%d \n", *len);
    ptr+=4;

    strncpy(info, ptr, *len);
    printf("info is :%s\n",info);


    sqlite_close(db);
    
    return 0;
}
#endif

