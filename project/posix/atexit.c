#include <stdio.h>
#include <stdlib.h>

void my_exit1(void)
{
        printf("exit 1 is executed!\n");
}
int main(void)
{
        atexit(my_exit1);
        atexit(my_exit1);
        printf("main is done!\n");
        _exit(0);
}
