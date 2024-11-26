OS := $(shell uname)

ifeq ($(OS), Linux)
    MAKEFILE:= tools/Makefile.l
else
    MAKEFILE:= tools/Makefile.w
endif

all:
	make -f $(MAKEFILE)