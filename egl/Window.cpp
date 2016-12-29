#include "Window.h"

struct wl_display *display = NULL;
struct wl_registry *registry=NULL;
struct wl_compositor *compositor = NULL;
struct wl_shell *shell=NULL;

struct wl_surface *surface;
struct wl_shell_surface *shell_surface;
struct wl_egl_window *egl_window;

EGLDisplay egl_display;
EGLConfig egl_conf;
EGLSurface egl_surface;
EGLContext egl_context;

static void global_registry_handler(void *data, struct wl_registry *registry,
                                    uint32_t id, const char *interface,
                                    uint32_t version) 
{
	cout<<"Got a registry event for "<< interface <<endl;

	if (strcmp(interface, "wl_compositor") == 0) {
		compositor = (wl_compositor*)wl_registry_bind(registry, id, &wl_compositor_interface, 1);
	} else if (strcmp(interface, "wl_shell") == 0) {
		shell = (wl_shell*) wl_registry_bind(registry, id, &wl_shell_interface, 1);
	}
}

static void global_registry_remover(void *data, struct wl_registry *registry,
	uint32_t id) 
{
	cout<<"Got a registry losing event for "<< id <<endl;
}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler, global_registry_remover};

static void connect(){
	display = wl_display_connect(NULL);
  	if (display == NULL) {
    	cout<<"Can't connect to display"<<endl;
    	exit(1);
  	}
 	cout<<"connected to display"<<endl;

  	registry = wl_display_get_registry(display);

	wl_registry_add_listener(registry, &registry_listener, NULL);
	wl_display_dispatch(display);
	wl_display_roundtrip(display);

	if (compositor == NULL || shell == NULL) {
		cout<<"Can't find compositor or shell"<<endl;
		exit(1);
	} else {
		cout<<"Found compositor and shell"<<endl;
	}
}

Window::Window()
{
	cout<<"create window"<<endl;
	connect();
	
}

Window::~Window()
{
	cout<<"destory window"<<endl;
}




void Window::show()
{
	cout<<"show window"<<endl;

}

void Window::resize(){


}