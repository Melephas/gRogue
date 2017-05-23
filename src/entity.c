#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "position.h"
#include "entity.h"

/* Entity Subsystem
 *  This file contains all functions that take the Entity type or return it
*/

Entity *createEntity(int x, int y, char *sym) // Returns an entity that gets created at (x, y) with the symbol sym.
{
	Entity *entity = malloc(sizeof(Entity));
	entity->position.x = x;
	entity->position.y = y;
	entity->symbol = sym;
	entity->floorTile = ".";
	return entity;
}

int drawEntity(Entity *ent) // Locates the point on the screen where an entity is and draws the entity there
{
	mvprintw(ent->position.y, ent->position.x, ent->symbol);
	move(ent->position.y, ent->position.x);
	return 1;
}

int moveEntity(Entity *ent, int x, int y) // Handles all the movement for an entity, including collision handling with the walls
{
	char str[1] = {(char)mvinch(y, x)};
	if (str[0] == '|' || str[0] == '-')
	{
		move(ent->position.y, ent->position.x);
		return 0;
	}
	mvprintw(ent->position.y, ent->position.x, ent->floorTile);
	ent->floorTile = str;
	ent->position.x = x;
	ent->position.y = y;
	drawEntity(ent);
	return 1;
}
