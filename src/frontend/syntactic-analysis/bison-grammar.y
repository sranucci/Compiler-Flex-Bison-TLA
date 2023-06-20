%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales
	Program * program;
	Expressions * expressions;
	Expression * expression;
	ChartType * chart_type;
	ChartType1 * chart_type_1;
	ChartType2 * chart_type_2;
	Number * number;
	Data * data;
	Interval * interval;
	IntervalWithStep * interval_with_step;
	ValueList * value_list;
	Value * value;
	YData * y_data;
	Function * function;
	AddDatas * add_datas;
	AddData * add_data;
	SetAxis * set_axis;
	Color * color;
	Xpression * xpression;
	StepLeft * step_left;
	StepRight * step_right;
	Factor * factor;
	Constants * constant;
	// Terminales.
	token token;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD
%token <token> CREATE
%token <token> CHART 
%token <token> LABEL
%token <token> WHERE
%token <token> X
%token <token> AND
%token <token> Y 
%token <token> SCATTER
%token <token> LINE
%token <token> BAR
%token <token> PIE
%token <token> IN
%token <token> IS
%token <token> CURLYOPEN
%token <token> CURLYCLOSE
%token <token> USERVALUE
%token <token> COMMA
%token <token> DATA
%token <token> XAXIS
%token <token> YAXIS
%token <token> VALUE
%token <token> SET
%token <token> WITH
%token <token> COLOR
%token <token> COLOROPTION
%token <token> EQUALS
%token <token> OPENPARENTHESIS
%token <token> CLOSEPARENTHESIS
%token <token> OPENBRACKET
%token <token> CLOSEBRACKET
%token <token> STEPSEPARATOR
%token <token> ADDMATH
%token <token> SUBMATH
%token <token> MULTMATH
%token <token> DIVMATH

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expressions> expressions
%type <expression> expression
%type <chart_type> chart_type
%type <chart_type_1> chart_type_1
%type <chart_type_2> chart_type_2
%type <number> number
%type <data> data
%type <interval> interval
%type <interval_with_step> interval_with_step
%type <value_list> value_list
%type <value> value
%type <y_data> y_data
%type <function> function
%type <add_datas> add_datas
%type <add_data> add_data
%type <set_axis> set_axis
%type <color> color
%type <step_left> step_left
%type <step_right> step_right
%type <xpression> xpression
%type <factor> factor
%type <constant> constant

// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADDMATH SUBMATH
%left MULTMATH DIVMATH

// El símbolo inicial de la gramatica.
%start program

%%

program: expressions	{ $$ = ProgramGrammarAction(1); }
;

expressions: expression expressions { $$ = 0; }
	| %empty { $$ = 0; }
	;

expression: CREATE CHART chart_type { $$ = 0; }
;

chart_type: chart_type_1 LABEL WHERE X data AND Y y_data color set_axis { $$ = 0; }
	| chart_type_2 LABEL add_datas { $$ = 0; }
	;


chart_type_1: SCATTER { $$ = 0; }
	| LINE { $$ = 0; }
	;

chart_type_2: BAR { $$ = 0; }
	| PIE { $$ = 0; }
	;


number: USERVALUE { $$ = 0; }
;

data: IN interval { $$ = 0; }
	| IN interval_with_step { $$ = 0; }
	| IS value_list { $$ = 0; }
	;


interval: step_left USERVALUE STEPSEPARATOR USERVALUE step_right { $$ = 0; }
	;

interval_with_step: step_left USERVALUE STEPSEPARATOR USERVALUE STEPSEPARATOR USERVALUE step_right { $$ = 0; }
	;

step_left: OPENPARENTHESIS { $$ = 0; }
	| OPENBRACKET { $$ = 0; }
	;
	
step_right: CLOSEPARENTHESIS { $$ = 0; }
	| CLOSEBRACKET { $$ = 0; }
	;


value_list: CURLYOPEN value CURLYCLOSE { $$ = 0; };


value: USERVALUE  { $$ = 0; }
	| USERVALUE COMMA value { $$ = 0; }
	;

y_data: data  { $$ = 0; }
	| EQUALS function { $$ = 0; }
	;


function: xpression { $$ = 0; };


xpression: xpression ADDMATH xpression					{ $$ = 0; }
	| xpression SUBMATH xpression						{ $$ = 0; }
	| xpression MULTMATH xpression						{ $$ = 0; }
	| xpression DIVMATH xpression						{ $$ = 0; }
	| factor											{ $$ = 0; }
	;

factor: OPENPARENTHESIS xpression CLOSEPARENTHESIS				{ $$ = 0; }
	| constant														{ $$ = 0; }
	;

constant: USERVALUE													{ $$ = 0; }
	| X { $$ = 0; }
	| SUBMATH X { $$ = 0;}
	;

add_datas: add_data add_datas{ $$ = 0; }
	| %empty { $$ = 0; }
	;

add_data: ADD DATA LABEL VALUE EQUALS number color { $$ = 0; }
;

set_axis: SET XAXIS LABEL SET YAXIS LABEL { $$ = 0; }
	| %empty{ $$ = 0; }
	;

color: WITH COLOR COLOROPTION { $$ = 0; }
	| %empty { $$ = 0; }
	;


%%
