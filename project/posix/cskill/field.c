#include <stdio.h>

struct
{
    unsigned int a:1;
    unsigned int b:2;
}prnt;
int main(void)
{
    struct prnt p1;
    p1.a=1;
    p1.b=1;
    printf("the size of prnt is :%d\n",sizeof(prnt));
}
