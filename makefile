CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LIBS = -lSDL2 -lm
INC_DIR = inc

all: raycaster

raycaster: main.o raycaster.o
	    $(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: src/%.c
	    $(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	    rm -f *.o raycaster

.PHONY: all clean
