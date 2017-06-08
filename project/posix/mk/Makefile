-include config.mk a.mk 
FILES = $(shell ls)
FLAGS := first $(EXT)
EXT = this is ext

all:
	echo "hello world" 
	echo `pwd`
	-cat file_not_exit
	make other-all
	@echo $(BUILDTYPE)
	@echo $(FILES)
	@echo $(FLAGS)
include ./other/Makefile
