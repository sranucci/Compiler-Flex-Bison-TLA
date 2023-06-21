#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

typedef struct chartType2Node {
    double x;
    double y;
    struct chartType2Node * next;
} chartType2Node;

typedef struct chartType1Singleton {
    char graphName[SIZE];
    char xAxisLabel[SIZE];
    char yAxisLabel[SIZE];
    char color[SIZE];
    chartType2Node * first;
} chartType1Singleton;