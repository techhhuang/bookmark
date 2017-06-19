#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>
#include <wayland-server.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <cairo/cairo.h>
#include <cairo/cairo-gl.h>

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
    printf("Got a registry event for %s id %d\n", interface, id);

    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
    } else if (strcmp(interface, "wl_shell") == 0) {
        shell = wl_registry_bind(registry, id, &wl_shell_interface, 1);
    }
}

static void global_registry_remover(void *data, struct wl_registry *registry,
                                    uint32_t id)
{
    printf("Got a registry losing event for %d\n", id);
}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler, global_registry_remover
};


static void create_window()
{
    cairo_device_t *cd = cairo_egl_device_create(egl_display,egl_context);

    if (cairo_device_status(cd) != CAIRO_STATUS_SUCCESS) {
        fprintf(stderr, "failed to get cairo EGL argb device\n");
        exit(1);
    }

    egl_window = wl_egl_window_create(surface, 800, 600);

    if (egl_window == EGL_NO_SURFACE) {
        fprintf(stderr, "Can't create egl window\n");
        exit(1);
    } else {
        fprintf(stderr, "Created egl window\n");
    }

    egl_surface = eglCreateWindowSurface(egl_display, egl_conf, egl_window, NULL);

    if (eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context)) {
        fprintf(stderr, "Made current\n");
    } else {
        fprintf(stderr, "Made current failed\n");
    }


    cairo_surface_t *cs = cairo_gl_surface_create_for_egl(cd,egl_surface,800,600);
    cairo_t *cr = cairo_create(cs);

    cairo_rectangle(cr, 0, 0, 800, 600);
    cairo_set_source_rgba(cr, 0, 0, 0, 0.8);
    cairo_fill(cr);

    double xc = 128.0;
    double yc = 128.0;
    double radius = 100.0;
    double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
    double angle2 = 180.0 * (M_PI/180.0);    

    cairo_set_line_width (cr, 10.0);
    cairo_arc (cr, xc, yc, radius, angle1, angle2);
    cairo_stroke (cr);

    /* draw helping lines */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_set_line_width (cr, 6.0);

    cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
    cairo_fill (cr);

    cairo_arc (cr, xc, yc, radius, angle1, angle1);
    cairo_line_to (cr, xc, yc);
    cairo_arc (cr, xc, yc, radius, angle2, angle2);
    cairo_line_to (cr, xc, yc);
    cairo_stroke (cr);

    cairo_gl_surface_swapbuffers(cs);

    // glClearColor(1.0, 1.0, 0.0, 0.0);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glFlush();


    // if (eglSwapBuffers(egl_display, egl_surface)) {
    //     fprintf(stderr, "Swapped buffers\n");
    // } else {
    //     fprintf(stderr, "Swapped buffers failed\n");
    // }
}

static void init_egl()
{
    EGLint major, minor, n;
    static const EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_ALPHA_SIZE, 1,
        EGL_DEPTH_SIZE, 1,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_NONE
    };

    // static const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
    //                                          EGL_NONE
    //                                         };
    static const EGLint *context_attribs = NULL;

    egl_display = eglGetDisplay(display);

    if (egl_display == EGL_NO_DISPLAY) {
        fprintf(stderr, "Can't create egl display\n");
        exit(1);
    } else {
        fprintf(stderr, "Created egl display\n");
    }

    if (eglInitialize(egl_display, &major, &minor) != EGL_TRUE) {
        fprintf(stderr, "Can't initialise egl display\n");
        exit(1);
    }

    printf("EGL major: %d, minor %d\n", major, minor);

    if (!eglBindAPI(EGL_OPENGL_API)) {
        fprintf(stderr, "failed to bind EGL client API\n");
        exit(1);
    }

    if (!eglChooseConfig(egl_display, config_attribs,&egl_conf, 1, &n) || n != 1) {
        fprintf(stderr, "failed to choose argb EGL config\n");
        exit(1);
    }

    egl_context =
        eglCreateContext(egl_display, egl_conf, EGL_NO_CONTEXT, context_attribs);


    if (!egl_context) {
        fprintf(stderr, "failed to create EGL context\n");
        exit(1);
    }

}

static void get_server_references(void)
{
    display = wl_display_connect(NULL);

    if (display == NULL) {
        fprintf(stderr, "Can't connect to display\n");
        exit(1);
    }

    printf("connected to display\n");

    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);

    wl_display_dispatch(display);
    wl_display_roundtrip(display);

    if (compositor == NULL || shell == NULL) {
        fprintf(stderr, "Can't find compositor or shell\n");
        exit(1);
    } else {
        fprintf(stderr, "Found compositor and shell\n");
    }
}

int main(int argc, char **argv)
{
    get_server_references();

    surface = wl_compositor_create_surface(compositor);

    if (surface == NULL) {
        fprintf(stderr, "Can't create surface\n");
        exit(1);
    } else {
        fprintf(stderr, "Created surface\n");
    }

    shell_surface = wl_shell_get_shell_surface(shell, surface);
    wl_shell_surface_set_toplevel(shell_surface);

    init_egl();
    create_window();
    while (wl_display_dispatch(display) != -1) {
        ;
    }

    wl_display_disconnect(display);
    printf("disconnected from display\n");

    exit(0);
}
