#ifndef SRC_MATH_PARSER_CALCULATOR_H_
#define SRC_MATH_PARSER_CALCULATOR_H_

#include "lexeme.h"

lexemes_t *create_tokens_from_expression(char *expression);
lexemes_t * form_postfix_notation(lexemes_t *lexemes);

#endif  /* SRC_MATH_PARSER_CALCULATOR_H_ */
