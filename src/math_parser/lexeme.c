#include <stdlib.h>

#include "lexeme.h"
#include "lexeme_private.h"

lexemes_t *new_lexemes_struct(void) {
    lexemes_t *object = (lexemes_t *)calloc(sizeof(lexemes_t) + sizeof(lexeme_t) * 128, sizeof(char));
    if (object != NULL) {
        object->count_lexemes = 0;
        object->all = (lexeme_t *)(object + 1);
    }

    return object;
}

void destroy_lexemes_struct(lexemes_t **ls) {
    free(*ls);
    *ls = NULL;
}

void push_lexem(lexemes_t *ls, lexeme_t l) {
    ls->all[ls->count_lexemes] = l;
    ls->count_lexemes++;
}

lexeme_t get_lexem_at(lexemes_t *ls, long int at) {
    return ls->all[at];
}
