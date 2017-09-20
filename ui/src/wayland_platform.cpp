#ifndef _WAYLAND_PLATFORM_h
#define _WAYLAND_PLATFORM_h

#include <Platform.h>
#include <Window.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>
#include <linux/input.h>  // for BTN_LEFT
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

// input devices
struct wl_seat *seat;
struct wl_pointer *pointer;
// struct wl_touch *touch;
// struct wl_keyboard *keyboard;

EGLDisplay egl_display;
EGLConfig egl_conf;
EGLSurface egl_surface;
EGLContext egl_context;

//
SmartUI::Window *focusWindow;

#define WIDTH 800
#define HEIGHT 600

#ifdef __cplusplus
extern "C" {
#endif

// *******************pointer handle ********************************
static void pointer_handle_enter(void *data, struct wl_pointer *pointer,
                                 uint32_t serial, struct wl_surface *surface,
                                 wl_fixed_t sx, wl_fixed_t sy) {
  printf("Pointer entered surface %p at %f %f\n", surface,
         wl_fixed_to_double(sx), wl_fixed_to_double(sy));
  focusWindow = (SmartUI::Window *)wl_surface_get_user_data(surface);
}

static void pointer_handle_leave(void *data, struct wl_pointer *pointer,
                                 uint32_t serial, struct wl_surface *surface) {
  printf("Pointer left surface %p\n", surface);
  focusWindow = NULL;
}

static void pointer_handle_motion(void *data, struct wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy) {
  // printf("Pointer moved at %f %f\n", wl_fixed_to_double(sx),
  //        wl_fixed_to_double(sy));
  focusWindow->onMouseMove(wl_fixed_to_double(sx), wl_fixed_to_double(sy));
}

static void pointer_handle_button(void *data, struct wl_pointer *wl_pointer,
                                  uint32_t serial, uint32_t time,
                                  uint32_t button, uint32_t state) {
  printf("Pointer button\n");

  // if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED)
  //   wl_shell_surface_move(shell_surface, seat, serial);

  focusWindow->onMouseButtonEvent(button - BTN_LEFT, state, time);
}

static void pointer_handle_axis(void *data, struct wl_pointer *wl_pointer,
                                uint32_t time, uint32_t axis,
                                wl_fixed_t value) {
  printf("Pointer handle axis\n");
}

static const struct wl_pointer_listener pointer_listener = {
    pointer_handle_enter,  pointer_handle_leave, pointer_handle_motion,
    pointer_handle_button, pointer_handle_axis,
};

static void seat_handle_capabilities(void *data, struct wl_seat *seat,
                                     uint32_t caps) {
  if ((caps & WL_SEAT_CAPABILITY_POINTER) && !pointer) {
    pointer = wl_seat_get_pointer(seat);
    wl_pointer_add_listener(pointer, &pointer_listener, NULL);
  } else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && pointer) {
    wl_pointer_destroy(pointer);
    pointer = NULL;
  }
}

static const struct wl_seat_listener seat_listener = {
    seat_handle_capabilities,
};

//******************************ping and pong******************************

static void handle_ping(void *data, struct wl_shell_surface *shell_surface,
                        uint32_t serial) {
  wl_shell_surface_pong(shell_surface, serial);
  printf("Pinged and ponged\n");
}

static void handle_configure(void *data, struct wl_shell_surface *shell_surface,
                             uint32_t edges, int32_t width, int32_t height) {}

static void handle_popup_done(void *data,
                              struct wl_shell_surface *shell_surface) {}

static const struct wl_shell_surface_listener shell_surface_listener = {
    handle_ping, handle_configure, handle_popup_done};

//*********************************global handler*********************

static void global_registry_handler(void *data, struct wl_registry *registry,
                                    uint32_t id, const char *interface,
                                    uint32_t version) {
  printf("registry event for %s id %d\n", interface, id);

  if (strcmp(interface, "wl_compositor") == 0) {
    compositor = (wl_compositor *)wl_registry_bind(registry, id,
                                                   &wl_compositor_interface, 1);
  } else if (strcmp(interface, "wl_shell") == 0) {
    shell = (wl_shell *)wl_registry_bind(registry, id, &wl_shell_interface, 1);
  } else if (strcmp(interface, "wl_seat") == 0) {
    seat = (wl_seat *)wl_registry_bind(registry, id, &wl_seat_interface, 1);
    wl_seat_add_listener(seat, &seat_listener, NULL);
  }
}

static void global_registry_remover(void *data, struct wl_registry *registry,
                                    uint32_t id) {
  printf("registry losing event for %d\n", id);
}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler, global_registry_remover};

static void create_window(void *data) {
  SmartUI::Window *win = (SmartUI::Window *)data;
  printf("create native window:%d %d\n", win->width(), win->height());
  egl_window = wl_egl_window_create(surface, win->width(), win->height());
  assert(egl_window != EGL_NO_SURFACE);

  egl_surface = eglCreateWindowSurface(egl_display, egl_conf,
                                       (EGLNativeWindowType)egl_window, NULL);
  assert(eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context));

  glViewport(0, 0, win->width(), win->height());
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  // eglSwapInterval(egl_display, 0);
}

static void init_egl(void *data) {
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
                             EGL_STENCIL_SIZE,
                             1,
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
  wl_display_roundtrip(display);
  assert(compositor);
  assert(shell);
}

void smart_platform_create_window(void *data) {
  surface = wl_compositor_create_surface(compositor);
  wl_surface_set_user_data(surface, data);
  assert(surface);
  shell_surface = wl_shell_get_shell_surface(shell, surface);
  wl_shell_surface_set_toplevel(shell_surface);
  wl_shell_surface_add_listener(shell_surface, &shell_surface_listener, data);
  init_egl(data);
  create_window(data);
}

void smart_platform_swap() { assert(eglSwapBuffers(egl_display, egl_surface)); }
void smart_platform_loop() {
  while (wl_display_dispatch(display) != -1) {
    ;
  }
  wl_display_disconnect(display);
  printf("disconnected from display\n");
}

#ifdef __cplusplus
};
#endif

#endif