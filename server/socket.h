
int socket_init();

#define BUFFER_SIZE 255
struct socket_data {
    int id;
    char name[BUFFER_SIZE];
    char buff[BUFFER_SIZE*10];
    
}
