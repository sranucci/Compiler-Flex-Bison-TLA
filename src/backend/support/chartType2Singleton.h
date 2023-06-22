#ifndef CALCULATOR_HEADER
#define CALCULATOR_HEADER

/**
* La calculadora pertenece al dominio de esta aplicación, y por ello se
* codifican en este lugar sus modelos y operaciones. Para que el dominio
* específico se encuentre completamente desacoplado del compilador, debería
* ser posible calcular algo utilizando estas funciones directamente.
*/
/*
int Add(const int leftAddend, const int rightAddend);

int Subtract(const int minuend, const int subtract);

int Multiply(const int multiplicand, const int multiplier);

int Divide(const int dividend, const int divisor);
*/

#include "../semantic-analysis/abstract-syntax-tree.h"


void addToCT2Data(double number, SelectedColor color, const char* name);
void setCT2PieChart();
void setCT2Name(char * name);
void setCT2BarChart();
void printCT2List();

void outputLabels(char * labels);
void outputBarNumbers(char * numbers);
void outputColors(char * colors);
void getGraphName(char * graphName);
void getChartType(char * buffer);
void freeCT2Data();
#endif
