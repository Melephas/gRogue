#include <stdlib.h>

#include "dmem.h"

struct DMR *initialiseDMR(unsigned int initialSize, unsigned int growSize)
{
    struct DMR *ret = malloc(sizeof(struct DMR));
    ret->count = 0;
    ret->size = initialSize;
    ret->growSize = growSize;
    ret->objects = malloc(sizeof(struct Object *) * initialSize);

    return ret;
}

void addObject(void *object, void (*freeFunction)(void *object))
{
}

void deleteObject(void *object)
{
}
