#include <EGL/egl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-server.h>

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

#define WIDTH 800
#define HEIGHT 600

#ifdef __cplusplus
extern "C" {
#endif

static void global_registry_handler(void *data, struct wl_registry *registry,
                                    uint32_t id, const char *interface,
                                    uint32_t version) {
  printf("registry event for %s id %d\n", interface, id);

  if (strcmp(interface, "wl_compositor") == 0) {
    compositor = (wl_compositor *)wl_registry_bind(registry, id,
                                                   &wl_compositor_interface, 1);
  } else if (strcmp(interface, "wl_shell") == 0) {
    shell = (wl_shell *)wl_registry_bind(registry, id, &wl_shell_interface, 1);
  }
}

static void global_registry_remover(void *data, struct wl_registry *registry,
                                    uint32_t id) {
  printf("registry losing event for %d\n", id);
}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler, global_registry_remover};

static void create_window() {
  egl_window = wl_egl_window_create(surface, WIDTH, HEIGHT);
  assert(egl_window != EGL_NO_SURFACE);

  egl_surface = eglCreateWindowSurface(egl_display, egl_conf,
                                       (EGLNativeWindowType)egl_window, NULL);
  assert(eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context));

  // eglSwapInterval(egl_display, 0);
}

static void init_egl() {
  EGLint major, minor, count, n, size;
  EGLConfig *configs;
  int i;
  EGLint config_attribs[] = {EGL_SURFACE_TYPE,
                             EGL_WINDOW_BIT,
                             EGL_RED_SIZE,
                             8,
                             EGL_GREEN_SIZE,
                             8,
                             EGL_BLUE_SIZE,
                             8,
                             EGL_RENDERABLE_TYPE,
                             EGL_OPENGL_ES2_BIT,
                             EGL_NONE};

  static const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                           EGL_NONE};

  egl_display = eglGetDisplay((EGLNativeDisplayType)display);
  assert(egl_display != EGL_NO_DISPLAY);

  assert(eglInitialize(egl_display, &major, &minor) == EGL_TRUE);
  eglGetConfigs(egl_display, NULL, 0, &count);

  printf("EGL major: %d, minor: %d ,configs:%d\n", major, minor, count);

  configs = (EGLConfig *)calloc(count, sizeof *configs);

  eglChooseConfig(egl_display, config_attribs, configs, count, &n);

  for (i = 0; i < n; i++) {
    eglGetConfigAttrib(egl_display, configs[i], EGL_BUFFER_SIZE, &size);
    printf("Buffer size for config %d is %d\n", i, size);
    eglGetConfigAttrib(egl_display, configs[i], EGL_RED_SIZE, &size);
    printf("Red size for config %d is %d\n", i, size);

    // just choose the first one
    egl_conf = configs[i];
    break;
  }

  egl_context =
      eglCreateContext(egl_display, egl_conf, EGL_NO_CONTEXT, context_attribs);
}

void smart_platform_init() {
  display = wl_display_connect(NULL);
  assert(display);

  struct wl_registry *registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, NULL);

  wl_display_dispatch(display);

  assert(compositor);
  assert(shell);

  surface = wl_compositor_create_surface(compositor);
  assert(surface);

  shell_surface = wl_shell_get_shell_surface(shell, surface);
  wl_shell_surface_set_toplevel(shell_surface);

  init_egl();
  create_window();
}

void smart_platform_terminate() {
  wl_display_disconnect(display);
  printf("disconnected from display\n");
  exit(0);
}

int smart_platform_shoud_close() {
  wl_display_dispatch_pending(display);
  return 0;
}

void smart_platform_swap_buffer() {
  assert(eglSwapBuffers(egl_display, egl_surface));
}

#ifdef __cplusplus
};
#endif