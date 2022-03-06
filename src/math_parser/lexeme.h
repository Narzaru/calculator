#ifndef SRC_MATH_PARSER_LEXEME_H_
#define SRC_MATH_PARSER_LEXEME_H_

/**************
 * BASE TYPES *
 **************/
enum lexeme_type {
    type_number,
    type_open_bracket,
    type_function,
    type_delimiter,
    type_operation,
    type_close_bracket
};

enum operation_type {
    operation_not_operation,
    operation_add,
    operation_sub,
    operation_mul,
    operation_pow,
    operation_mod,
    operation_unary
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

void push_lexem(lexemes_t *ls, lexeme_t l);

lexeme_t get_lexem_at(lexemes_t *ls, long int at);

#endif  /* SRC_MATH_PARSER_LEXEME_H_ */
