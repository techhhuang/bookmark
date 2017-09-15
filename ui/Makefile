INCLUDES = -I . -I ./include 
LIBSRC = $(shell find lib -name *.cpp)
all:
	

$(MAKECMDGOALS):
	g++ demos/$(MAKECMDGOALS).cpp $(LIBSRC) -lwayland-client -lwayland-egl -lGLESv2 -lEGL -o main_client $(INCLUDES)

run:
