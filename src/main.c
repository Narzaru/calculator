#include <stdio.h>

#include "stack/stack.h"

int main(void) {
    stack_t *stack = create_stack();

    for (int i = 0; i < 512; ++i) {
        double item = i*1.0;
        push(&stack, item);
    }

    while(!is_empty(stack)) {
        printf("%d ", pop(stack));
    }

    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);

    destroy_stack(&stack);
}
