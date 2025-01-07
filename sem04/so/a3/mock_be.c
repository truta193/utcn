
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_BUFFER_SIZE 255
#define REQ_PIPE_NAME "REQ_PIPE_47947"
#define RESP_PIPE_NAME "RESP_PIPE_47947"

int main() {
    unlink(REQ_PIPE_NAME);
    unlink(RESP_PIPE_NAME);
    mkfifo(REQ_PIPE_NAME, 0644);
    int fd1 = open(REQ_PIPE_NAME, O_WRONLY);
    int fd2 = open(RESP_PIPE_NAME, O_RDONLY);

    char *a = strdup("ECHO#");
    char * buffer = malloc(255);

    write(fd1, a, 5);
    while(1) {
        read(fd2, buffer, 1);
        printf("%s\n", buffer);
    }
    return 0;
}