#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <sys/types.h>
#include <stdbool.h>

#include "stack_type.h"
#include "errors.h"

/**
 * @brief Create a stack object
 * 
 * @return stack_t *
 * @retval NULL
 */
stack_t *create_stack();


/**
 * @brief Destroy the stack object.
 * After it destroy, the object is NULL
 * 
 * @param stack - pointer to the stack pointer.
 */
void destroy_stack(stack_t **stack);


/**
 * @brief Check if stack is empty
 * 
 * @param stack 
 * @return state of the stack
 * @retval true
 * @retval false
 */
bool is_empty(stack_t *stack);


/**
 * @brief Push item to the stack
 * 
 * @param stack pointer to the stack pointer
 * @param item data to will push in the stack
 * @return status_t
 * @retval OK
 * @retval REALLOC_ERROR
 */
status_t push(stack_t **stack, STACK_VALUE_TYPE item);


/**
 * @brief Pop item from the stack top.
 * 
 * @param stack stack pointer
 * @return item
 */
STACK_VALUE_TYPE pop(stack_t *stack);


/**
 * @brief Peek item from the stack top.
 * 
 * @param stack stack pointer
 * @return item
 */
STACK_VALUE_TYPE peek(stack_t *stack);

#endif  /* SRC_STACK_H_ */
