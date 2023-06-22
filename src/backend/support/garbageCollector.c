


#include <stdio.h>
#include <stdlib.h>


typedef struct memoryNode {
    void * memDir;
    struct memoryNode * next;
} memoryNode;




typedef struct {
    memoryNode * first;
} masterMemoryNode;





static masterMemoryNode * createGarbageCollectorSingletonInstance(){
    static masterMemoryNode master;
    master.first = NULL;
    return &master;
}



static masterMemoryNode * getGarbageCollectorSingletonInstance(){
    static masterMemoryNode * masterPtr = NULL;
    if ( masterPtr == NULL){
        masterPtr = createGarbageCollectorSingletonInstance();
    }
    return masterPtr;
}








void addToGarbageCollector(void *memDir) {
    masterMemoryNode *gcInstance = getGarbageCollectorSingletonInstance();
    
    memoryNode *newNode = (memoryNode *)malloc(sizeof(memoryNode));
    newNode->memDir = memDir;
    newNode->next = NULL;
    
    if (gcInstance->first == NULL) {
        gcInstance->first = newNode;
    } else {
        memoryNode *currentNode = gcInstance->first;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}


void * getMemory(int bytes){
    void * memDir = calloc(1,bytes);
    addToGarbageCollector(memDir);
    return memDir;
}

void freeAll() {
    masterMemoryNode *gcInstance = getGarbageCollectorSingletonInstance();
    
    memoryNode *currentNode = gcInstance->first;
    while (currentNode != NULL) {
        memoryNode *nextNode = currentNode->next;
        free(currentNode->memDir);
        free(currentNode);
        currentNode = nextNode;
    }
    
    gcInstance->first = NULL;
}