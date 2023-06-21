#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Patrones terminales del lenguaje diseñado.

token LabelPatternAction(const char * lexeme,int length);



token CreatePatternAction(const char * lexeme);

token ChartPatternAction(const char * lexeme);

token WherePatternAction(const char * lexeme);



token ScatterPatternAction(const char * lexeme);

token BarPatternAction(const char * lexeme);

token PiePatternAction(const char * lexeme);

token LinePatternAction(const char * lexeme);



token XPatternAction(const char * lexeme);
token YPatternAction(const char * lexeme);
token AndPatternAction(const char * lexeme);



token InPatternAction(const char * lexeme);
token IsPatternAction(const char * lexeme);

token SubPatternAction(const char * lexeme);

token MultPatternAction(const char * lexeme);

token DivPatternAction(const char * lexeme);


token AddPatternAction(const char * lexeme);
token DataPatternAction(const char * lexeme);


token UserValuePatternAction(const char * lexeme,int length) ;

token CommaPatternAction(const char * lexeme);
token CurlyOpenPatternAction(const char * lexeme);

token CurlyClosePatternAction(const char * lexeme);


token SetPatternAction(const char * lexeme);

token WithPatternAction(const char * lexeme);


token ColorOptionPatternAction(const char * lexeme,int length);


token ColorPatternAction(const char * lexeme);


token OpenParenthesisPatternAction(const char * lexeme);


token CloseParenthesisPatternAction(const char * lexeme);

token OpenBracketPatternAction(const char * lexeme);

token CloseBracketPatternAction(const char * lexeme);

token UnknownPatternAction(const char * lexeme, const int length);

token XAxisPatternAction(const char * lexeme);

token YAxisPatternAction(const char * lexeme);

token StepSeparatorPatternAction(const char * lexeme);

token EqualsPatternAction(const char * lexeme);

token ValuePatternAction(const char * lexeme);

token AddMathPatternAction(const char * lexeme);

token SubMathPatternAction(const char * lexeme);

token MultMathPatternAction(const char * lexeme);

token DivMathPatternAction(const char * lexeme);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

#endif
