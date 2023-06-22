#ifndef GARBAGECOLLECTOR
#define GARBAGECOLLECTOR


void addToGarbageCollector(void *memDir);
void freeAll();
void * getMemory(int bytes);
#endif