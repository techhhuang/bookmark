#include <stdio.h>
#include <stdlib.h>

struct wl_display;
struct wl_display;
struct wl_display
{
    int id;
    int version;
};


typedef struct wl_display my_display;

int main()
{
    struct wl_display display;
    display.id=1;
    display.version=2;
    my_display *dpy=malloc(sizeof(struct wl_display));
    printf("the lenght of wl_display is:%d\n",(int)sizeof(my_display));
    dpy->id=3;
    printf("id=%d ,version=%d\n",dpy->id,dpy->version);
    printf("id=%d ,version=%d\n",display.id,display.version);
}
