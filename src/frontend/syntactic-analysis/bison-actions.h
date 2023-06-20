#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.

//funciones nuestras

ChartType2 * BarGrammarAction();
ChartType2 * PieGrammarAction();
ChartType * ChartType2GrammarAction(ChartType2 * ct2, AddDatas * data);
Number * NumberGrammarAction(double a);
Color * ColorGrammarAction(char * string);
AddData * DataGrammarAction(Number * number, Color * color);
Expression * ExpressionGrammarAction(ChartType *chart);
Expressions * ExpressionsGrammarAction(Expression * expression, Expressions * expressions);
Program * ProgramGrammarAction(Expressions * expressions);
AddDatas * AddDatasGrammarAction(AddData * data, AddDatas * datas);

void freeProgram(Program * program);
void freeExpressions(Expressions * expressions);
void freeExpression(Expression * expression);
void freeChartType(ChartType * chartType);
void freeChartType1(ChartType1 * chartType1);
void freeChartType2(ChartType2 * chartType2);
void freeNumber(Number * number);
void freeData(Data * data);
void freeInterval(Interval * mail);
void freeIntervalWithStep(IntervalWithStep * intervalWithStep);
void freeStepLeft(StepLeft * stepLeft);
void freeStepRight(StepRight * stepRight);
void freeValueList(ValueList * valueList);
void freeValue(Value * value);
void freeYData(YData * yData);
void freeColor(Color * color);
void freeAddData(AddData * addData);
void freeAddDatas(AddDatas * addDatas);
void freeConstant(Constant * constant);
void freeFactor(Factor * factor);
void freeXpression(Xpression * xpression);
void freeFunction(Function * function);
void freeSetAxis(SetAxis * setAxis);

#endif
