#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#include "lexeme.h"
#include "calculator.h"

void print(lexemes_t *ls);
void print_type(enum lexeme_type type);
void print_oper(enum operation_type oper);
void print_func(enum function_type func);
void print_num(double num);

int main(void) {
    char a[] = "85.5 + 8 + .5 * cos(sin(3.3))";
    lexemes_t *ls = create_tokens_from_expression(a);
    print(ls);
    lexemes_t *ls_out = form_postfix_notation(ls);
    print(ls_out);
    destroy_lexemes_struct(&ls);
    destroy_lexemes_struct(&ls_out);
    return 0;
}

void print(lexemes_t *ls) {
    printf("| ITER |     TYPE      |    OPER   |    FUNC   |     VALUE    |\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < ls->count_lexemes; ++i) {
        printf("| %-4d | ", i);
        print_type(get_lexem_at(ls, i).type);
        printf(" | ");
        print_oper(get_lexem_at(ls, i).oper);
        printf(" | ");
        print_func(get_lexem_at(ls, i).func);
        printf(" | ");
        print_num(get_lexem_at(ls, i).value);
        printf(" |");
        printf("\n");
    }
}

void print_type(enum lexeme_type type) {
    switch (type) {
        case type_incorrect: {
            printf("  incorrect  ");
            break;
        }
        case type_number: {
            printf("   number    ");
            break;
        }
        case type_open_bracket: {
            printf("open bracket ");
            break;
        }
        case type_function: {
            printf("  function   ");
            break;
        }
        case type_delimiter: {
            printf("  BIG ERROR  ");
            break;
        }
        case type_operation: {
            printf("  operation  ");
            break;
        }
        case type_close_bracket: {
            printf("close bracket");
            break;
        }
        case type_x_var: {
            printf("      x      ");
            break;
        }
        default: {
            printf("  BIG ERROR  ");
        }
    }
}

void print_oper(enum operation_type oper) {
    switch (oper) {
        case operation_not_operation: {
            printf("         ");
            break;
        }
        case operation_add: {
            printf("    +    ");
            break;
        }
        case operation_sub: {
            printf("    -    ");
            break;
        }
        case operation_mul: {
            printf("    *    ");
            break;
        }
        case operation_div: {
            printf("    /    ");
            break;
        }
        case operation_pow: {
            printf("    ^    ");
            break;
        }
        case operation_mod: {
            printf("    %    ");
            break;
        }
        default: {
            printf("BIG ERROR");
            break;
        }
    }
}

void print_func(enum function_type func) {
    switch (func) {
        case function_not_function: {
            printf("         ");
            break;
        }
        case function_cos: {
            printf("   cos   ");
            break;
        }
        case function_sin: {
            printf("   sin   ");
            break;
        }
        case function_tan: {
            printf("   tan   ");
            break;
        }
        case function_acos: {
            printf("   acos  ");
            break;
        }
        case function_asin: {
            printf("   asin  ");
            break;
        }
        case function_atan: {
            printf("   atan  ");
            break;
        }
        case function_sqrt: {
            printf("   sqrt  ");
            break;
        }
        case function_ln: {
            printf("   ln    ");
            break;
        }
        case function_log: {
            printf("   log   ");
            break;
        }
        default: {
            printf("BIG ERROR");
            break;
        }
    }
}

void print_num(double num) {
    if (isnan(num)) {
        printf("     nan    ");
    } else {
        printf("%.6e", num);
    }
}
