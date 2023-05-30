#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct Expression Expression;
typedef struct ProgramNode ProgramNode;
typedef struct ExpressionsNode ExpressionsNode;
typedef struct ExpressionNode ExpressionNode;
typedef struct ChartTypeNode ChartTypeNode;
typedef struct ChartType1Node ChartType1Node;
typedef struct ChartType2Node ChartType2Node;
typedef struct AddDatas AddDatas;
typedef struct Data Data;
typedef struct YData YData;
typedef struct Color Color;
typedef struct SetAxis SetAxis;
typedef struct Interval Interval;
typedef struct IntervalWithStep IntervalWithStep;
typedef struct ValueList ValueList;
typedef struct StepLeft StepLeft;
typedef struct StepRight StepRight;
typedef struct Value Value;
typedef struct Function Function;
typedef struct Number Number;

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

struct ProgramNode {
	ExpressionsNode * expressionsNode;
};

struct ExpressionsNode {
	ExpressionNode * expressionNode;
	ExpressionsNode * expressionsNode;
};


struct ExpressionNode {
	ChartTypeNode * chartTypeNode;
}; 


typedef enum {
	CHARTTYPE1,
	CHARTTYPE2
} ChartType;


struct ChartTypeNode {
	//---------first option
	ChartType * chartType;
	ChartType1Node * chartType1Node;
	Data * data;
	YData * yData;
	Color * color;
	SetAxis * setAxis;


	//---------Second option
	ChartType2Node * chartType2Node;
	AddDatas * addDatas;

};


struct ChartType1Node {
	//put constants
};


struct ChartType2Node {
	//put constatns
};


struct StepLeft{

};

struct StepRight {

};


struct ValueList {
	Value * value;
};

struct Value {

};

struct YData {
	Function * function;

};

struct AddData {
	Number * number;
	Color * color;
};





typedef enum {
	REGULAR,
	WITHSTEP,
	VALUELIST
} IntervalType;


struct Data {
	IntervalType intervalType;
	Interval * interval;
	IntervalWithStep * intervalWithStep;
	ValueList * valueList;
};










//=-----------------Cosas catedra
typedef enum {
	EXPRESSION,
	CONSTANT
} FactorType;

typedef struct {
	FactorType type;
	Expression * expression;
} Factor;











typedef enum {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	FACTOR
} ExpressionType;

struct Expression {
	ExpressionType type;
	Expression * leftExpression;
	Expression * rightExpression;
};

typedef struct {
	Expression * expression;
} Program;

#endif
