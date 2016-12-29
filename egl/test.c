#include "Log.h"
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>
#include <wayland-server.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>


class Window
{
public:
    Window();
    ~Window();
    void show();

    static void connect();
    static void run();

    static struct wl_display *display;
    static struct wl_registry *registry;
    static struct wl_compositor *compositor;
    static struct wl_shell *shell;

    static void registry_handler(void *, struct wl_registry *, uint32_t, const char *, uint32_t);
    static void registry_remover(void *, struct wl_registry *, uint32_t);
    static struct wl_registry_listener registry_listener;

    static void handle_ping(void *data, struct wl_shell_surface *shell_surface, uint32_t serial);
    static void handle_configure(void *data, struct wl_shell_surface *shell_surface,
                                 uint32_t edges, int32_t width, int32_t height);
    static void handle_popup_done(void *data, struct wl_shell_surface *shell_surface);
    static const struct wl_shell_surface_listener shell_surface_listener;
private:
    void init_egl();
    void create_egl_window();
    struct wl_surface *surface;
    struct wl_shell_surface *shell_surface;
    struct wl_egl_window *egl_window;
    EGLDisplay egl_display;
    EGLConfig egl_conf;
    EGLSurface egl_surface;
    EGLContext egl_context;

};
struct wl_display *Window::display = NULL;
struct wl_registry *Window::registry = NULL;
struct wl_compositor *Window::compositor = NULL;
struct wl_shell *Window::shell = NULL;

Window::Window()
{
    if (surface = wl_compositor_create_surface(compositor)) {
        TRACE("create surface\n");
    } else {
        TRACE("can't create surface\n");
        return;
    }

    shell_surface = wl_shell_get_shell_surface(shell, surface);
    wl_shell_surface_set_toplevel(shell_surface);

    wl_shell_surface_add_listener(shell_surface, &shell_surface_listener, NULL);


    init_egl();
    create_egl_window();

}
Window::~Window()
{

}
void Window::show()
{



}
void Window::run()
{
    while (wl_display_dispatch(display) != -1);

    wl_display_disconnect(display);
    TRACE("disconnected from display\n");
}
void Window::connect()
{
    display = wl_display_connect(NULL);

    if (display = wl_display_connect(NULL)) {
        TRACE("connected to display\n");
    } else {
        TRACE("can't connect to display\n");
        return;
    }

    registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);

    wl_display_dispatch(display);
    wl_display_roundtrip(display);

    if (compositor == NULL || shell == NULL) {
        TRACE("Can't find compositor or shell\n");
        return;
    } else {
        TRACE("Found compositor and shell\n");
    }
}
void Window::registry_handler(void *data, struct wl_registry *registry,
                              uint32_t id, const char *interface,
                              uint32_t version)
{
    TRACE("Got a registry event for %s id %d\n", interface, id);

    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = (wl_compositor *)wl_registry_bind(registry, id, &wl_compositor_interface, 1);
    } else if (strcmp(interface, "wl_shell") == 0) {
        shell = (wl_shell *) wl_registry_bind(registry, id, &wl_shell_interface, 1);
    }
}

void Window::registry_remover(void *data, struct wl_registry *registry,
                              uint32_t id)
{
    TRACE("Got a registry losing event for %d\n", id);
}

struct wl_registry_listener Window::registry_listener = {
    registry_handler, registry_remover
};
void Window::init_egl()
{
    EGLint major, minor, count, n, size;
    EGLConfig *configs;
    int i;
    EGLint config_attribs[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RED_SIZE, 8,
                               EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
                               EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE
                              };

    static const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                             EGL_NONE
                                            };

    egl_display = eglGetDisplay((EGLNativeDisplayType)display);

    if (egl_display == EGL_NO_DISPLAY) {
        TRACE("can't create egl display\n");
        exit(1);
    } else {
        TRACE("created egl display\n");
    }

    if (eglInitialize(egl_display, &major, &minor) != EGL_TRUE) {
        TRACE("Can't initialise egl display\n");
        exit(1);
    }

    TRACE("EGL major: %d, minor %d\n", major, minor);

    eglGetConfigs(egl_display, NULL, 0, &count);
    TRACE("EGL has %d configs\n", count);

    configs = (EGLConfig *)calloc(count, sizeof * configs);

    eglChooseConfig(egl_display, config_attribs, configs, count, &n);

    for (i = 0; i < n; i++) {
        eglGetConfigAttrib(egl_display, configs[i], EGL_BUFFER_SIZE, &size);
        TRACE("Buffer size for config %d is %d\n", i, size);
        eglGetConfigAttrib(egl_display, configs[i], EGL_RED_SIZE, &size);
        TRACE("Red size for config %d is %d\n", i, size);

        // just choose the first one
        egl_conf = configs[i];
        break;
    }

    egl_context =
        eglCreateContext(egl_display, egl_conf, EGL_NO_CONTEXT, context_attribs);
}
void Window::create_egl_window()
{
    egl_window = wl_egl_window_create(surface, 480, 360);

    if (egl_window == EGL_NO_SURFACE) {
        TRACE("Can't create egl window\n");
        exit(1);
    } else {
        TRACE("Created egl window\n");
    }

    egl_surface = eglCreateWindowSurface(egl_display, egl_conf, egl_window, NULL);

    if (eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context)) {
        TRACE("Made current\n");
    } else {
        TRACE("Made current failed\n");
    }


    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();


    if (eglSwapBuffers(egl_display, egl_surface)) {
        TRACE("Swapped buffers\n");
    } else {
        TRACE("Swapped buffers failed\n");
    }
}

void Window::handle_ping(void *data, struct wl_shell_surface *shell_surface,
                         uint32_t serial)
{
    wl_shell_surface_pong(shell_surface, serial);
    TRACE("pinged and ponged\n");
}

void Window::handle_configure(void *data, struct wl_shell_surface *shell_surface,
                              uint32_t edges, int32_t width, int32_t height)
{
}

void Window::handle_popup_done(void *data, struct wl_shell_surface *shell_surface)
{
}

const struct wl_shell_surface_listener Window::shell_surface_listener = {
    handle_ping, handle_configure, handle_popup_done
};

int main(int argc, char **argv)
{
    Window::connect();
    Window win1;
    Window win2;
    // win.show();
    Window::run();
    exit(0);
}
