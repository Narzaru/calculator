/************
 * INCLUDES *
 ************/
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "calculator.h"
#include "stack.h"

lexeme_t calc(stack_t *stack, lexeme_t operator);

lexeme_t calculate_rpn(lexemes_t *ls) {
    stack_t *stack = create_stack();
    lexeme_t l;

    for (int i = 0; i < ls->count_lexemes; ++i) {
        l = get_lexem_at(ls, i);
        if (is_number_type(l) || is_x_var_type(l)) {
            push(&stack, l);
        } else if (is_operator_type(l) || is_unary_type(l) || is_function_type(l)) {
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
