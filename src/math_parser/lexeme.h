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
    type_incorrect,     /* on incorrect input */
    type_number,        /* number 0.5, 16, ... */
    type_open_bracket,  /* bracket ( */
    type_function,      /* function sin, cos */
    type_delimiter,     /* delimiter , not used*/
    type_operator,      /* opearation + - */
    type_unary,         /* unary operator */
    type_close_bracket, /* bracket ) */
    type_x_var          /* variable x */
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
lexemes_t *new_lexemes_struct(void);

void destroy_lexemes_struct(lexemes_t **ls);

void push_lexem(lexemes_t **ls, lexeme_t l);

status_t extend_lexemes_struct(lexemes_t **ls);

lexeme_t get_lexem_at(lexemes_t *ls, long int at);

bool is_number(lexeme_t *l);

bool is_function(lexeme_t *l);

bool is_open_bracket(lexeme_t *l);

bool is_close_bracket(lexeme_t *l);

bool is_operator(lexeme_t *l);

void to_unary(lexeme_t *l);

bool is_right_associative(lexeme_t *l);

int get_priority(enum operator_type oper);

bool is_unary(lexeme_t *l);

#endif  /* SRC_MATH_PARSER_LEXEME_H_ */
