#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
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
typedef struct Constants Constants;
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
typedef struct {
	int value;
} Constant;

/**
* En caso de que un no-terminal ("Factor" en este caso), posea más de una
* regla de producción asociada, se crea además de la estructura un enumerado
* que identitifque cada reducción posible (cada regla de producción). Luego,
* se agrega una instancia de este enumerado dentro del nodo del no-terminal.
*
* De este modo, al recorrer el AST, es posible determinar qué nodos hijos
* posee según el valor de este enumerado.
*/

typedef struct Expressions {
	Expression * expression;
	Expressions * expressions;
} Expressions;

typedef struct Expression {
	ChartType * chartType;
} Expression;

typedef struct ChartType {
	ChartType1 * chartType1;
	Data * data;
	YData * yData;
	SetAxis * setAxis;
	ChartType2 * chartType2;
	AddDatas * addDatas;
} ChartType;

typedef struct ChartType1 {
	int a;
} ChartType1;

typedef struct ChartType2 {
	int a;
} ChartType2;

typedef struct Number {
	int a;
} Number;

typedef struct Data {
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

typedef struct StepLeft {
	int a;
} StepLeft;

typedef struct StepRight {
	int a;
} StepRight;

typedef struct ValueList {
	Value * value;
} ValueList;

typedef struct Value {
	Value * value;
} Value;

typedef struct YData {
	Data * data;
	Function * function;
} YData;


typedef struct Color{
	int a;
} Color;

typedef struct AddData {
	Number * number;
	Color * color;
} AddData;


typedef struct AddDatas {
	AddData * addData;
	AddDatas * addDatas;
} AddDatas;

typedef enum constants_states {
	USERVALUEDATA,
	XDATA,
	SUBMATHDATA,
} constants_states;

typedef struct Constants {
	constants_states state;
	
} Constants;

typedef enum factor_states {
	CONSTANT,
	WITHPARENTHESIS
} factor_states;


typedef struct Factor {
	factor_states state;
	Constant * constant;
	Xpression * Xpression;
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



//---------------- De La Catedra -------------------

typedef struct {
	Expressions * expression;
} Program;

#endif
