#include<stdio.h>


__attribute__((visibility("default"))) void visible()
{
    printf("symbol will be visible\n");
}

void hidden()
{
    printf("sysmbol will be hidden\n");
}
