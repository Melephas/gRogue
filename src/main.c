#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "confSys.h"

#include "position.h"
#include "room.h"
#include "entity.h"

// Typedefs


// Global Variables
int rooms;
Room **map;
int screenW, screenH;

// Variable lookup table for config file ease of use
char names[1] = {'r'};
int *addr[1] = {&rooms};

// Function prototypes
int setup();
int shutdown();
void handleIn(char, Entity *);


int main(int argc, char *argv[])
{
    if (!setup()) // This is where all the startup happens, including map generation and config loading
    	return 1;
	
    // Create player
    Entity *player = createEntity(map[0]->position.x+1, map[0]->position.y+1, '@');
    drawEntity(player);

    int ch;
    while ((ch = getch()) != 'q') // Currently this is the main game loop
    {
    	handleIn(ch, player);
    }

    return shutdown(); // This is the end of the program
}

int setup() // Sets up everything needed to run the game, then returns 1
{
	// Ncurses setup
    initscr();
    noecho();
    curs_set(FALSE);
    refresh();
    getmaxyx(stdscr, screenH, screenW);
    if (screenH > 50)
    	screenH = 50;
    // End Ncurses setup
    // Internal setup
    loadConfig("config.txt", names, addr, sizeof(names));
	
    srand(time(NULL));
    srand(rand());

    map = malloc(sizeof(Room) * rooms);
    int x;
    for (x = 0; x < rooms; ++x)
    {
    	map[x] = malloc(sizeof(Room));
    	do
    	{
    	    map[x] = generateRoom(screenW, screenH);
    	}
    	while (checkRoomCollision(map[x], map, x));
    }
    drawMap(map, rooms);

    // End Internal setup
	
    return 1;
}

int shutdown() // Takes care of everything that needs to be done to return the console to the state it was in before running the game
{
    curs_set(TRUE);
    endwin();
    return 100;
}

void handleIn(char in, Entity *player) // Handles player keyboard input
{
    int x;

    switch ((int)in)
    {
    case 'w':
    case 'W':
    	moveEntity(player, player->position.x, player->position.y - 1);
    	break;
    case 's':
    case 'S':
    	moveEntity(player, player->position.x, player->position.y + 1);
    	break;
    case 'a':
    case 'A':
    	moveEntity(player, player->position.x - 1, player->position.y);
    	break;
    case 'd':
    case 'D':
    	moveEntity(player, player->position.x + 1, player->position.y);
    	break;
    case 'r':
    case 'R':
    	for (x = 0; x < rooms; ++x)
    	{
    	    map[x] = malloc(sizeof(Room));
    	    do
    	    {
    	    	map[x] = generateRoom(screenW, screenH);
    	    }
            while (checkRoomCollision(map[x], map, x));
    	}
    	moveEntity(player, map[0]->position.x+1, map[0]->position.y+1);
    	clear();
    	drawMap(map, rooms);
    	drawEntity(player);
    	break;
    }
}


