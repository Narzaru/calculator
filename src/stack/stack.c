#include <stdlib.h>

#include "stack.h"
#include "private_stack.h"

#define STD_CAP 64

stack_t *create_stack() {
    stack_t *stack;
    void *mem;

    mem = calloc(sizeof(stack_t) + STD_CAP * sizeof(STACK_VALUE_TYPE), sizeof(char));
    stack = (stack_t *)mem;

    if (stack != NULL) {
        stack->capacity = STD_CAP;
        stack->array = (STACK_VALUE_TYPE *)(mem + sizeof(stack_t));
        stack->top = -1;  /*-1 mean empty stack */
    }

    return stack;
}

void destroy_stack(stack_t **stack) {
    free(*stack);
    *stack = NULL;
}

status_t extend_stack(stack_t **stack) {
    status_t status;

    (*stack)->capacity *= 2;
    void *mem = realloc(*stack, sizeof(stack_t) + ((*stack)->capacity * sizeof(STACK_VALUE_TYPE)));

    if (mem == NULL) {
        (*stack)->top = -1;
        status = REALLOC_ERROR;
    } else {
        (*stack) = mem;
        (*stack)->array = (STACK_VALUE_TYPE *)(mem + sizeof(stack_t));
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

STACK_VALUE_TYPE pop(stack_t *stack) {
    return stack->array[stack->top--];
}

STACK_VALUE_TYPE peek(stack_t *stack) {
    return stack->array[(stack->top - 1)];
}
