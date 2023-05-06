#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */


//nuestras funciones

token LabelPatternAction(const char * lexeme){
	printf("label\n");
	yylval = LABEL;
	return LABEL;
}



token CreatePatternAction(const char * lexeme){
	printf("create\n");
	yylval.token = CREATE;
	return CREATE;
}
token ChartPatternAction(const char * lexeme){
	printf("chart\n");
	yylval.token = CHART;
	return CHART;
}
token WherePatternAction(const char * lexeme){
	printf("Where\n");
	yylval.token = WHERE;
	return WHERE;
}



token ScatterPatternAction(const char * lexeme){
	printf("Scatter\n");
	yylval.token = SCATTER;
	return SCATTER;
}
token BarPatternAction(const char * lexeme){
	printf("Bar\n");
	yylval.token = BAR;
	return BAR;
}
token PiePatternAction(const char * lexeme){
	printf("Pie\n");
	yylval.token = PIE;
	return PIE;
}
token LinePatternAction(const char * lexeme){
	printf("Line\n");
	yylval.token = LINE;
	return LINE;
}



token XPatternAction(const char * lexeme){
	printf("X\n");
	yylval.token = X;
	return X;
}
token YPatternAction(const char * lexeme){
	printf("Y\n");
	yylval.token = Y;
	return Y;
}
token AndPatternAction(const char * lexeme){
	printf("AND\n");
	yylval.token = AND;
	return AND;
}



token InPatternAction(const char * lexeme){
	printf("IN\n");
	yylval.token = IN;
	return IN;
}
token IsPatternAction(const char * lexeme){
	printf("Is");
	yylval.token = IS;
	return IS;
}
token EqualPatternAction(const char * lexeme){
	printf("Equal\n");
	yylval.token = EQUAL;
	return EQUAL;
}

token SubPatternAction(const char * lexeme){
	printf("SUB\n");
	yylval.token = SUB;
	return SUB;
}

token MultPatternAction(const char * lexeme){
	printf("MULT\n");
	yylval.token = MULT;
	return MULT;
}

token DivPatternAction(const char * lexeme){
	printf("DIV");
	yylval.token = DIV;
	return DIV;
}


token AddPatternAction(const char * lexeme){
	printf("ADD\n");
	yylval.token = ADD;
	return ADD;
}
token DataPatternAction(const char * lexeme){
	printf("DATA\n");
	yylval.token = DATA;
	return DATA;
}


token UserValuePatternAction(const char * lexeme) {
	printf("USERVALUE\n");
	yylval.token = USERVALUE;
	return USERVALUE;
}


token CommaPatternAction(const char * lexeme){
	printf("COMMA\n");
	yylval.token = COMMA;
	return COMMA;
}

token CurlyOpenPatternAction(const char * lexeme){
	printf("CURLYOPEN\n");
	yylval.token = CURLYOPEN;
	return CURLYOPEN;
}

token CurlyClosePatternAction(const char * lexeme){
	printf("CURLYCLOSE\n");
	yylval.token = CURLYCLOSE;
	return CURLYCLOSE;
}


token SetPatternAction(const char * lexeme){
	printf("SET\n");
	yylval.token = SET;
	return SET;
}

token WithPatternAction(const char * lexeme){
	printf("WITH\n");
	yylval.token = WITH;
	return WITH;
}


token ColorOptionPatternAction(const char * lexeme){
	printf("COLOROPTION\n");
	yylval.token = COLOROPTION;
	return COLOROPTION;
}


token ColorPatternAction(const char * lexeme){
	printf("COLOR\n");
	yylval.token = COLOR;
	return COLOR;
}


token OpenParenthesisPatternAction(const char * lexeme){
	printf("OPENPARENTHEISS\n");
	yylval.token = OPENPARENTHESIS;
	return OPENPARENTHESIS;
}


token CloseParenthesisPatternAction(const char * lexeme){
	printf("CLOSEPARENTHESIS\n");
	yylval.token = CLOSEPARENTHESIS;
	return CLOSEPARENTHESIS;
}


token OpenBracketPatternAction(const char * lexeme){
	printf("Open bracket\n");
	yylval.token = OPENBRACKET;
	return OPENBRACKET;
}

token CloseBracketPatternAction(const char * lexeme){
	printf("Close Bracket\n");
	yylval.token = CLOSEBRACKET;
	return CLOSEBRACKET;
}


token ValuePatternAction(const char * lexeme){
	printf("VALUE\n");
	yylval.token = VALUE;
	return VALUE;
}

token EqualsPatternAction(const char * lexeme){
	printf("EQUALS\n");
	yylval.token = EQUALS;
	return EQUALS;
}

token YAxisPatternAction(const char * lexeme){
	printf("YAXIS\n");
	yylval.token = YAXIS;
	return YAXIS;
}

token XAxisPatternAction(const char * lexeme){
	printf("XAXIS\n");
	yylval.token = XAXIS;
	return XAXIS;
}

token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}



void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}
