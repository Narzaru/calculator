#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#include "lexeme.h"
#include "calculator.h"

void print(lexemes_t *ls);
void print_type(enum lexeme_type type);
void print_oper(enum operator_type oper);
void print_func(enum function_type func);
void print_num(double num);

int main(void) {
    // char a[] = "sin(3+5)*8-cos(sin(ln(15)*8)-6)";
    char a[] = "sin(3+5)*8-cos(sin(ln(15)*8)-6)";
    lexemes_t *tokens = create_tokens_from_expression(a);
    print(tokens);
    if (is_valid_tokens(tokens)) {
        lexemes_t *rpn = form_rpn(tokens);
        if (rpn != NULL) {
            lexeme_t res = calculate_rpn(rpn);
            print(rpn);
            printf("%.12g", res.value);
            destroy_lexemes_struct(&rpn);
        } else {
            printf("error in form_rpn");    
        }
    } else {
        printf("error in create_tokens_from_expression");
    }
    destroy_lexemes_struct(&tokens);
    return 0;
}

void print(lexemes_t *ls) {
    if (ls == NULL) {
        printf("NULL object\n");
    } else {
        printf("| ITER |     TYPE      |    OPER   |    FUNC   |     VALUE     |\n");
        printf("----------------------------------------------------------------\n");
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
    printf("\n");
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
        case type_operator: {
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
        case type_unary: {
            printf("   unary     ");
            break;
        }
        default: {
            printf("  BIG ERROR  ");
        }
    }
}

void print_oper(enum operator_type oper) {
    switch (oper) {
        case operator_not_operation: {
            printf("         ");
            break;
        }
        case operator_add: {
            printf("    +    ");
            break;
        }
        case operator_sub: {
            printf("    -    ");
            break;
        }
        case operator_mul: {
            printf("    *    ");
            break;
        }
        case operator_div: {
            printf("    /    ");
            break;
        }
        case operator_pow: {
            printf("    ^    ");
            break;
        }
        case operator_mod: {
            printf("    %%    ");
            break;
        }
        case operator_unary_add: {
            printf("    +    ");
            break;
        }
        case operator_unary_sub: {
            printf("    -    ");
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
        printf("     nan     ");
    } else {
        printf("%+.6e", num);
    }
}
