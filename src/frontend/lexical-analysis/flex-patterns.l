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
float           \-?[0-9]+(\.[0-9]+)?
endline			[\n]
whitespace		[ \f\n\r\t\v]

%%




"{"                                         {  return CurlyOpenPatternAction(yytext);}
{float}                                     { return UserValuePatternAction(yytext,yyleng); }
","                                         { return CommaPatternAction(yytext); }
"}"                                         {  return CurlyClosePatternAction(yytext);}




\"[a-zA-z ]+\"                              { return LabelPatternAction(yytext,yyleng); }
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

"is"                                        { return IsPatternAction(yytext); }
"add"                                       { return AddPatternAction(yytext); }
"data"                                      { return DataPatternAction(yytext); }

"set"                                       { return SetPatternAction(yytext); }
"x-axis"                                    { return XAxisPatternAction(yytext); }
"y-axis"                                    { return YAxisPatternAction(yytext); }

"with"                                      { return WithPatternAction(yytext); }
"color"                                     { return ColorPatternAction(yytext); }
"red"|"blue"|"orange"|"yellow"|"black"|"green"      { return ColorOptionPatternAction(yytext,yyleng); }


"value"                                     { return ValuePatternAction(yytext); }



"="                                         { return EqualsPatternAction(yytext); }


                                    
{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%