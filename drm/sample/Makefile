FLAGS=`pkg-config --cflags --libs libdrm`
FLAGS+=-Wall -O0 -g
FLAGS+=-D_FILE_OFFSET_BITS=64

all:
	gcc -o modeset modeset.c $(FLAGS)
	gcc -o modeset-double-buffered modeset-double-buffered.c $(FLAGS)
	gcc -o modeset-vsync modeset-vsync.c $(FLAGS)
clean:
	rm modeset modeset-double-buffered modeset-vsync
