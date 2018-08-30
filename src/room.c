#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "room.h"

/* Room Subsystem
 *  Contains all the functions that take the Room type or return it
*/

Room *generateRoom(int screenW, int screenH) // Generates a room that fits within the screenW and screenH provided
{	// All rooms should be at least 6x6

	Room *room = malloc(sizeof(Room));
	room->position.x = abs(rand()) % (int)((2 * screenW) / 3);
	room->position.y = abs(rand()) % (int)((2 * screenH) / 3);
	room->width = (abs(rand()) % 17) + 8;
	room->height = (abs(rand()) % 12) + 8;

        room->doors = malloc(sizeof(Position) * 4);

        room->doors[0] = malloc(sizeof(Position));
        room->doors[0]->x = (rand() % (room->width - 1)) + 1 + room->position.x;
        room->doors[0]->y = room->position.y;

	return room;
}

int drawMap(Room **map, int size) // Draws all the rooms in the map provided, the size of the map (amount of rooms) is what should be given in the size variable
{
	int x;
	int y;
	int i;
	for (i = 0; i < size; ++i)
	{
		for (y = map[i]->position.y; y < (map[i]->position.y + map[i]->height); ++y) // draw vertical walls
		{
			mvprintw(y, map[i]->position.x, "|");
			mvprintw(y, map[i]->position.x + map[i]->width - 1, "|");
		}
		for (x = map[i]->position.x; x < (map[i]->position.x + map[i]->width); ++x) // draw horizontal walls
		{
			mvprintw(map[i]->position.y, x, "-");
			mvprintw(map[i]->position.y + map[i]->height - 1, x, "-");
		}
		for (x = map[i]->position.x + 1; x < (map[i]->position.x + map[i]->width - 1); ++x) // fill room
		{
			for (y = map[i]->position.y +1; y < (map[i]->position.y + map[i]->height - 1); ++y)
			{
				mvprintw(y, x, ".");
			}
		}

                mvprintw(map[i]->doors[0]->y, map[i]->doors[0]->x, "#");
	}


	return 0;
}

int checkRoomCollision(Room *room, Room **map, int mapSize) // Checks for collision between one room and all others on the map
	// This function works as is, but still needs improving to remove some edge cases thrown up by ranom generation, it's rare to run into one of these though
{
	int i;
	for (i = 0; i < mapSize; ++i)
	{
		// Check room collision with map element
		if (room->position.x >= map[i]->position.x-1 && room->position.x < map[i]->position.x + map[i]->width+1)
		{
			if (room->position.y >= map[i]->position.y-1 && room->position.y < map[i]->position.y + map[i]->height+1)
			{
				return 1;
			}
		}
		if (room->position.x + room->width >= map[i]->position.x-1 && room->position.x + room->width < map[i]->position.x + map[i]->height+1)
		{
			if (room->position.y >= map[i]->position.y-1 && room->position.y < map[i]->position.y + map[i]->height+1)
			{
				return 1;
			}
		}
		if (room->position.x >= map[i]->position.x-1 && room->position.x < map[i]->position.x + map[i]->width+1)
		{
			if (room->position.y + room->height >= map[i]->position.y-1 && room->position.y + room->height < map[i]->position.y + map[i]->height+1)
			{
				return 1;
			}
		}
		if (room->position.x + room->width >= map[i]->position.x-1 && room->position.x + room->width < map[i]->position.x + map[i]->width+1)
		{
			if (room->position.y + room->height >= map[i]->position.y-1 && room->position.y + room->height < map[i]->position.y + map[i]->height+1)
			{
				return 1;
			}
		}
		
		// Check map element collision with room
		if (map[i]->position.x >= room->position.x-1 && map[i]->position.x < room->position.x + room->width+1)
		{
			if (map[i]->position.y >= room->position.y-1 && map[i]->position.y < room->position.y + room->height+1)
			{
				return 1;
			}
		}
		if (map[i]->position.x + map[i]->width >= room->position.x-1 && map[i]->position.x + map[i]->width < room->position.x + room->height+1)
		{
			if (map[i]->position.y >= room->position.y-1 && map[i]->position.y < room->position.y + room->height+1)
			{
				return 1;
			}
		}
		if (map[i]->position.x >= room->position.x-1 && map[i]->position.x < room->position.x + room->width+1)
		{
			if (map[i]->position.y + map[i]->height >= room->position.y-1 && map[i]->position.y + map[i]->height < room->position.y + room->height+1)
			{
				return 1;
			}
		}
		if (map[i]->position.x + map[i]->width >= room->position.x-1 && map[i]->position.x + map[i]->width < room->position.x + room->width+1)
		{
			if (map[i]->position.y + map[i]->height >= room->position.y-1 && map[i]->position.y + map[i]->height < room->position.y + room->height+1)
			{
				return 1;
			}
		}
	}
	return 0;
}
