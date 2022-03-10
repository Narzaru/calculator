#ifndef SRC_MATH_PARSER_CALCULATOR_H_
#define SRC_MATH_PARSER_CALCULATOR_H_

#include <stdbool.h>

#include "lexeme.h"

lexemes_t *create_tokens_from_expression(char *expression);

#endif  /* SRC_MATH_PARSER_CALCULATOR_H_ */
