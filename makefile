NAME = game
    
CC = gcc
CFLAGS = -lncurses -I$(IDIR) -Wall -O3

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: clean build

build:
	$(CC) $(SOURCES) $(CFLAGS) -o $(NAME)
clean:
	$(RM) $(NAME)
