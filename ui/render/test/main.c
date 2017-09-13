#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <wayland-client.h>
#include <wayland-server.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <sys/time.h>

#include <weston/WindowManager-client-protocol.h>

#include<GLES2/gl2.h>

#define NANOVG_GLES2_IMPLEMENTATION   // Use GL2 implementation.

#include "nanovg.h"
#include "nanovg_gl.h"
#include "nanovg_gl_utils.h"
#include "demo.h"
#include "perf.h"

#define WIDTH 960
#define HEIGHT 1280

double getTimeNow(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double time = tv.tv_sec*1000   + tv.tv_usec/1000 ;
    return time;
}

struct NVGcontext* vg;
DemoData ddata;
PerfGraph fps;

double prevt,nowt,t,t0=0,dt;

void draw(){
    nowt = getTimeNow();
    t= nowt - prevt;
    dt = t - t0;
    t0 = t;
     printf("time:%f  dt: %f\n",t/1000,dt/1000);
    updateGraph(&fps, dt/1000.0);
    glViewport(0, 0, WIDTH, HEIGHT);

    glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    nvgBeginFrame(vg, WIDTH, HEIGHT, 1);
    renderDemo(vg, 30,30, WIDTH,HEIGHT, t/1000.0, 0, &ddata);
    renderGraph(vg, 5,5, &fps);

    // nvgBeginPath(vg);
    // //nvgRect(vg, 100,100, 120,30);
    // nvgCircle(vg, 120,120, 50);
    // nvgPathWinding(vg, NVG_HOLE);   // Mark circle as a hole.
    // nvgFillColor(vg, nvgRGBA(255,192,0,255));
    // nvgFill(vg);

    nvgEndFrame(vg);
}
struct wl_display *display = NULL;
struct wl_compositor *compositor = NULL;
struct wl_surface *surface;
struct wl_egl_window *egl_window;
struct wl_region *region;
struct wl_shell *shell;
struct wl_shell_surface *shell_surface;

EGLDisplay egl_display;
EGLConfig egl_conf;
EGLSurface egl_surface;
EGLContext egl_context;


static void global_registry_handler(void *data, struct wl_registry *registry,
                                    uint32_t id, const char *interface,
                                    uint32_t version)
{
    printf("registry event for %s id %d\n", interface, id);

    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = (wl_compositor *) wl_registry_bind(registry, id, &wl_compositor_interface, 1);
    } else if (strcmp(interface, "wl_shell") == 0) {
        shell = (wl_shell *) wl_registry_bind(registry, id, &wl_shell_interface, 1);
    }
}

static void global_registry_remover(void *data, struct wl_registry *registry,
                                    uint32_t id)
{
    printf("registry losing event for %d\n", id);
}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler, global_registry_remover
};


static void create_window()
{
    egl_window = wl_egl_window_create(surface, WIDTH, HEIGHT);
    assert(egl_window != EGL_NO_SURFACE);

    egl_surface = eglCreateWindowSurface(egl_display, egl_conf, egl_window, NULL);
    assert(eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context));

    eglSwapInterval(egl_display, 0);

}

static void init_egl()
{
    EGLint major, minor, count, n, size;
    EGLConfig *configs;
    int i;
    EGLint config_attribs[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RED_SIZE, 8,
                               EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8 ,EGL_ALPHA_SIZE,8,EGL_STENCIL_SIZE,1,
                               EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE
                              };

    static const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                             EGL_NONE
                                            };

    egl_display = eglGetDisplay((EGLNativeDisplayType)display);
    assert(egl_display != EGL_NO_DISPLAY);
    

    assert(eglInitialize(egl_display, &major, &minor) == EGL_TRUE);
    eglGetConfigs(egl_display, NULL, 0, &count);

    printf("EGL major: %d, minor: %d ,configs:%d\n", major, minor,count);

    configs = (EGLConfig *)calloc(count, sizeof * configs);

    eglChooseConfig(egl_display, config_attribs, configs, count, &n);

    for (i = 0; i < n; i++) {
        eglGetConfigAttrib(egl_display, configs[i], EGL_BUFFER_SIZE, &size);
        printf("Buffer size for config %d is %d\n", i, size);
        eglGetConfigAttrib(egl_display, configs[i], EGL_RED_SIZE, &size);
        printf("Red size for config %d is %d\n", i, size);
        eglGetConfigAttrib(egl_display, configs[i], EGL_ALPHA_SIZE, &size);
        printf("Alpha size for config %d is %d\n", i, size);

        // just choose the first one
        egl_conf = configs[i];
        break;
    }

    egl_context =
        eglCreateContext(egl_display, egl_conf, EGL_NO_CONTEXT, context_attribs);
}


int main(int argc, char **argv)
{
 
    display = wl_display_connect(NULL);
    assert(display);

    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);

    wl_display_dispatch(display);
    
    assert(compositor);
    assert(shell);

    surface = wl_compositor_create_surface(compositor);
    assert(surface);

    //shell_surface = wl_shell_get_shell_surface(shell, surface);
    shell_surface = wl_shell_wm_get_shell_surface(shell, surface, 2054, 0, 0, 0);
  
    wl_shell_surface_set_visibility(shell_surface, 1);
    wl_shell_surface_set_toplevel(shell_surface);
    wl_shell_surface_set_window_geometry(shell_surface, 0, 0, WIDTH, HEIGHT);


    
    init_egl();
    create_window();
    // init_gl();
    
    prevt= getTimeNow();
    initGraph(&fps, GRAPH_RENDER_FPS, "Frame Time");
    vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES|NVG_DEBUG);

    assert(loadDemoData(vg, &ddata) != -1);
   

    while ( 1 ) {
       printf("looping \n");
       wl_display_dispatch_pending(display);
       draw();
       assert(eglSwapBuffers(egl_display, egl_surface));
       
    }

    wl_display_disconnect(display);
    printf("disconnected from display\n");

    exit(0);
}
