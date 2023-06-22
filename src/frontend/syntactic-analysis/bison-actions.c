#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "../../backend/support/chartType1Singleton.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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



Program * ProgramGrammarAction(Expression * expression) {
	
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
	printf("llegamos hasta program\n");
	if ( expression->chartType->chartTypeState == TYPE2  ){
		for ( AddDatas *currentPtr = expression->chartType->addDatas; currentPtr->addDatasState != NODATA ; currentPtr = currentPtr->addDatas){
			printf("agregando %s\n",currentPtr->addData->dataName);
			addToCT2Data(currentPtr->addData->number->value,currentPtr->addData->color->col,currentPtr->addData->dataName);
		}

		state.isChartType1 = false;
	} else {
		printf("chartType1\n");
		Value * xvals = expression->chartType->data->valueList->value;
		Value * yvals = expression->chartType->yData->valueList->value;
		while ( yvals->valueState != ONLYVALUE && xvals->valueState != ONLYVALUE){
			addCoordinate(xvals->userNumber,yvals->userNumber);
			yvals = yvals->value;
			xvals = xvals->value;
		}
		
		if ( yvals->valueState != ONLYVALUE || xvals->valueState != ONLYVALUE){
			//todo setear error
		} else {
			addCoordinate(xvals->userNumber,yvals->userNumber);
			yvals = yvals->value;
			xvals = xvals->value;
		}
		setSelectedColor(expression->chartType->color->col);
		if ( expression->chartType->setAxis->setAxisState = CONTAINSAXISDATA ){
			setXAxisName(expression->chartType->setAxis->xaxis);
			setYAxisName(expression->chartType->setAxis->yaxis);
		}

		state.isChartType1 = true;

	}
	Program * program = calloc(1,sizeof(Program));
	program->expression = expression;
	state.program = program;


	return program;
}




AddDatas * EmptyDatasGrammarAction(){
	printf("emptyDatasActionFired\n");
	AddDatas * data = calloc(1, sizeof(AddDatas));
	data->addDatasState = NODATA;
	return data;
}

Color * EmptyColorGrammarAction(){
	printf("EmptyColorGrammarActionFired\n");
	Color * color = calloc(1,sizeof(Color));
	color->col = BLUECOLOR;
	return color;
}

//funciones nuestras

ChartType2 * BarGrammarAction(){
	printf("BarGrammarActionFired\n");
	ChartType2 * ct2 = calloc(1,sizeof(ChartType2));
	ct2->chartType2State = BARTYPE;
	setCT2BarChart();
	return ct2;
}

ChartType2 * PieGrammarAction(){
	printf("PieGrammarActionFired\n");
	ChartType2 * ct2 = calloc(1,sizeof(ChartType2));
	ct2->chartType2State = PIETYPE;
	setCT2PieChart();
	return ct2;
}

ChartType * ChartType2GrammarAction(ChartType2 * ct2, char * graphName, AddDatas * datas){
	printf("CT2GrammarActionFired\n");
	ChartType * ct = calloc(1,sizeof(ChartType));
	ct->chartTypeState = TYPE2;
	ct->chartType2 = ct2;
	ct->addDatas = datas;
	setCT2Name(graphName);
	//agregamos los elementos al singleton
	printf("estamos en ChartType2GrammarAction\n");
	return ct;
}

Number * NumberGrammarAction(double a){
	Number * number = calloc(1,sizeof(Number));
	printf("the number recieved was %f\n",a);
	number->value = a;
	return number;
} 

//"red"|"blue"|"orange"|"yellow"|"black"|"green"      
Color * ColorGrammarAction(char * string){
	printf("ColorGrammarActionFired\n");
	Color * color = calloc(1,sizeof(Color));



	printf("the color recieved was %s\n",string);
	if ( strcmp(string, "blue") == 0){
		color->col = BLUECOLOR;
	} else if ( strcmp(string,"red") == 0){
		color->col = REDCOLOR;
	} else if ( strcmp(string, "orange") == 0){
		color->col = ORANGECOLOR;
	} else if ( strcmp(string,"yellow") == 0){
		color->col = YELLOWCOLOR;
	} else if ( strcmp(string,"green") == 0){
		color->col = GREENCOLOR;
	} else {
		color->col = BLACKCOLOR;
	} 
	return color;
}



AddData * DataGrammarAction(char * dataName,Number * number, Color * color){
	printf("DataGrammarActionFired\n");

	AddData * addData = calloc(1,sizeof(AddData));
	addData->number = number;
	addData->color = color;
	addData->dataName = dataName;
	return addData;
}

Expression * ExpressionGrammarAction(ChartType *chart){
	printf("ExpressionGrammarActionFired\n");

	Expression * expr = calloc(1,sizeof(Expression));
	printf("malloc Success\n");
	expr->chartType = chart;
	return expr;
}





AddDatas * AddDatasGrammarAction(AddData * data, AddDatas * datas){
	printf("AddDatasGrammarActionFired\n");

	AddDatas * d = calloc(1,sizeof(AddDatas));
	d->addData = data;
	d->addDatas = datas;
	d->addDatasState = WITHDATA;
	return d;
}


//nuevas funciones

SetAxis * SetAxisGrammarAction(char * xAxis, char * yAxis){
	printf("SetAxxisGrammarActionFired\n");
	SetAxis * axis = calloc(1,sizeof(SetAxis));
	axis->xaxis = xAxis;
	axis->yaxis = yAxis;
	axis->setAxisState = CONTAINSAXISDATA;
	return axis;
}


SetAxis * SetEmptyAxisGrammarAction(){
	printf("SetEmptyAxxisGrammarActionFired\n");
	SetAxis * axis = calloc(1,sizeof(SetAxis));
	axis->setAxisState = EMPTYAXISSTATE;
	return axis;
}

Value * UserValueGrammarAction(double val){
	printf("SetUserValueGrammarActionFired\n");
	printf("recieved value %f\n",val);
	Value * v = calloc(1,sizeof(Value));
	v->valueState = ONLYVALUE;
	v->userNumber = val;
	return v;
}

Value * UserValueCommaGrammarAction(double val, Value * next){
	printf("UserValueCommaGrammarActionFired\n");
	Value * v = calloc(1,sizeof(Value));
	v->valueState = MOREVALUES;
	v->userNumber = val;
	v->value = next;
	return v;
}

ValueList *  ValueListGrammarAction(Value * first){
	printf("ValueListGrammarActionFired\n");
	ValueList * l = calloc(1,sizeof(ValueList));
	l->value = first;
	return l;
}

Data * DataValueListGrammarAction(ValueList * list){
	printf("DataGrammarActionFired\n");
	Data * d = calloc(1,sizeof(Data));
	d->valueList = list;
	return d;
}


ChartType1 * ScatterGrammarAction(){
	printf("ScatterGrammarActionFired\n");

	ChartType1 * c = calloc(1,sizeof(ChartType1));
	c->chartType1State = SCATTERTYPE;

	return c;
}


ChartType1 * LineGrammarAction(){
	printf("LineGrammarActionFired\n");

	ChartType1 * c = calloc(1,sizeof(ChartType1));
	c->chartType1State = LINETYPE;
	return c;
}


ChartType * ChartType1GrammarAction(ChartType1 * chartType1,char * graphName,Data * xdata,Data * ydata,Color * color, SetAxis * axis ){
	printf("CT1ActionFired\n");
	printf("%s\n",graphName);
	ChartType * c = calloc(1,sizeof(ChartType));
	c->chartTypeState = TYPE1;
	c->chartType1 = chartType1;
	c->data = xdata;
	c->yData = ydata;
	c->color =  color;
	//TODO setear singleton el nombre
	setCT1Name(graphName);
	c->setAxis = axis;

	return c;
}


/*
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

*/