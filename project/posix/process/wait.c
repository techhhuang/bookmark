#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
        pid_t pid;
        if ((pid = fork()) < 0) {
                printf("fork error \n");
        } else if (pid == 0) {
                printf("child process is running....\n");
                sleep(3);
                printf("child process is exiting....\n");
                //                _exit(0);
        }
        printf("before wait！\n");
        int status;
        if (wait(&status) != pid) {
                printf("wait error!\n");
        }
        printf("after wait! \n");
}
