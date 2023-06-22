#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chartType1Singleton.h"

#define SIZE 512

typedef struct chartType1Node {
    double x;
    double y;
    struct chartType1Node * next;
} chartType1Node;

typedef struct chartType1Singleton {
    char graphName[SIZE];
    char xAxisLabel[SIZE];
    char yAxisLabel[SIZE];
    char color[SIZE];
    chartType1Node * first;
    ChartType1State state;
} chartType1Singleton;


static chartType1Singleton * createSingletonCT1Instance(){
    static chartType1Singleton singleton;
    memset(&singleton,0,sizeof(chartType1Singleton));
    return &singleton;
}


static chartType1Singleton * getSingletonCT1Instance(){
    static chartType1Singleton * ptr;
    if ( ptr == NULL){
        ptr = createSingletonCT1Instance();
    }

    return ptr;
}


void setChartType1State(ChartType1State state){
    getSingletonCT1Instance()->state = state;
}

ChartType1State getChartType1State(){
    return getSingletonCT1Instance()->state;
}


void getDataAsScatter(char * buffer){
    chartType1Singleton * master = getSingletonCT1Instance();
    int bytesCopied = 0;
    for ( chartType1Node * current = master->first; current != NULL; current = current->next){
        bytesCopied += sprintf(buffer + bytesCopied,"{ x : %f , y : %f },",current->x,current->y);
    }
    buffer[bytesCopied - 1] = 0;//sacamos la ,
}


void getChartType1GraphName(char * buffer){
    strcpy(buffer,getSingletonCT1Instance()->graphName);
}


int getChartType1XAxisLabel(char * label){
    if ( strlen(getSingletonCT1Instance()->xAxisLabel) > 0 ){
        strcpy(label,getSingletonCT1Instance()->xAxisLabel);
        return 1;
    }
    return 0;
}


int getChartType1YAxisLabel(char * label){
    if ( strlen(getSingletonCT1Instance()->yAxisLabel) > 0 ){
        strcpy(label,getSingletonCT1Instance()->yAxisLabel);
        return 1;
    }
    return 0;
}



int getChartType1Color(char * color){
    if ( strlen(getSingletonCT1Instance()->color) > 0 ){
        strcpy(color,getSingletonCT1Instance()->color);
        return 1;
    }
    return 0;
}





void addCoordinate(double x, double y) {
    chartType1Singleton *singleton = getSingletonCT1Instance();

    chartType1Node *newNode = (chartType1Node *)malloc(sizeof(chartType1Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;

    if (singleton->first == NULL) {
        singleton->first = newNode;
    } else {
        chartType1Node *currentNode = singleton->first;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }

}

void setCT1Name(char * buff){
    strcpy(getSingletonCT1Instance()->graphName,buff);
}



void setSelectedColor(SelectedColor color){
    char *chosenColor;
    switch (color) {
    case REDCOLOR:
        chosenColor = "rgba(255, 0, 0, 0.7)";
        break;
    case BLUECOLOR:
        chosenColor = "rgba(0, 0, 255, 0.7)";
        break;
    case ORANGECOLOR:
        chosenColor = "rgba(255, 165, 0, 0.7)";
        break;
    case YELLOWCOLOR:
        chosenColor = "rgba(255, 255, 0, 0.7)";
        break;
    case BLACKCOLOR:
        chosenColor = "rgba(0, 0, 0, 0.7)";
        break;
    default:
        chosenColor = "rgba(0, 255, 0, 0.7)";
        break;
    }
    strcpy(getSingletonCT1Instance()->color,chosenColor);
}


void setXAxisName(char * name){
    strcpy(getSingletonCT1Instance()->xAxisLabel,name);
}


void setYAxisName(char * name){
    strcpy(getSingletonCT1Instance()->yAxisLabel,name);
}

int getXAxisName(char * buffer){
    chartType1Singleton * ptr = getSingletonCT1Instance();
    if ( ptr->xAxisLabel == NULL){
        return 0;
    }
    strcpy(buffer,ptr->xAxisLabel);
    return 1;
}



int getYAxisName(char * buffer){
    chartType1Singleton * ptr = getSingletonCT1Instance();
    if ( ptr->yAxisLabel == NULL){
        return 0;
    }
    strcpy(buffer,ptr->yAxisLabel);
    return 1;
}
