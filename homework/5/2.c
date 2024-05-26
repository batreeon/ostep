#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int m = mkdir("./input", S_IRWXU);
    if (m == -1 && errno != EEXIST) {
        printf("mkdir failed!\n");
        exit(1);
    }
    int fd = open("./input/2test", O_CREAT | O_RDWR, S_IRWXU);
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *s = "abc";
        write(fd, s, 3);
        s = "def";
        write(fd, s, 3);
        s = "ghi";
        write(fd, s, 3);
    }else{
        char *s = "123";
        write(fd, s, 3);
        s = "456";
        write(fd, s, 3);
        s = "789";
        write(fd, s, 3);

        int wc = wait(NULL);

        lseek(fd, 0, SEEK_SET);
        char buf[128];
        if (read(fd, buf, 18) == -1) {
            printf("read failed");
            close(fd);
            exit(1);
        }
        printf("output: %s\n", buf);
        close(fd);
    }

    return 0;
}