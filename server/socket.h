#include <sqlite3.h>

#define BUFFER_SIZE 255
struct socket_data {
    int id;
    int socket;
    char name[BUFFER_SIZE];
    char buff[BUFFER_SIZE*10];
    sqlite3 *db;
};

int server_init(void);
sqlite3 * sqlite_init(void);
void sqlite_read(struct socket_data *data);
void sqlite_close(sqlite3 *db);

