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
bool is_valid_tokens(lexemes_t *ls) {
    lexeme_t l;
    lexeme_t pl;
    int brackets_dif = 0;
    bool is_correct;
    bool has_incorrect_chunk;
    for (int i = 0; i < ls->count_lexemes; ++i) {
        l = get_lexem_at(ls, i);
        if (is_open_bracket(&l)) {
            brackets_dif++;
        } else if (is_close_bracket(&l)) {
            brackets_dif--;
        } else if (l.type == type_incorrect) {
            has_incorrect_chunk = false;
        }
    }

    if (brackets_dif == 0) {
        is_correct = true;
        pl = get_lexem_at(ls, 0);
        for (int i = 1; i < ls->count_lexemes && is_correct == true; ++i) {
            l = get_lexem_at(ls, i);
            if (is_operator(&pl) && (!is_number(&l) && !is_function(&l) && !is_open_bracket(&l)) && !is_operator(&l)) {
                is_correct = false;
            }
            pl = l;
        }
    } else {
        is_correct = false;
    }

    return is_correct & !has_incorrect_chunk;
}

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
            is_unary = false;
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
            if (!is_empty(stack) && peek(stack).type == type_function) {
                push_lexem(&out_lexeme, pop(stack));
            }
            is_unary = false;
        // if operator
        } else if (is_operator(&l)) {
            if (is_unary) {
                to_unary(&l);
            }
            while (
                !is_empty(stack)
                && peek(stack).type == type_operator
                && ((!is_right_associative(&l) && get_priority(peek(stack).oper) >= get_priority(l.oper))
                    || (is_right_associative(&l) && get_priority(peek(stack).oper) > get_priority(l.oper))
                    )) {
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

lexeme_t calculate_rpn(lexemes_t *ls) {
    stack_t *stack = create_stack();
    lexeme_t l;

    for (int i = 0; i < ls->count_lexemes; ++i) {
        l = get_lexem_at(ls, i);
        if (is_number(&l)) {
            push(&stack, l);
        } else if (is_operator(&l) || is_function(&l)) {
            push(&stack, calc(stack, l));
        }
    }

    l = pop(stack);
    destroy_stack(&stack);
    return l;
}

lexeme_t calc(stack_t *stack, lexeme_t operator) {
    lexeme_t l1;
    lexeme_t l2;
    lexeme_t lo;

    if (operator.oper == operator_add) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value + l1.value;
    } else if (operator.oper == operator_sub) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value - l1.value;
    } else if (operator.oper == operator_mul) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value * l1.value;
    } else if (operator.oper == operator_div) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value / l1.value;
    } else if (operator.oper == operator_mod) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = fmod(l2.value, l1.value);
    } else if (operator.oper == operator_pow) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = pow(l2.value, l1.value);
    } else if (operator.oper == operator_unary_add) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l1.value;
    } else if (operator.oper == operator_unary_sub) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = 0 - l1.value;
    } else if (operator.func == function_cos) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = cos(l1.value);
    } else if (operator.func == function_sin) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = sin(l1.value);
    } else if (operator.func == function_tan) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = tan(l1.value);
    } else if (operator.func == function_acos) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = acos(l1.value);
    } else if (operator.func == function_asin) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = asin(l1.value);
    } else if (operator.func == function_atan) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = atan(l1.value);
    } else if (operator.func == function_sqrt) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = sqrt(l1.value);
    } else if (operator.func == function_ln) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = log(l1.value);
    } else if (operator.func == function_log) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = log10(l1.value);
    }

    return lo;
}
