#ifndef SRC_MATH_PARSER_LEXEME_H_
#define SRC_MATH_PARSER_LEXEME_H_

/************
 * INCLUDES *
 ************/
#include <stdbool.h>
#include "errors.h"

/**************
 * BASE TYPES *
 **************/
enum lexeme_type {
    type_incorrect,
    type_number,
    type_open_bracket,
    type_function,
    type_delimiter,
    type_operator,
    type_unary,
    type_close_bracket,
    type_x_var
};

enum operator_type {
    operator_not_operation,
    operator_add,
    operator_sub,
    operator_mul,
    operator_div,
    operator_mod,
    operator_pow,
    operator_unary_add,
    operator_unary_sub
};

enum function_type {
    function_not_function,
    function_cos,
    function_sin,
    function_tan,
    function_acos,
    function_asin,
    function_atan,
    function_sqrt,
    function_ln,
    function_log
};

struct lexeme {
    enum lexeme_type type;
    enum operator_type oper;
    enum function_type func;
    double value;
};

struct lexemes {
    struct lexeme *all;
    long int count_lexemes;
    long int capacity;
};


/***********
 * DEFINES *
 ***********/
typedef struct lexeme lexeme_t;
typedef struct lexemes lexemes_t;


/************************
 * FUNCTION DECLARATION *
 ************************/

/* functions for working with lexemes_t type */
lexemes_t *new_lexemes_struct(void);

void destroy_lexemes_struct(lexemes_t **ls);

status_t push_lexem(lexemes_t **ls, lexeme_t l);

status_t extend_lexemes_struct(lexemes_t **ls);

lexeme_t get_lexeme_at(lexemes_t *ls, long int at);

/* functions for type validation */
bool is_incorrect_type(lexeme_t l);

bool is_number_type(lexeme_t l);

bool is_open_bracket_type(lexeme_t l);

bool is_function_type(lexeme_t l);

bool is_delimiter_type(lexeme_t l);

bool is_operator_type(lexeme_t l);

bool is_unary_type(lexeme_t l);

bool is_close_bracket_type(lexeme_t l);

bool is_x_var_type(lexeme_t l);

#endif  /* SRC_MATH_PARSER_LEXEME_H_ */
