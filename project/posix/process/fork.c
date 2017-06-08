#include <stdio.h>
#include <unistd.h>

int global_var=6;

int main(void)
{
        pid_t pid;
        int var=88;
        if ((pid = fork()) < 0) {
                printf("fork error");
        }
        if (pid == 0){
                global_var++;
                var++;
                printf("child pid is : %d global is:%d local is:%d\n",getpid(),global_var,var);
                sleep(20);
        } else { 
                printf("parent pid is : %d global is:%d local is:%d\n",getpid(),global_var,var);
        }
}
