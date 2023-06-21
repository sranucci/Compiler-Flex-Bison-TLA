

#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
/*


int Add(const int leftAddend, const int rightAddend) {
	return leftAddend + rightAddend;
}

int Subtract(const int minuend, const int subtract) {
	return minuend - subtract;
}

int Multiply(const int multiplicand, const int multiplier) {
	return multiplicand * multiplier;
}

int Divide(const int dividend, const int divisor) {
	return dividend / divisor;
}



*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define SIZE 512

typedef enum {
    PIECHARTTYPE,
    BARCHARTTYPE,
} CT2TYPE;

typedef struct ChartType2Node {
    double number;
    char color[SIZE];
    char name[SIZE];
    struct ChartType2Node * next;
} ChartType2Node;


typedef struct {
    CT2TYPE type;
    char graphName[SIZE];
    ChartType2Node * first;
} ChartType2MasterNode;


static ChartType2MasterNode * createCT2SingletonInstance(){
    static ChartType2MasterNode master;
    memset((void *)&master,0,sizeof(ChartType2MasterNode));
    return &master;
}


static ChartType2MasterNode * getSingletonInstance(){
    static ChartType2MasterNode * master = NULL;
    if (master == NULL){
        master = createCT2SingletonInstance();
    }
    return master;
}

void getGraphName(char * graphName){
    strcpy(graphName,getSingletonInstance()->graphName);
}

//"red"|"blue"|"orange"|"yellow"|"black"|"green"      
void addToCT2Data(double number, SelectedColor color, const char* name) {
    ChartType2Node* newNode = (ChartType2Node*)malloc(sizeof(ChartType2Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

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


    

    printf("adding the following:%f,%s\n",number,name);
    newNode->number = number;
    strncpy(newNode->color, chosenColor, SIZE);
    strncpy(newNode->name, name, SIZE);
    newNode->next = NULL;

    ChartType2MasterNode* master = getSingletonInstance();
    if (master->first == NULL) {
        master->first = newNode;
    } else {
        ChartType2Node* current = master->first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void setCT2Name(char * name){
    strcpy(getSingletonInstance()->graphName,name);
}

void setCT2PieChart(){
    getSingletonInstance()->type = PIECHARTTYPE;
}

void setCT2BarChart(){
    getSingletonInstance()->type = BARCHARTTYPE;
}

void printCT2List() {
    ChartType2MasterNode* master = getSingletonInstance();
    ChartType2Node* current = master->first;
    //printf("Graph Name: %s\n", master->GraphName);
    while (current != NULL) {
        printf("Number: %.2lf, Color: %s, Name: %s\n", current->number, current->color, current->name);
        current = current->next;
    }
}


void outputLabels(char * labels){
    ChartType2MasterNode * masterNode = getSingletonInstance();
    int i = 0;
    labels[i++] = '[';
    for ( ChartType2Node * currentPtr = masterNode->first; currentPtr != NULL; currentPtr = currentPtr->next){
        i +=  sprintf(labels + i,"%s,",currentPtr->name);
    }
    labels[i - 1] = ']';
    labels[i] = 0;
}


void outputBarNumbers(char * numbers){
    ChartType2MasterNode * masterNode = getSingletonInstance();
    int i = 0;
    numbers[i++] = '[';
    for ( ChartType2Node * currentPtr = masterNode->first; currentPtr != NULL; currentPtr = currentPtr->next){
        i +=  sprintf(numbers + i,"%f,",currentPtr->number);
    }
    numbers[i - 1] = ']';
    numbers[i] = 0;
}

void outputColors(char * colors){
    ChartType2MasterNode * masterNode = getSingletonInstance();
    int i = 0;
    colors[i++] = '[';
    for ( ChartType2Node * currentPtr = masterNode->first; currentPtr != NULL; currentPtr = currentPtr->next){
        i +=  sprintf(colors + i,"\"%s\",",currentPtr->color);
    }
    colors[i - 1] = ']';
    colors[i] = 0;
}


void getChartType(char * buffer){
    ChartType2MasterNode * masterNode = getSingletonInstance();
    char * message;
    if ( masterNode->type == PIECHARTTYPE ){
        message = "pie";
    } else {
        message = "bar";
    }

    strcpy(buffer,message);
}