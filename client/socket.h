
int server_init(void);

#define BUFFER_SIZE 255
struct socket_data {
    int id;
    int socket;
    char name[BUFFER_SIZE];
    char buff[BUFFER_SIZE*10];
    
};
