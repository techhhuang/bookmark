#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <cstring>
#include <wayland-client.h>
#include <wayland-server.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using namespace std;

class Window
{
private:


public:
	Window();
	~Window();
	void show();
	void resize();
	
};


#endif