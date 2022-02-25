#ifndef SRC_STACK_TYPE_H_
#define SRC_STACK_TYPE_H_

#include <sys/types.h>

#ifndef STACK_VALUE_TYPE
#define STACK_VALUE_TYPE int
#endif  //!STACK_VALUE_TYPE


typedef enum statuses {
    OK = 0,
    ALLOC_ERROR = 1,
    REALLOC_ERROR = 2,
} status_t;

typedef struct stack {
    ssize_t top;
    ssize_t capacity;
    STACK_VALUE_TYPE *array;
} stack_t;

#endif  //!SRC_STACK_TYPE_H_