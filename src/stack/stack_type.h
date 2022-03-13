#ifndef SRC_STACK_TYPE_H_
#define SRC_STACK_TYPE_H_

#include <sys/types.h>
#include "lexeme.h"

#ifndef STACK_VALUE_TYPE
#define STACK_VALUE_TYPE lexeme_t
#endif  /* STACK_VALUE_TYPE */

typedef struct stack {
    ssize_t top;
    ssize_t capacity;
    STACK_VALUE_TYPE *array;
} stack_t;

#endif  /* SRC_STACK_TYPE_H_ */