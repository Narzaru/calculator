#include "stdio.h"
#include "calculator.h"
#include "../stack/stack.h"

#define add 1
#define sub 1
#define mul 2
#define div 2
#define mod 2
#define pow 3



int get_priority(enum operation_type oper);

bool is_number(lexeme_t *lexeme);

bool is_operator(lexeme_t *lexeme);

bool is_open_bracket(lexeme_t *lexeme);

bool is_close_bracket(lexeme_t *lexeme);

bool is_function(lexeme_t *lexeme);

lexemes_t *form_postfix_notation(lexemes_t *lexemes) {
    lexemes_t *out_lexeme = new_lexemes_struct();
    stack_t *stack = create_stack();
    lexeme_t lexeme;

    for (int i = 0; (out_lexeme != NULL) && (i < lexemes->count_lexemes); ++i) {
        lexeme = get_lexem_at(lexemes, i);
        // if number
        if (is_number(&lexeme)) {
            push_lexem(&out_lexeme, lexeme);
        // if function
        } else if (is_function(&lexeme)) {
            push(&stack, lexeme);
        // if open bracket
        } else if (is_open_bracket(&lexeme)) {
            push(&stack, lexeme);
        // if close bracket
        } else if (is_close_bracket(&lexeme)) {
            while (!is_empty(stack) && (peek(stack).type != type_open_bracket)) {
                push_lexem(&out_lexeme, pop(stack));
            }
            if (is_empty(stack)) {
                destroy_lexemes_struct(&out_lexeme);
            }
            pop(stack);
        // if operator
        } else if (is_operator(&lexeme)) {
            while (
                !is_empty(stack)
                && ((peek(stack).type == type_function)
                || (get_priority(peek(stack).oper) >= get_priority(lexeme.oper)))) {
                push_lexem(&out_lexeme, pop(stack));
            }
            push(&stack, lexeme);
        // else error or delimiter
        } else {
            destroy_lexemes_struct(&out_lexeme);
        }
    }

    while (!is_empty(stack) && out_lexeme != NULL) {
        lexeme = pop(stack);
        printf("%d ", lexeme.type);
        if (!is_operator(&lexeme)) {
            destroy_lexemes_struct(&out_lexeme);
        }
        push_lexem(&out_lexeme, lexeme);
    }

    destroy_stack(&stack);
    return out_lexeme;
}

bool is_number(lexeme_t *lexeme) {
    bool is_number;
    if (lexeme->type == type_x_var || lexeme->type == type_number) {
        is_number = true;
    } else {
        is_number = false;
    }
    return is_number;
}

bool is_operator(lexeme_t *lexeme) {
    bool is_operator;
    if (lexeme->type == type_operation) {
        is_operator = true;
    } else {
        is_operator = false;
    }
    return is_operator;
}

bool is_open_bracket(lexeme_t *lexeme) {
    bool is_open_bracket;
    if (lexeme->type == type_open_bracket) {
        is_open_bracket = true;
    } else {
        is_open_bracket = false;
    }
    return is_open_bracket;
}

bool is_close_bracket(lexeme_t *lexeme) {
    bool is_close_bracket;
    if (lexeme->type == type_close_bracket) {
        is_close_bracket = true;
    } else {
        is_close_bracket = false;
    }
    return is_close_bracket;
}

bool is_function(lexeme_t *lexeme) {
    bool is_function;
    if (lexeme->type == type_function) {
        is_function = true;
    } else {
        is_function = false;
    }
    return is_function;
}

int get_priority(enum operation_type oper) {
    int priority;
    if (oper >= operation_add && oper <= operation_sub) {
        priority = 1;
    } else if (oper >= operation_mul && oper <= operation_mod) {
        priority = 2;
    } else if (oper == operation_pow) {
        priority = 3;
    } else {
        priority = -1;
    }
    return priority;
}
