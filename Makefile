# Global Compilation Variables

# The compiler
CC=gcc

# Pre-processor flags
CPPFLAGS=`sdl-config --cflags` `pkg-config --cflags gtk+-2.0`

# C compiler flags
CFLAGS= -Wall -Werror -std=c99 -O3 

# Linker flags
LDFLAGS=

# Linker libs
LDLIBS= -lm `sdl-config --libs` `pkg-config --libs gtk+-2.0`   

# all target just call the production of main
all: main clean

# main target using implicit rules, just express dependencies
main: main.o

.PHONY: clean

# clean compilation products
clean:
	@echo "Cleaning up .o files"
	@find . -name "*.o" -type f -delete

# END of File

