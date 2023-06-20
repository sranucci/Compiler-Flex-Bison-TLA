#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct Program Program;
typedef struct Expression Expression;
typedef struct Expressions Expressions;
typedef struct ChartType ChartType;
typedef struct ChartType1 ChartType1; 
typedef struct ChartType2 ChartType2;
typedef struct Number Number;
typedef struct Data Data;
typedef struct Interval Interval;
typedef struct IntervalWithStep IntervalWithStep;
typedef struct StepLeft StepLeft;
typedef struct StepRight StepRight;
typedef struct ValueList ValueList;
typedef struct Value Value;
typedef struct YData YData;
typedef struct Color Color;
typedef struct AddData AddData;
typedef struct AddDatas AddDatas;
typedef struct Constant Constant;
typedef struct Factor Factor;
typedef struct Xpression Xpression;
typedef struct Function Function;
typedef struct Xpression Xpression;
typedef struct Function Function;
typedef struct SetAxis SetAxis;



/**
* Para cada no-terminal se define una nueva estructura que representa su tipo
* de dato y, por lo tanto, su nodo en el AST (Árbol de Sintaxis Abstracta).
*/

/**
* En caso de que un no-terminal ("Factor" en este caso), posea más de una
* regla de producción asociada, se crea además de la estructura un enumerado
* que identitifque cada reducción posible (cada regla de producción). Luego,
* se agrega una instancia de este enumerado dentro del nodo del no-terminal.
*
* De este modo, al recorrer el AST, es posible determinar qué nodos hijos
* posee según el valor de este enumerado.
*/

typedef struct Program {
	Expressions * expressions;
} Program;

typedef enum ExpressionsState {
	NOT_EMPTY,
	EMPTY,
} ExpressionsState;

typedef struct Expressions {
	ExpressionsState expressionsState;

	//NOT_EMPTY
	Expression * expression;
	Expressions * expressions;

	//EMPTY
} Expressions;


typedef struct Expression {
	ChartType * chartType;
} Expression;

typedef enum ChartTypeState {
	TYPE1,
	TYPE2,
} ChartTypeState;

typedef struct ChartType {
	ChartTypeState chartTypeState;

	//TYPE1
	ChartType1 * chartType1;
	Data * data;
	YData * yData;
	SetAxis * setAxis;

	//TYPE2
	ChartType2 * chartType2;
	AddDatas * addDatas;
} ChartType;

typedef enum ChartType1State {
	SCATTERTYPE,
	LINETYPE,
} ChartType1State;

typedef struct ChartType1 {
	//puede ser 'scatter' o 'line'
	ChartType1State chartType1State;
} ChartType1;

typedef enum ChartType2State {
	BARTYPE,
	PIETYPE,
} ChartType2State;

typedef struct ChartType2 {
	//puede ser 'bar' o 'pie'
	ChartType2State chartType2State;
} ChartType2;

typedef struct Number {
	double value; //puede ser cualquier numero
} Number;

typedef enum DataState {
	INTERVAL,
	INTERVALWSTEP,
	VALUELIST,
} DataState;

typedef struct Data {
	DataState dataState;
	Interval * interval;
	IntervalWithStep * intervalWithStep;
	ValueList * valueList;
} Data;

typedef struct Interval {
	StepLeft * stepLeft;
	StepRight * stepRight;
} Interval;

typedef struct IntervalWithStep {
	StepLeft * stepLeft;
	StepRight * stepRight;
} IntervalWithStep;

typedef enum StepLeftState {
	OPENPAR,
	OPENBRA,
} StepLeftState;

typedef struct StepLeft {
	StepLeftState stepLeftState;
} StepLeft;

typedef enum StepRightState {
	CLOSEPAR,
	CLOSEBRA,
} StepRightState;

typedef struct StepRight {
	StepRightState stepRightState;
} StepRight;


typedef struct ValueList {
	Value * value;
} ValueList;

typedef enum ValueState {
	ONLYVALUE,
	MOREVALUES,
} ValueState;

typedef struct Value {
	ValueState valueState;

	//MOREVALUES
	Value * value;

	//ONLYVALUE
} Value;

typedef enum YDataState {
	ISDATA,
	FUNCTION,
} YDataState;

typedef struct YData {
	YDataState yDataState;

	//DATA
	Data * data;

	//FUNCTION
	Function * function;
} YData;

typedef enum  {
	WITHOUTCOLOR,
	WITHCOLOR,
} ColorState;

typedef enum {
	REDCOLOR,
	BLUECOLOR
} SelectedColor;

typedef struct Color{
	ColorState colorState;
	SelectedColor col;
	//NOTEMPTY
	int a;

	//EMPTY
} Color;

typedef struct AddData {
	Number * number;
	Color * color;
} AddData;

typedef enum AddDatasState {
	NODATA,
	WITHDATA,
} AddDatasState;

typedef struct AddDatas {
	AddDatasState addDatasState;

	//WITHDATA
	AddData * addData;
	AddDatas * addDatas;

	//NODATA
} AddDatas;

typedef enum constant_states {
	USERVALUEDATA,
	XDATA,
	SUBMATHDATA,
} constant_states;

typedef struct Constant {
	constant_states state;
	
} Constant;

typedef enum factorStates {
	CONSTANT,
	WITHPARENTHESIS
} factorStates;


typedef struct Factor {
	factorStates state;

	//CONSTANT
	Constant * constant;

	//WITHPARENTHESIS
	Xpression * xpression;
} Factor;


typedef enum xPressionState {
	ADDMATHDATA,
	MULTMATHDATA,
	DIVMATHDATA,
} xPressionState;

typedef struct Xpression {
	xPressionState state;
	Xpression * xpressionLeft;
	Xpression * xpressionRight;
} Xpression;


typedef struct Function {
	Function * function;
} Function;

typedef enum SetAxisState {
	EMPTYAXISSTATE,
	CONTAINSAXISDATA
} SetAxisState;

typedef struct SetAxis {
	SetAxisState setAxisState;
} SetAxis;

#endif
