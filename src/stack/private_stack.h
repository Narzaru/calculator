#ifndef SRC_INTERNAL_STACK_H_
#define SRC_INTERNAL_STACK_H_

#include "stack_type.h"
#include "errors.h"

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

#endif  /* SRC_INTERNAL_STACK_H_ */
