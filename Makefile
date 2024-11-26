OS := $(shell uname)

ifeq ($(OS), Linux)
    MAKEFILE:= tools/Makefile.l
endif

ifeq ($(OS), MINGW32_NT)
    MAKEFILE:= tools/Makefile.w
endif

all:
	make -f $(MAKEFILE)
