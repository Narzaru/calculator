#ifndef SRC_MATH_PARSER_LEXEME_H_
#define SRC_MATH_PARSER_LEXEME_H_

enum lexeme_type {
    number,
    open_bracket,
    function,
    delimiter,
    operation,
    close_bracket
};

enum operation_type {
    not_operation,
    add,
    sub,
    mul,
    pow,
    mod,
    unary
};

enum function_type {
    not_function,
    cos,
    sin,
    tan,
    acos,
    asin,
    atan,
    sqrt,
    ln,
    log
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

typedef struct lexeme lexeme_t;
typedef struct lexemes lexemes_t;

lexemes_t *new_lexemes_struct(void);

void destroy_lexemes_struct(lexemes_t **ls);

void push_lexem(lexemes_t *ls, lexeme_t l);

void get_lexem_at(lexemes_t *ls, long int at);

#endif  /* SRC_MATH_PARSER_LEXEME_H_ */
