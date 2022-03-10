#ifndef SRC_MATH_PARSER_LEXEME_H_
#define SRC_MATH_PARSER_LEXEME_H_

/************
 * INCLUDES *
 ************/
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
    type_operation,     /* opearation + - */
    type_close_bracket, /* bracket ) */
    type_x_var          /* variable x */
};

enum operation_type {
    operation_not_operation,
    operation_add,
    operation_sub,
    operation_mul,
    operation_div,
    operation_pow,
    operation_mod
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
    enum operation_type oper;
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

#endif  /* SRC_MATH_PARSER_LEXEME_H_ */
