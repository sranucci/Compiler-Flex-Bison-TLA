#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chartType1Singleton.h"

#define SIZE 512

//nodos de la lista
typedef struct chartType1Node {
    double x;
    double y;
    struct chartType1Node * next;
} chartType1Node;


//nodo maestro, 
typedef struct chartType1Singleton {
    char graphName[SIZE];
    char xAxisLabel[SIZE];
    char yAxisLabel[SIZE];
    char color[SIZE];
    chartType1Node * first;
    ChartType1State state;
} chartType1Singleton;


//patron singleton
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


//libera recursos alocados
void freeCT1Mem(){
    chartType1Singleton * ptr = getSingletonCT1Instance();
    for ( chartType1Node * current = ptr->first; current != NULL;){
        chartType1Node * toFree = current;
        current = current->next;
        free(toFree);
    }
}

void setChartType1State(ChartType1State state){
    getSingletonCT1Instance()->state = state;
}

ChartType1State getChartType1State(){
    return getSingletonCT1Instance()->state;
}



//devuelve los datos en buffer en formato necesario para grafico SCATTER
void getDataAsScatter(char * buffer){
    chartType1Singleton * master = getSingletonCT1Instance();
    int bytesCopied = 0;
    for ( chartType1Node * current = master->first; current != NULL; current = current->next){
        bytesCopied += sprintf(buffer + bytesCopied,"{ x : %f , y : %f },",current->x,current->y);
    }
    buffer[bytesCopied - 1] = 0;//sacamos la ,
}

// devuelve nombre del grafico
void getChartType1GraphName(char * buffer){
    strcpy(buffer,getSingletonCT1Instance()->graphName);
}

//devuelve nombre del eje x si lo hubiese
int getChartType1XAxisLabel(char * label){
    if ( strlen(getSingletonCT1Instance()->xAxisLabel) > 0 ){
        strcpy(label,getSingletonCT1Instance()->xAxisLabel);
        return 1;
    }
    return 0;
}

//devuelve nombre del eje y si lo hubiese
int getChartType1YAxisLabel(char * label){
    if ( strlen(getSingletonCT1Instance()->yAxisLabel) > 0 ){
        strcpy(label,getSingletonCT1Instance()->yAxisLabel);
        return 1;
    }
    return 0;
}


//devuelve el color del grafico
int getChartType1Color(char * color){
    if ( strlen(getSingletonCT1Instance()->color) > 0 ){
        strcpy(color,getSingletonCT1Instance()->color);
        return 1;
    }
    return 0;
}




//agrega un par de coordenada a la lista
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

//setea el nombre del grafico
void setCT1Name(char * buff){
    strcpy(getSingletonCT1Instance()->graphName,buff);
}


//setea el color del grafico, en el formato necesario para chart js
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
    printf("%s\n",name);
    strcpy(getSingletonCT1Instance()->xAxisLabel,name);
}


void setYAxisName(char * name){
    strcpy(getSingletonCT1Instance()->yAxisLabel,name);
}


//recupera los datos para el eje x e y
void getXandYAxisData(char * xbuff,char * ybuff ){
    chartType1Singleton * ptr = getSingletonCT1Instance();
    int xBytesRead = 0;
    int yBytesRead = 0;

    for (chartType1Node * current = ptr->first; current != NULL ; current = current->next){
        xBytesRead += sprintf(xbuff + xBytesRead,"%f,",current->x);
        yBytesRead += sprintf(ybuff + yBytesRead,"%f,",current->y);
    }
    xbuff[xBytesRead - 1] = 0;
    ybuff[yBytesRead - 1] = 0;
}

