%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expressions;
	int expression;
	int chart_type;
	int chart_type_1;
	int chart_type_2;
	int number;
	int data;
	int interval;
	int interval_with_step;
	int value_list;
	int value;
	int y_data;
	int function;
	int add_datas;
	int add_data;
	int set_axis;
	int color;

	// Terminales.
	int add;
	int create;
	int chart;
	int label;
	int where;
	int x;
	int and;
	int y;
	int scatter;
	int line;
	int bar;
	int pie;
	int in;
	int is;
	int curlyopen;
	int curlyclose;
	int uservalue;
	int comma;
	int add;
	int data;
	int x-axis;
	int y-axis;
	int value;
	int set;
	int with;
	int color;
	int coloroption;
	int equals;/
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
%token <token> ADD
%token <token> DATA
%token <token> X-AXIS
%token <token> Y-AXIS
%token <token> VALUE
%token <token> SET
%token <token> WITH
%token <token> COLOR
%token <token> COLOROPTION
%token <token> EQUALS


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

// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program

%%

program: expressions	{ $$ = int ProgramGrammarAction(1);}

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

/*
interval: /*(0; 5] o similares { $$ = 0; };

interval_with_step: /*[-1; 1.5; 10) o similares { $$ = 0; };
*/

value_list: CURLYOPEN value CURLYCLOSE { $$ = 0; };


value: USERVALUE  { $$ = 0; }
	| USERVALUE COMMA value { $$ = 0; }
	;

y_data: data  { $$ = 0; }/*| = function*/
	;


add_datas: add_data add_datas{ $$ = 0; }
	| %empty { $$ = 0; }
	;

add_data: ADD DATA label VALUE EQUALS number color { $$ = 0; }
;

set_axis: SET XAXIS label SET YAXIS label{ $$ = 0; }
	| %empty{ $$ = 0; }
	;

color: WITH COLOR COLOROPTION { $$ = 0; }
	| %empty { $$ = 0; }
	;


%%
