SHELL:=/bin/bash
PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = leftistTree.o Node.o

CPPFLAGS = -std=c++11 -Wall
CFLAGS = -std=c99 -Wall 
LFLAGS = -lm

BUILD_MODE = run

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g -O0
	CFLAGS += -fsanitize=address
	LFLAGS += -lasan
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2 -pie -fPIE
	LFLAGS += -pie -fPIE
else
	#$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	leftistTree

leftistTree:	$(OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr leftistTree $(OBJS)
