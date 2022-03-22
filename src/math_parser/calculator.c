/************
 * INCLUDES *
 ************/
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "calculator.h"
#include "stack.h"

/************************
 * FUNCTION DECLARATION *
 ************************/
bool is_operand(lexeme_t l);

bool is_command(lexeme_t l);

lexeme_t calc(stack_t *stack, lexeme_t command);

/***************************
 * FUNCTION IMPLEMENTATION *
 ***************************/
lexeme_t calculate_rpn(lexemes_t *rpn, double *x_val) {
    stack_t *stack = create_stack();
    lexeme_t l;

    for (int i = 0; i < rpn->count_lexemes; ++i) {
        l = get_lexeme_at(rpn, i);
        if (is_operand(l)) {
            if (x_val != NULL && is_x_var_type(l)) {
                l.type = type_number;
                l.oper = operator_not_operation;
                l.func = function_not_function;
                l.value = *x_val;
            }
            push(&stack, l);
        } else if (is_command(l)) {
            push(&stack, calc(stack, l));
        }
    }

    l = pop(stack);
    destroy_stack(&stack);
    return l;
}

bool is_operand(lexeme_t l) {
    bool is_operand;
    if (is_number_type(l) || is_x_var_type(l)) {
        is_operand = true;
    } else {
        is_operand = false;
    }
    return is_operand;
}

bool is_command(lexeme_t l) {
    bool is_command;
    if (is_operator_type(l) || is_unary_type(l) || is_function_type(l)) {
        is_command = true;
    } else {
        is_command = false;
    }
    return is_command;
}

lexeme_t calc(stack_t *stack, lexeme_t command) {
    lexeme_t l1;
    lexeme_t l2;
    lexeme_t lo;

    if (command.oper == operator_add) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value + l1.value;
    } else if (command.oper == operator_sub) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value - l1.value;
    } else if (command.oper == operator_mul) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value * l1.value;
    } else if (command.oper == operator_div) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l2.value / l1.value;
    } else if (command.oper == operator_mod) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = fmod(l2.value, l1.value);
    } else if (command.oper == operator_pow) {
        l1 = pop(stack);
        l2 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = pow(l2.value, l1.value);
    } else if (command.oper == operator_unary_add) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = l1.value;
    } else if (command.oper == operator_unary_sub) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = 0 - l1.value;
    } else if (command.func == function_cos) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = cos(l1.value);
    } else if (command.func == function_sin) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = sin(l1.value);
    } else if (command.func == function_tan) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = tan(l1.value);
    } else if (command.func == function_acos) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = acos(l1.value);
    } else if (command.func == function_asin) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = asin(l1.value);
    } else if (command.func == function_atan) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = atan(l1.value);
    } else if (command.func == function_sqrt) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = sqrt(l1.value);
    } else if (command.func == function_ln) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = log(l1.value);
    } else if (command.func == function_log) {
        l1 = pop(stack);
        memcpy(&lo, &l1, sizeof(lexeme_t));
        lo.value = log10(l1.value);
    }

    return lo;
}
