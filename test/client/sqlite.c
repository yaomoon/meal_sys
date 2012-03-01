#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#include "socket.h"
#include "mealsys.h"

int callfun(void *p, int argc, char **argv, char **argvv)
{
    struct socket_data sock_data = *((struct socket_data *)p);
    char *ptr = sock_data.buff;
    int name_len = 0;
    int info_len = 0;

    memset(sock_data.buff,0,strlen(sock_data.buff));

    sscanf(argv[0], "%d", (int *)ptr);
    ptr+=4;

    name_len = strlen(argv[1]);
    *((int *)ptr) = name_len;
    ptr+=4;
    strcpy(ptr,argv[1]);
//
//printf("%d\n",len);
//
    ptr+=name_len;

    sscanf(argv[2], "%d", (int *)ptr);
    ptr+=4;

    info_len = strlen(argv[3]);
    *((int *)ptr) = info_len;
//
//printf("%s\n",argv[3]);
//printf("%d\n",len);
//
    ptr+=4;
    strcpy(ptr,argv[3]);
    ptr+=info_len;

    write(sock_data.socket, sock_data.buff, name_len+info_len+4*4);

    return 0;
}

sqlite3 * sqlite_init(void)
{
    sqlite3 *db;
    char *err = 0;
    int ret = 0;
    int empty = 1;

    ret = sqlite3_open("./mealsys.db", &db);
    if(ret != SQLITE_OK) {
        printf("open error\n");
        exit(1);
    }

    return db;
}
void sqlite_read(struct socket_data *data)
{
    char *err = 0;
    int ret = 0;

    ret = sqlite3_exec(data->db, "select * from meallist where id=4;", callfun, data, &err);
    if(ret != SQLITE_OK) {
        printf("exec error\n");
        fputs(err, stderr);
        fputs("\n", stderr);
        exit(1);
    }
}
void sqlite_close(sqlite3 *db)
{
    sqlite3_close(db);
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
# endif



