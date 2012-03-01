#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "socket.h"

int main(int argc, const char *argv[])
{
    pid_t pid = 0, pid2;
    int status;
    
    //data_base_init();
    pid = fork();
    if(pid < 0) {
        printf("create new process failed\n");
        exit(1);
    } else if (pid == 0) {
        printf("this is the child process\n");
        server_init();
        exit(1);
    } else {
        printf("this is the parent process\n");
        sleep(4);
    }
    pid2 = pid = waitpid(pid,&status,0);
    printf("chiled pid = %d\n",pid2);
    printf("helloyaomoon\n");
    return 0;
}
