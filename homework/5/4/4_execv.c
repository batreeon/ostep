#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *args[] = {"ls", NULL};
        if(execv("/bin/ls", args) == -1) {
            printf("execl failed!\n");
        }
    }
    return 0;
}