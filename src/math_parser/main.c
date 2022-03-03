#include <stdio.h>

#include "calculator.h"

int main(void) {
    char a[] = "privet, a kak dela ?";
    fix_expression(a);
    printf("%s", a);

    return 0;
}