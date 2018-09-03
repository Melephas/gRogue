#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "position.h"
#include "entity.h"

/* Entity Subsystem
 *  This file contains all functions that take the Entity type or return it
*/

Entity *createEntity(int x, int y, char sym) // Returns an entity that gets created at (x, y) with the symbol sym.
{
	Entity *entity = malloc(sizeof(Entity));
	entity->position.x = x;
	entity->position.y = y;
	entity->symbol = sym;
	entity->floorTile = '.';
	return entity;
}

int drawEntity(Entity *ent) // Locates the point on the screen where an entity is and draws the entity there
{
	mvprintw(ent->position.y, ent->position.x, "%c", ent->symbol);
	return 1;
}

int moveEntity(Entity *ent, int x, int y) // Handles all the movement for an entity, including collision handling with the walls
{
	char newTile = mvinch(y, x);
	if (newTile == '|' || newTile == '-' || newTile == ' ')
		return 0;

	mvprintw(ent->position.y, ent->position.x, "%c", ent->floorTile);
	ent->floorTile = newTile;
	ent->position.x = x;
	ent->position.y = y;
	drawEntity(ent);
	return 1;
}

struct stylus *createStylus(int x, int y, char tip)
{
    struct stylus *styl = malloc(sizeof(struct stylus));
    styl->symbol = '*';
    styl->position.x = x;
    styl->position.y = y;
    styl->tip = tip;

    return styl;
}

void moveStylus(struct stylus *styl, int x, int y)
{
    mvprintw(styl->position.y, styl->position.x, "%c", styl->tip);
    styl->position.x = x;
    styl->position.y = y;
    mvprintw(y, x, "%c", styl->symbol);
}
