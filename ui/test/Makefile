INCLUDES = -I . -I ../include -I ../render
LIBS = -L ../render
SRC = $(wildcard ../src/*.cpp)
all:
	

render:
	g++ render_test.cpp $(LIBSRC)  $(LIBS) -lwayland-client -lwayland-egl -lGLESv2 -lEGL -lnanovg -o test $(INCLUDES)

ui:
	g++ ui_test.cpp $(INCLUDES) $(SRC)  $(LIBS) -lwayland-client -lwayland-egl -lGLESv2 -lEGL -lnanovg -o test -std=c++11

run:
