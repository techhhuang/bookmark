INCLUDES = -I . -I ../include -I ../render
LIBS =-L .
SRC = $(wildcard ../src/*.cpp)
SYSROOT = /home/leo/build/dra7xx-evm
PREFIX = arm-linux-gnueabihf-
LIBSYUNOS = -L . -L$(SYSROOT)/usr/lib/  -lwayland-client -lEGL -lpvr_wlegl -lGLESv2 -lnanovg2 -Wl,-rpath-link,/usr/lib/ 
INCLUDESYUNOS =  -I ../include -I ../render -I $(SYSROOT)/usr/include/ 
all:
	

render:
	g++ render_test.cpp $(LIBSRC)  $(LIBS) -lwayland-client -lwayland-egl -lGLESv2 -lEGL -lnanovg -o test $(INCLUDES)

ui:

	g++ ui_test.cpp $(INCLUDES) $(SRC)  $(LIBS) -lwayland-client -lwayland-egl -lGLESv2 -lEGL -lnanovg -o test -std=c++11

engine:
	gcc -c  ../render/nanovg.c -lm
	ar rc libnanovg.a nanovg.o
	rm -f nanovg.o
engine-yunos:
	$(PREFIX)gcc -c  ../render/nanovg.c --sysroot=$(SYSROOT) -lm
	$(PREFIX)ar rc libnanovg2.a nanovg.o
	rm -f nanovg.o
yunos:
	$(PREFIX)g++ ui_test.cpp $(INCLUDESYUNOS) $(SRC) $(LIBSYUNOS) --sysroot=$(SYSROOT) -std=c++11 -DYUNOS -o test
run:yunos
	adb -host push test /tmp
	adb -host shell 'cd /tmp;./test'