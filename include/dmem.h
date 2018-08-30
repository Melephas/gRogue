#ifndef DMEM_H
#define DMEM_H

struct DMR
{
    unsigned int count;
    unsigned int size;
    unsigned int growSize;
    void *objects;
}

struct Object
{
    void *object;
    void (*freeFunc)(void *object);
}    

struct DMR *initialiseDMB(unsigned int initialSize, unsigned int growSize);
void addObject(void *object, void (*freeFunction)(void *object));
void deleteObject(void *object);

#endif
