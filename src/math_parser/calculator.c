#include <assert.h>
#include "stdio.h"
#include "calculator.h"
#include "../stack/stack.h"

#define add 1
#define sub 1
#define mul 2
#define div 2
#define mod 2
#define pow 3

int get_priority(enum operation_type oper) {
    int priority;
    if (oper >= operation_add && oper <= operation_sub) {
        priority = 1;
    } else if (oper >= operation_mul && oper <= mod) {
        priority = 2;
    } else if (oper == mod) {
        priority = 3;
    } else {
        priority = -1;
    }
    return priority;
}

bool is_first_priority_higher(enum operation_type first, enum operation_type second) {
    return get_priority(first) >= get_priority(second);
}

lexemes_t *form_postfix_notation(lexemes_t *ls) {
    lexemes_t *out = new_lexemes_struct();
    stack_t *stack = create_stack();
    lexeme_t l;
    for (int i = 0; i < ls->count_lexemes; ++i) {
        l = get_lexem_at(ls, i);
        switch (l.type) {
            // if number
            case type_number:
                push_lexem(&out, l);
                break;
            // if function or open bracket
            case type_function:
            case type_open_bracket:
                push(&stack, l);
                break;
            // if operator
            case type_operation:
                while (!is_empty(stack) && get_priority(peek(stack).oper) >= get_priority(l.oper)) {
                    push_lexem(&out, pop(stack));
                }
                push(&stack, l);
                break;
            case type_close_bracket:
                while (!is_empty(stack) && peek(stack).type != type_open_bracket && peek(stack).type == type_operation ) {
                    push_lexem(&out, pop(stack));
                }
                if (is_empty(stack) && peek(stack).type == type_open_bracket) {
                    assert(0);
                } else if (peek(stack).type == type_open_bracket) {
                    pop(stack);
                } else if (peek(stack).type == type_function) {
                    push_lexem(&out, pop(stack));
                }
                break;
            default:
                assert(0);
        }
    }
    while (!is_empty(stack) && peek(stack).type == type_operation) {
        push_lexem(&out, pop(stack));
    }
    destroy_stack(&stack);
    return out;
}
