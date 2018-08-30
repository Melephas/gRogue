#ifndef ENTITY_H
#define ENTITY_H

typedef struct entity
{
	Position position;
	int health;
	char symbol;
	char floorTile;
} Entity;

struct stylus
{
    Position position;
    char symbol;
    char tip;
}

int moveEntity(Entity *ent, int x, int y);
Entity *createEntity(int x, int y, char symbol);
int drawEntity(Entity *ent);
struct stylus *createStylus(int x, int y, char tip);
void moveStylus(struct stylus *styl, int x, int y);

#endif
