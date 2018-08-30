#ifndef ROOM_H
#define ROOM_H

#include "position.h"

typedef struct room
{
	Position position;
	int height;
	int width;
        Position **doors;
} Room;

Room *generateRoom(int, int);
int drawMap(Room **, int);
int checkRoomCollision(Room *, Room **, int);

#endif
