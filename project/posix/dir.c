#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char buff[512];
    printf("current cwd is:%s\n", getcwd(buff, 512));
    chdir("/home/saic");
    printf("current cwd is:%s\n", getcwd(buff, 512));

//    printf("current dir name is :%s\n",get_current_dir_name());
//    printf("current wd is:%s\n",getwd(buff));
    return 0;
}
