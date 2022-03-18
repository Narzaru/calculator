#include <math.h>
#include <gtk/gtk.h>
#include "calculator.h"

#define UNUSED(expr) (void)(expr)

void on_press_enter(GtkEntry *entry, gpointer null) {
    UNUSED(null);

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    const gchar *str = gtk_entry_buffer_get_text(buffer);
   
    char strout[255];

    if (str != NULL) {
        strcpy(strout, str);
        lexemes_t *tokens = form_tokens(strout);

        if (is_valid_tokens(tokens)) {
            lexemes_t *rpn = form_rpn(tokens);
            if (rpn != NULL) {
                lexeme_t res = calculate_rpn(rpn);
                g_snprintf(strout, 255, "%-f", res.value);
                gtk_entry_buffer_set_text(buffer, strout, strlen(strout));
                destroy_lexemes_struct(&rpn);
            } else {
                gtk_entry_buffer_set_text(buffer, "error", 6);
            }
        } else {
            gtk_entry_buffer_set_text(buffer, "error", 6);
        }
        destroy_lexemes_struct(&tokens);
    }
}

void on_button_EQ_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    on_press_enter(io_field, NULL);
}

void on_botton_LOG_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "log()", 5, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_LN_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "ln()", 4, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_TAN_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "tan()", 5, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_ATAN_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "atan()", 6, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_SIN_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "sin()", 5, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_ASIN_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "asin()", 6, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_COS_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "cos()", 5, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_ACOS_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "acos()", 6, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_BRACKET_OPEN_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "(", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_BRACKET_CLOSE_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), ")", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_SQRT_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "^", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_MOD_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "mod()", 5, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_CLS_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gtk_editable_delete_text(
        GTK_EDITABLE(io_field),
        0,
        gtk_entry_get_max_length(GTK_ENTRY(io_field)));
}

void on_botton_DEL_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gtk_editable_delete_text(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) - 1,
        gtk_editable_get_position(GTK_EDITABLE(io_field)));
}

void on_botton_0_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "0", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_1_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "1", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_2_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "2", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_3_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "3", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_4_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "4", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_5_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "5", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_6_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "6", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_7_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "7", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_8_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "8", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_9_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "9", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_DOT_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), ".", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_SUB_clicked (GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "-", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_ADD_clicked (GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "+", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_MUL_clicked (GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "*", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_DIV_clicked (GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "/", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}
