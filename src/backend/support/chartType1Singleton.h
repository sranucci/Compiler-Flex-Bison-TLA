#ifndef CT1SINGLETON
#define CT1SINGLETON

#include "../semantic-analysis/abstract-syntax-tree.h"


void addToList(double x, double y);
void setCT1Name(char * buff);




void setSelectedColor(SelectedColor color);

void addCoordinate(double x, double y);

void getXandYAxisData(char * xbuff,char * ybuff );

void setXAxisName(char * name);
void setYAxisName(char * name);

int getXAxisName(char * buffer);

ChartType1State getChartType1State();
void setChartType1State(ChartType1State state);
int getYAxisName(char * buffer);

void getDataAsScatter(char * buffer);


void getChartType1GraphName(char * buffer);
int getChartType1XAxisLabel(char * label);
int getChartType1YAxisLabel(char * label);
int getChartType1Color(char * color);



void freeCT1Mem();


#endif