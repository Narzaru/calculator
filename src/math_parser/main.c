#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "lexeme.h"
#include "calculator.h"

int main(void) {
    lexemes_t *lexemes = new_lexemes_struct();

    lexeme_t lexeme;
    
    lexeme.func = -1;
    lexeme.oper = -1;
    lexeme.type = -1;
    lexeme.value = 0.0;

    for (int i = 0; i < 128; ++i) {
        push_lexem(lexemes, lexeme);
    }

    destroy_lexemes_struct(&lexemes);

    return 0;
}
