#include <stdbool.h>

#include "calculator.h"

void fix_expression(char *expression) {
    char* d = expression;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*expression++ = *d++);
}
