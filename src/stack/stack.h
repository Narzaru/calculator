#ifndef SRC_STACK_STACK_H_
#define SRC_STACK_STACK_H_

#include <sys/types.h>
#include <stdbool.h>

#include "stack_type.h"
#include "errors.h"

stack_t *create_stack();

void destroy_stack(stack_t **stack);

bool is_empty(stack_t *stack);

status_t push(stack_t **stack, STACK_VALUE_TYPE item);

STACK_VALUE_TYPE pop(stack_t *stack);

STACK_VALUE_TYPE peek(stack_t *stack);

#endif  /* SRC_STACK_STACK_H_ */
