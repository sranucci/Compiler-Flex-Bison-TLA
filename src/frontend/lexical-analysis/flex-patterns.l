%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x VALUELIST
%x INTERVALLIST

/* Patrones reutilizables. */
digit			[0-9]
float           [0-9]+(\.[0-9]+)?
endline			[\n]
whitespace		[ \f\n\r\t\v]

%%




"{"                                         { BEGIN(VALUELIST); return CurlyOpenPatternAction(yytext);}
{float}                                     { return UserValuePatternAction(yytext); }
","                                         { return CommaPatternActino(yytext); }
"}"                                         { BEGIN(INITIAL) return CurlyClosePatternAction(yytext);}




\"[a-zA-z ]+\"                              { return LabelPatternAction(yytext); }
"create"                                    { return CreatePatternAction(yytext); }
"chart"                                     { return ChartPatternAction(yytext); }
"where"                                     { return WherePatternAction(yytext); }

"scatter"                                   { return ScatterPatternAction(yytext); }
"bar"                                       { return BarPatternAction(yytext); }
"pie"                                       { return PiePatternAction(yytext); }
"line"                                      { return LinePatternAction(yytext); }

"x"                                         { return XPatternAction(yytext); }
"y"                                         { return YPatternAction(yytext); }
"and"                                       { return AndPatternAction(yytext); }

"in"                                        { return InPatternAction(yytext); }
"is"                                        { return IsPatternAction(yytext); }
"="                                         { return EqualPatternAction(yytext); }

"add"                                       { return AddPatternAction(yytext); }
"data"                                      { return DataPatternAction(yytext); }

"set"                                       { return SetPatternAction(yytext); }
"x-axis"                                    { return XAxisPatternAction(yytext); }
"y-axis"                                    { return YAxisPatternAction(yytext); }

"with"                                      { return WithPatternAction(yytext); }
"color"                                     { return ColorPatternAction(yytext); }
"red"|"blue"|"orange"|"yellow"|"black"      { return ColorOptionPatternAction(yytext); }

"+"											{ return AddPatternAction(yytext); }
"-"											{ return SubPatternAction(yytext); }
"*"											{ return MultPatternAction(yytext); }
"/"											{ return DivPatternAction(yytext); }
"="                                         { return EqualsPatternAction(yytext); }
"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }
"["                                         { return OpenBracketPatternAction(yytext); }
"]"                                         { return CloseBracketPatternAction(yytext); }
"value"                                     { return ValuePatternAction(yytext); }

									
{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%