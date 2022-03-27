/************
 * INCLUDES *
 ************/
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#include "calculator.h"
#include "lexeme.h"

/*******************************
 * STATIC CONSTANTS FOR PARSER *
 *******************************/
static const char short_delimiters[] = " ()+-*/^%";

/* in our example only one long delimiter */
static const char long_delimiters[] = "mod";

/* size for types */
#define TYPE_ROWS 11
#define TYPE_COLUMNS 16
/* offsets for function from start */
#define DELIM_POS 0
#define COS_POS 1
#define SIN_POS 2
#define TAN_POS 3
#define ACOS_POS 4
#define ASIN_POS 5
#define ATAN_POS 6
#define SQRT_POS 7
#define LN_POS 8
#define LOG_POS 9
/* functions and operators for parser */
static const char types[TYPE_ROWS][TYPE_COLUMNS] = {
    "()+-*/^%",
    "cos",
    "sin",
    "tan",
    "acos",
    "asin",
    "atan",
    "sqrt",
    "ln",
    "log",
    "ERROR" };

/************************
 * FUNCTION DECLARATION *
 ************************/
bool is_delimiter(char *string);

void construct_lexeme(lexeme_t *l, char *token);

enum lexeme_type get_lexeme_type(char *token);

bool is_token_a_number(char *token);

bool is_token_a_function(char *token);

enum operator_type get_lexeme_operation(enum lexeme_type type, char *token);

enum function_type get_lexeme_function(enum lexeme_type type, char *token);

double get_lexeme_value(enum lexeme_type type, char *token);

/*************
 * FUNCTIONS *
 *************/
lexemes_t *form_tokens(char *expression) {
    lexeme_t lexeme;
    lexemes_t *lexemes = new_lexemes_struct();

    char token[256];

    int i = 0;
    int j;
    while (expression[i] != '\0') {
        memset(token, 0, sizeof(token));
        j = 0;

        /* if delimiter '+ - * / ( and ...' */
        if (is_delimiter(&expression[i])) {
            /* if space - skip */
            if (expression[i] == ' ') {
                ++i;
                continue;
            /* if 'mod==%' opearion */
            } else if (expression[i] == 'm') {
                token[0] = '%';
                i += 3;
            /* if any delimiter */
            } else {
                token[0] = expression[i];
                ++i;
            }
        /* else number function or trash */
        } else {
            while (!is_delimiter(&expression[i])) {
                token[j] = expression[i];
                ++i;
                ++j;
            }
        }
        /* parse token into lexeme_t type */
        construct_lexeme(&lexeme, token);
        /* push lexeme at top of lexemes */
        push_lexem(&lexemes, lexeme);
    }

    return lexemes;
}

bool is_delimiter(char *string) {
    bool is_delimiter;
    if (strchr(short_delimiters, *string) != NULL) {
        is_delimiter = true;
    } else if (strstr(string, long_delimiters) == string) {
        is_delimiter = true;
    } else {
        is_delimiter = false;
    }

    return is_delimiter;
}

void construct_lexeme(lexeme_t *l, char *token) {
    l->type = get_lexeme_type(token);
    l->oper = get_lexeme_operation(l->type, token);
    l->func = get_lexeme_function(l->type, token);
    l->value = get_lexeme_value(l->type, token);
}

enum lexeme_type get_lexeme_type(char *token) {
    enum lexeme_type token_type = type_incorrect;
    char *p_char;

    if (strlen(token) == 1 && token[0] == 'x') {
        token_type = type_x_var;
    /* if number */
    } else if (is_token_a_number(token)) {
        token_type = type_number;
    /* if operator or bracket or operation */
    } else if ((p_char = strstr(types[DELIM_POS], token)) != NULL) {
        if (*p_char == '(') {
            token_type = type_open_bracket;
        } else if (*p_char == ')') {
            token_type = type_close_bracket;
        } else {
            token_type = type_operator;
        }
    /* if function */
    } else if (is_token_a_function(token)) {
        token_type = type_function;
    /* else incorrect */
    } else {
        token_type = type_incorrect;
    }

    return token_type;
}

bool is_token_a_number(char *token) {
    bool is_number = true;
    for (int i = 0; token[i] != '\0'; ++i) {
        if ((token[i] > '9' || token[i] < '0') && token[i] != '.' && token[i] != ',' && token[i]) {
            is_number = false;
        }
    }
    return is_number;
}

bool is_token_a_function(char *token) {
    bool is_function = false;
    for (int i = 1; i < TYPE_ROWS; ++i) {
        if (strstr(types[i], token) == types[i] && strlen(token) == strlen(types[i])) {
            is_function = true;
        }
    }
    return is_function;
}

enum operator_type get_lexeme_operation(enum lexeme_type type, char *token) {
    enum operator_type operation;
    if (type == type_operator) {
        switch (*token) {
          case '+': {
            operation = operator_add;
            break;
          }
          case '-': {
            operation = operator_sub;
            break;
          }
          case '*': {
            operation = operator_mul;
            break;
          }
          case '/': {
            operation = operator_div;
            break;
          }
          case '^': {
            operation = operator_pow;
            break;
          }
          case '%': {
            operation = operator_mod;
            break;
          }
          default: {
            operation = operator_not_operation;
          }
        }
    } else {
        operation = operator_not_operation;
    }
    return operation;
}

enum function_type get_lexeme_function(enum lexeme_type type, char *token) {
    enum function_type function;
    char *p_pos;

    if (type == type_function) {
        int i;

        for (i = 1; i < TYPE_ROWS; ++i) {
            p_pos = strstr(token, types[i]);
            if (p_pos != NULL && p_pos == token) {
                break;
            }
        }

        switch (i) {
          case COS_POS: {
            function = function_cos;
            break;
          }
          case SIN_POS: {
            function = function_sin;
            break;
          }
          case TAN_POS: {
            function = function_tan;
            break;
          }
          case ACOS_POS: {
            function = function_acos;
            break;
          }
          case ASIN_POS: {
            function = function_asin;
            break;
          }
          case ATAN_POS: {
            function = function_atan;
            break;
          }
          case SQRT_POS: {
            function = function_sqrt;
            break;
          }
          case LN_POS: {
            function = function_ln;
            break;
          }
          case LOG_POS: {
            function = function_log;
            break;
          }
          default: {
            function = function_not_function;
          }
        }
    } else {
        function = function_not_function;
    }
    return function;
}

double get_lexeme_value(enum lexeme_type type, char *token) {
    double result;
    if (type == type_number) {
        char *p_char;
        char *dot_pos = strchr(token, '.');
        if (dot_pos != NULL) {
            *dot_pos = ',';
        }
        result = strtod(token, &p_char);
        /* if all string is converted */
        if (p_char != NULL) {
            if (result == HUGE_VAL || result == -HUGE_VAL) {
                result = NAN;
            }
        } else {
            result = NAN;
        }
    } else {
        result = NAN;
    }

    return result;
}

