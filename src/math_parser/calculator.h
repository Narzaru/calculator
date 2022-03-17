#ifndef SRC_MATH_PARSER_CALCULATOR_H_
#define SRC_MATH_PARSER_CALCULATOR_H_

#include "lexeme.h"

lexemes_t *create_tokens_from_expression(char *expression);
bool is_valid_tokens(lexemes_t *ls);
lexemes_t *form_rpn(lexemes_t *ls);
lexeme_t calculate_rpn(lexemes_t *ls);

#endif  /* SRC_MATH_PARSER_CALCULATOR_H_ */
