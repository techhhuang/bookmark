#ifndef _WAYLAND_PLATFORM_h
#define _WAYLAND_PLATFORM_h

#ifdef __cplusplus
extern "C" {
#endif

void smart_platform_init();
void smart_platform_create_window(void *data);
void smart_platform_swap(void *data);
void smart_platform_loop();
#ifdef __cplusplus
};
#endif

#endif