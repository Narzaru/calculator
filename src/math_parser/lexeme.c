#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "lexeme.h"

#define STD_CAP 64

lexemes_t *new_lexemes_struct(void) {
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

status_t push_lexem(lexemes_t **ls, lexeme_t l) {
    status_t status;
    if ((*ls)->count_lexemes >= (*ls)->capacity) {
        status = extend_lexemes_struct(ls);
    } else {
        status = OK;
    }
    if (status == OK) {
        (*ls)->all[(*ls)->count_lexemes] = l;
        (*ls)->count_lexemes++;
    }
    return status;
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

lexeme_t get_lexeme_at(lexemes_t *ls, long int at) {
    return ls->all[at];
}

bool is_incorrect_type(lexeme_t l) {
    bool is_incorrect;
    if (l.type == type_incorrect) {
        is_incorrect = true;
    } else {
        is_incorrect = false;
    }
    return is_incorrect;
}

bool is_number_type(lexeme_t l) {
    bool is_number;
    if (l.type == type_number) {
        is_number = true;
    } else {
        is_number = false;
    }
    return is_number;
}

bool is_open_bracket_type(lexeme_t l) {
    bool is_open_bracket;
    if (l.type == type_open_bracket) {
        is_open_bracket = true;
    } else {
        is_open_bracket = false;
    }
    return is_open_bracket;
}

bool is_function_type(lexeme_t l) {
    bool is_function;
    if (l.type == type_function) {
        is_function = true;
    } else {
        is_function = false;
    }
    return is_function;
}

bool is_delimiter_type(lexeme_t l) {
    bool is_delimiter;
    if (l.type == type_delimiter) {
        is_delimiter = true;
    } else {
        is_delimiter = false;
    }
    return is_delimiter;
}

bool is_operator_type(lexeme_t l) {
    bool is_operator;
    if (l.type == type_operator || l.type == type_unary) {
        is_operator = true;
    } else {
        is_operator = false;
    }
    return is_operator;
}

bool is_unary_type(lexeme_t l) {
    bool is_unary;
    if (l.type == type_unary) {
        is_unary = true;
    } else {
        is_unary = false;
    }
    return is_unary;
}

bool is_close_bracket_type(lexeme_t l) {
    bool is_close_bracket;
    if (l.type == type_close_bracket) {
        is_close_bracket = true;
    } else {
        is_close_bracket = false;
    }
    return is_close_bracket;
}

bool is_x_var_type(lexeme_t l) {
    bool is_var;
    if (l.type == type_x_var) {
        is_var = true;
    } else {
        is_var = false;
    }
    return is_var;
}
