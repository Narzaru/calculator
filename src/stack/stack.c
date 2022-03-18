#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

#define STD_CAP 64

/**
 * @brief It try to realloc the stack
 * 
 * @param stack pointer to the stack pointer
 * @return status_t
 * @retval OK
 * @retval REALLOC_ERROR
 */
status_t extend_stack(stack_t **stack);


/**
 * @brief Check stack overflow for realloc
 * 
 * @param stack pointer to the stack
 * @return state
 * @retval true
 * @retval false
 */
bool is_full(stack_t *stack);

stack_t *create_stack() {
    stack_t *stack;

    stack = (stack_t *)calloc(sizeof(stack_t) + STD_CAP * sizeof(STACK_VALUE_TYPE), sizeof(char));

    if (stack != NULL) {
        stack->capacity = STD_CAP;
        stack->array = (STACK_VALUE_TYPE *)(stack + 1);
        stack->top = -1;
    }

    return stack;
}

void destroy_stack(stack_t **stack) {
    free(*stack);
    *stack = NULL;
}

bool is_empty(stack_t *stack) {
    bool state;
    if (stack->top < 0) {
        state = true;
    } else {
        state = false;
    }
    return state;
}

status_t push(stack_t **stack, STACK_VALUE_TYPE item) {
    status_t status;

    (*stack)->top += 1;
    (*stack)->array[(*stack)->top] = item;
    if (is_full((*stack))) {
        status = extend_stack(stack);
    } else {
        status = OK;
    }

    return status;
}

bool is_full(stack_t *stack) {
    bool state;
    if (stack->top >= stack->capacity - 1) {
        state = true;
    } else {
        state = false;
    }
    return state;
}

STACK_VALUE_TYPE pop(stack_t *stack) {
    return stack->array[stack->top--];
}

STACK_VALUE_TYPE peek(stack_t *stack) {
    return stack->array[(stack->top)];
}

status_t extend_stack(stack_t **stack) {
    status_t status;

    (*stack)->capacity *= 2;
    stack_t *temp = (stack_t *)realloc(*stack, sizeof(stack_t) + ((*stack)->capacity * sizeof(STACK_VALUE_TYPE)));

    if (temp == NULL) {
        fprintf(stderr, "allocation error");
        status = REALLOC_ERROR;
    } else {
        *stack = temp;
        (*stack)->array = (STACK_VALUE_TYPE *)(temp + 1);
        status = OK;
    }
    return status;
}
