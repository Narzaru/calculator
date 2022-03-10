#include <stdlib.h>
#include <stdio.h>

#include "lexeme.h"

#define STD_CAP 128

lexemes_t *new_lexemes_struct(void) {
    /* alloc memory on lexemes_t and lexeme_t[STD_CAP]; */
    lexemes_t *new_object;
    new_object = (lexemes_t *)calloc(sizeof(lexemes_t) + sizeof(lexeme_t) * STD_CAP, sizeof(char));

    if (new_object != NULL) {
        new_object->capacity = STD_CAP;
        new_object->count_lexemes = 0;
        new_object->all = (lexeme_t *)(new_object + 1);
    }

    return new_object;
}

void destroy_lexemes_struct(lexemes_t **ls) {
    free(*ls);
    *ls = NULL;
}

void push_lexem(lexemes_t **ls, lexeme_t l) {
    if ((*ls)->count_lexemes >= (*ls)->capacity) {
        extend_lexemes_struct(ls);
    }
    (*ls)->all[(*ls)->count_lexemes] = l;
    (*ls)->count_lexemes++;
}

status_t extend_lexemes_struct(lexemes_t **ls) {
    status_t status;

    (*ls)->capacity *= 2;
    lexemes_t *temp = (lexemes_t *)realloc(*ls, sizeof(lexemes_t) + ((*ls)->capacity * sizeof(lexeme_t)));

    if (temp == NULL) {
        fprintf(stderr, "allocation error");
        status = REALLOC_ERROR;
    } else {
        *ls = temp;
        (*ls)->all = (lexeme_t *)(temp + 1);
        status = OK;
    }
    return status;
}

lexeme_t get_lexem_at(lexemes_t *ls, long int at) {
    return ls->all[at];
}
