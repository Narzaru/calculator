/*************
 * INCLUDEES *
 *************/
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "calculator.h"
#include "../stack/stack.h"

/***********
 * DEFINES *
 ***********/
// #define add 1
// #define sub 1
// #define mul 2
// #define div 2
// #define mod 2
// #define pow 3
// #define un_add 4
// #define un_sub 4

/************************
 * FUNCTION DECLARATION *
 ************************/

void to_unary(lexeme_t *l);

bool is_right_associative(lexeme_t *l);

int get_priority(enum operator_type oper);

lexeme_t calc(stack_t *stack, lexeme_t operator);

/***************************
 * FUNCTION IMPLEMENTATION *
 ***************************/
lexemes_t *form_rpn(lexemes_t *ls) {
    bool is_unary = true;
    lexemes_t *out_lexeme = new_lexemes_struct();
    stack_t *stack = create_stack();
    lexeme_t l;

    for (int i = 0; (out_lexeme != NULL) && (i < ls->count_lexemes); ++i) {
        l = get_lexem_at(ls, i);
        // if number
        if (is_number(&l)) {
            push_lexem(&out_lexeme, l);
            is_unary = false;
        // if function
        } else if (is_function(&l)) {
            push(&stack, l);
        // if open bracket
        } else if (is_open_bracket(&l)) {
            push(&stack, l);
            is_unary = true;
        // if close bracket
        } else if (is_close_bracket(&l)) {
            while (!is_empty(stack) && (peek(stack).type != type_open_bracket)) {
                push_lexem(&out_lexeme, pop(stack));
            }
            if (is_empty(stack)) {
                destroy_lexemes_struct(&out_lexeme);
            }
            pop(stack);
            is_unary = false;
        // if operator
        } else if (is_operator(&l)) {
            if (is_unary) {
                to_unary(&l);
            }
            while (
                !is_empty(stack)
                && (
                    (!is_right_associative(&l) && get_priority(peek(stack).oper) >= get_priority(l.oper))
                    || (is_right_associative(&l) && get_priority(peek(stack).oper) > get_priority(l.oper)))) {
                push_lexem(&out_lexeme, pop(stack));
            }
            push(&stack, l);
            is_unary = true;
        // else error or delimiter
        } else {
            destroy_lexemes_struct(&out_lexeme);
        }
    }

    while (!is_empty(stack) && out_lexeme != NULL) {
        l = pop(stack);
        if (!is_operator(&l) && !is_function(&l)) {
            destroy_lexemes_struct(&out_lexeme);
        }
        push_lexem(&out_lexeme, l);
    }

    destroy_stack(&stack);
    return out_lexeme;
}

void to_unary(lexeme_t *l) {
    if (l->type == type_operator) {
        if (l->oper == operator_add) {
            l->type = type_unary;
            l->oper = operator_unary_add;
        } else if (l->oper == operator_sub) {
            l->type = type_unary;
            l->oper = operator_unary_sub;
        }
    }
}

bool is_right_associative(lexeme_t *l) {
    bool is_right_associative;
    if (l->type == type_unary || l->oper == operator_pow) {
        is_right_associative = true;
    } else {
        is_right_associative = false;
    }
    return is_right_associative;
}

int get_priority(enum operator_type oper) {
    int priority;
    if (oper >= operator_add && oper <= operator_sub) {
        priority = 1;
    } else if (oper >= operator_mul && oper <= operator_mod) {
        priority = 2;
    } else if (oper == operator_pow) {
        priority = 3;
    } else if (oper >= operator_unary_add || oper <= operator_unary_sub) {
        priority = 4;
    } else {
        priority = -1;
    }
    return priority;
}

lexemes_t *simplify_rpn(lexemes_t *ls) {
    lexemes_t *out_lexeme = new_lexemes_struct();
    stack_t *stack = create_stack();
    lexeme_t l;

    int x_pos;

    for (int i = 0; (out_lexeme != NULL) && (i < ls->count_lexemes); ++i) {
        l = get_lexem_at(ls, i);
        if (is_number(&l)) {
            push(&stack, l);
        } else if (is_operator(&l) || is_function(&l)) {
            push(&stack, calc(stack, l));
        }
    }

    while (!is_empty(stack)) {
        push_lexem(&out_lexeme, pop(stack));
    }
    destroy_stack(&stack);
    return out_lexeme;
}

lexeme_t calc(stack_t *stack, lexeme_t operator) {
    lexeme_t l1;
    lexeme_t l2;
    lexeme_t lo;

    double num1;
    double num2;

    bool is_calulatable;

    if (operator.oper == operator_add) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            l2 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = l2.value + l1.value;
        } else {
            lo = operator;
        }
    } else if (operator.oper == operator_sub) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            l2 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = l2.value - l1.value;
        } else {
            lo = operator;
        }
    } else if (operator.oper == operator_mul) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            l2 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = l2.value * l1.value;
        } else {
            lo = operator;
        }
    } else if (operator.oper == operator_div) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            l2 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = l2.value / l1.value;
        } else {
            lo = operator;
        }
    } else if (operator.oper == operator_mod) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            l2 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = fmod(l2.value, l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.oper == operator_pow) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            l2 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = pow(l2.value, l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.oper == operator_unary_add) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = l1.value;
        } else {
            lo = operator;
        }
    } else if (operator.oper == operator_unary_sub) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = 0 - l1.value;
        } else {
            lo = operator;
        }
    } else if (operator.func == function_cos) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = cos(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_sin) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = sin(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_tan) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = tan(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_acos) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = acos(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_asin) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = asin(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_atan) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = atan(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_sqrt) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = sqrt(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_ln) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = log(l1.value);
        } else {
            lo = operator;
        }
    } else if (operator.func == function_log) {
        if (peek(stack).type != type_x_var) {
            l1 = pop(stack);
            memcpy(&lo, &l1, sizeof(lexeme_t));
            lo.value = log10(l1.value);
        } else {
            lo = operator;
        }
    }

    return lo;
}
