CC=clang

# C compiler flags
CFLAGS= -Wall -Werror -std=c99

# Linker libs
LDLIBS= `pkg-config --cflags --libs gtk+-3.0`
SRC=main.c

# all target just call the production of main
all: main clean

# main target using implicit rules, just express dependencies
main:
	$(CC) $(CFLAGS) $(LDLIBS) $(SRC) -o mediocr

# clean compilation products
clean:
	rm -f *.o
