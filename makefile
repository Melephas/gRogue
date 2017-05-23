CC = gcc
CFLAGS = -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: clean build

build:
	$(CC) $(SOURCES) $(CFLAGS) -o game
clean:
	rm rougelike
