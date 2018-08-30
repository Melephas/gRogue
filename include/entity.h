#ifndef ENTITY_H
#define ENTITY_H

typedef struct entity
{
	Position position;
	int health;
	char symbol;
	char floorTile;
} Entity;

int moveEntity(Entity *, int, int);
Entity *createEntity(int, int, char);
int drawEntity(Entity *);

#endif
