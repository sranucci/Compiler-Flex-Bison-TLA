%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales
	Program * program;

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
	Constant * constant;
	// Terminales.
	token token;
	double numberData;
	char * string;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD
%token <token> CREATE
%token <token> CHART 
%token <string> LABEL
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
%token <numberData> USERVALUE
%token <token> COMMA
%token <token> DATA
%token <token> XAXIS
%token <token> YAXIS
%token <token> VALUE
%token <token> SET
%token <token> WITH
%token <token> COLOR
%token <string> COLOROPTION
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
%type <expression> expression
%type <chart_type> chart_type
%type <chart_type_1> chart_type_1
%type <chart_type_2> chart_type_2
%type <number> number
%type <data> data
%type <value_list> value_list
%type <value> value
%type <add_datas> add_datas
%type <add_data> add_data
%type <set_axis> set_axis
%type <color> color

// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADDMATH SUBMATH
%left MULTMATH DIVMATH

// El símbolo inicial de la gramatica.
%start program

%%

program: expression	{ $$ = ProgramGrammarAction($1); }
;

expression: CREATE CHART chart_type { $$ = ExpressionGrammarAction($3); }
;

chart_type: chart_type_1 LABEL WHERE X data AND Y data color set_axis { $$ = ChartType1GrammarAction($1,$2,$5,$8,$9,$10); }
	| chart_type_2 LABEL add_datas { $$ = ChartType2GrammarAction($1,$2,$3); }
	;


chart_type_1: SCATTER { $$ = ScatterGrammarAction(); }
	| LINE { $$ = LineGrammarAction(); }
	;

chart_type_2: BAR { $$ = BarGrammarAction(); }
	| PIE { $$ = PieGrammarAction(); }
	;


number: USERVALUE { $$ = NumberGrammarAction($1); }
;

data: IS value_list { $$ = DataValueListGrammarAction($2); }
	;

value_list: CURLYOPEN value CURLYCLOSE { $$ = ValueListGrammarAction($2); };


value: USERVALUE COMMA value { $$ = UserValueCommaGrammarAction($1,$3); }
	| USERVALUE  { $$ = UserValueGrammarAction($1); }
	;

add_data: ADD DATA LABEL VALUE EQUALS number color { $$ = DataGrammarAction($3,$6,$7) ; }
;

add_datas: add_data add_datas{ $$ = AddDatasGrammarAction($1,$2); }
	| %empty { $$ = EmptyDatasGrammarAction(); }
	;


set_axis: SET XAXIS LABEL SET YAXIS LABEL { $$ = SetAxisGrammarAction($3,$6); }
	| %empty{ $$ = SetEmptyAxisGrammarAction(); }
	;

color: WITH COLOR COLOROPTION { $$ = ColorGrammarAction($3); }
	| %empty { $$ = EmptyColorGrammarAction(); }
	;


%%
