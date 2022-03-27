#ifndef SRC_MATH_PARSER_CALCULATOR_H_
#define SRC_MATH_PARSER_CALCULATOR_H_

#include "lexeme.h"

/***********
 * DEFINES *
 ***********/
#ifndef PI
#define PI 3.141592653589793238
#endif  /* PI */

#ifndef NAN
#define NAN 0.0 / 0.0
#endif  /* NAN */

#ifndef INF
#define INF 1.0 / 0.0
#endif  /* INF */

lexemes_t *form_tokens(char *expression);
bool is_valid_tokens(lexemes_t *ls);
lexemes_t *form_rpn(lexemes_t *ls);
lexeme_t calculate_rpn(lexemes_t *rpn, double *x_val);
bool is_valid_rpn(lexemes_t *ls);
status_t calculator(char *expression, char *x, double *result);
void to_locale_decimal_point(char *string);

#endif  /* SRC_MATH_PARSER_CALCULATOR_H_ */
