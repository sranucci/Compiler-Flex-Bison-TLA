#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/



Program * ProgramGrammarAction(Expressions * expressions) {
	
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/

	Program * program = calloc(1,sizeof(Program));
	program->expressions = expressions;
	state.program = program;

	return program;
}



//funciones nuestras

ChartType2 * BarGrammarAction(){
	ChartType2 * ct2 = calloc(1,sizeof(ChartType2));
	ct2->chartType2State = BARTYPE;
	return ct2;
}

ChartType2 * PieGrammarAction(){
	ChartType2 * ct2 = calloc(1,sizeof(ChartType2));
	ct2->chartType2State = PIETYPE;
	return ct2;
}

ChartType * ChartType2GrammarAction(ChartType2 * ct2, AddDatas * datas){
	ChartType * ct = calloc(1,sizeof(ChartType));
	ct->chartTypeState = TYPE2;
	ct->chartType2 = ct2;
	ct->addDatas = datas;
	return ct;
}

Number * NumberGrammarAction(double a){
	Number * number = calloc(1,sizeof(Number));
	number->value = a;
	return number;
} 


Color * ColorGrammarAction(char * string){
	Color * color = calloc(1,sizeof(Color));
	color->colorState;
	if ( strcmp(string, "blue") == 0){
		color->col = REDCOLOR;
	} else if ( strcmp(string,"red") == 0){
		color->col = BLUECOLOR;
	}
	return color;
}


AddData * DataGrammarAction(Number * number, Color * color){
	AddData * addData = calloc(1,sizeof(AddData));
	addData->number = number;
	addData->color = color;
	return addData;
}

Expression * ExpressionGrammarAction(ChartType *chart){
	Expression * expr = calloc(1,sizeof(Expression));
	expr->chartType = chart;
	return expr;
}

Expressions * ExpressionsGrammarAction(Expression * expression, Expressions * expressions){
	Expressions * expr = calloc(1,sizeof(Expressions));
	expr->expression = expression;
	expr->expressions = expressions;
	return expr;
}



AddDatas * AddDatasGrammarAction(AddData * data, AddDatas * datas){
	AddDatas * d = calloc(1,sizeof(AddDatas));
	d->addData = data;
	d->addDatas = datas;
	return d;
}


void freeProgram(Program * program){
	freeExpressions(program->expressions);
	free(program);
}
void freeExpressions(Expressions * expressions){
	if(expressions->expressionsState == NOT_EMPTY){
		freeExpression(expressions->expression);
		freeExpressions(expressions->expressions);
	}
	free(expressions);
}
void freeExpression(Expression * expression){
	freeChartType(expression->chartType);
	free(expression);
}
void freeChartType(ChartType * chartType){
	if(chartType->chartTypeState == TYPE1){
		freeChartType1(chartType->chartType1);
		freeData(chartType->data);
		freeYData(chartType->yData);
		freeSetAxis(chartType->setAxis);
	} else if (chartType->chartTypeState == TYPE2){
		freeChartType2(chartType->chartType2);
		freeAddDatas(chartType->addDatas);
	}
	free(chartType);
}
void freeChartType1(ChartType1 * chartType1){
	free(chartType1);
}
void freeChartType2(ChartType2 * chartType2){
	free(chartType2);
}
void freeNumber(Number * number){
	free(number);
}
void freeData(Data * data){
	if(data->dataState == INTERVAL)
		freeInterval(data->interval);
	else if(data->dataState == INTERVALWSTEP)
		freeIntervalWithStep(data->intervalWithStep);
	else if(data->dataState == VALUELIST)
		freeValueList(data->valueList);
		
	free(data);
}
void freeInterval(Interval * interval){
	freeStepLeft(interval->stepLeft);
	freeStepRight(interval->stepRight);
	free(interval);
}
void freeIntervalWithStep(IntervalWithStep * intervalWithStep){
	freeStepLeft(intervalWithStep->stepLeft);
	freeStepRight(intervalWithStep->stepRight);
	free(intervalWithStep);
}
void freeStepLeft(StepLeft * stepLeft){
	free(stepLeft);
}
void freeStepRight(StepRight * stepRight){
	free(stepRight);
}
void freeValueList(ValueList * valueList){
	freeValue(valueList->value);
	free(valueList);
}
void freeValue(Value * value){
	free(value);
}
void freeYData(YData * yData){
	if(yData->yDataState == ISDATA){
		freeData(yData->data);
	} else if (yData->yDataState == FUNCTION){
		freeFunction(yData->function);
	}

	free(yData);
}
void freeColor(Color * color){
	free(color);
}
void freeAddData(AddData * addData){
	freeNumber(addData->number);
	freeColor(addData->color);
	free(addData);
}
void freeAddDatas(AddDatas * addDatas){
	if(addDatas->addDatasState == WITHDATA){
		freeAddData(addDatas->addData);
		freeAddDatas(addDatas->addDatas);
	}
	free(addDatas);
}
void freeConstant(Constant * constant){
	free(constant);
}
void freeFactor(Factor * factor){
	if(factor->state == CONSTANT){
		freeConstant(factor->constant);
	} else if(factor->state == WITHPARENTHESIS){
		freeXpression(factor->xpression);
	}
	free(factor);
}
void freeXpression(Xpression * xpression){
	freeXpression(xpression->xpressionLeft);
	freeXpression(xpression->xpressionRight);
	free(xpression);
}
void freeFunction(Function * function){
	freeFunction(function->function);
	free(function);
}
void freeSetAxis(SetAxis * setAxis){
	free(setAxis);
}