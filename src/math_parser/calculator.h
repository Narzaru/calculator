#ifndef SRC_MATH_PARSER_CALCULATOR_H_
#define SRC_MATH_PARSER_CALCULATOR_H_

#include "lexeme.h"

lexemes_t *form_tokens(char *expression);
bool is_valid_tokens(lexemes_t *ls);
lexemes_t *form_rpn(lexemes_t *ls);
lexeme_t calculate_rpn(lexemes_t *rpn, double *x_val);
status_t calculator(char *expression, double *result);

#endif  /* SRC_MATH_PARSER_CALCULATOR_H_ */
