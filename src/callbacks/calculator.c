#include <math.h>
#include <gtk/gtk.h>
#include "calculator.h"
#include "gtk_help.h"
#include "simple_grapher/grapher.h"

void on_plote_window_close(GtkWidget *widget, gpointer main_window) {
    UNUSED(widget);
    gtk_widget_set_sensitive(GTK_WIDGET(main_window), TRUE);
}

void on_botton_plote_clicked(GtkButton *b, gpointer main_window) {
    UNUSED(b);
    /* builder init */
    GtkBuilder *builder;
    GtkWindow *window;

    builder = gtk_builder_new_from_file("./ui/plotter.ui");

    /* get window object from the builder */
    window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

    /* enable all signals from builder */
    gtk_builder_connect_signals(builder, NULL);

    /* disable main window */
    gtk_widget_set_sensitive(GTK_WIDGET(main_window), FALSE);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_plote_window_close), main_window);

    /* show window */
    gtk_widget_show_all(GTK_WIDGET(window));
}

void on_press_enter(GtkEntry *entry, gpointer entry_x) {
    char expression[256];
    char x_str[65];
    snprintf(expression, sizeof(expression), "%s", gtk_entry_get_text(entry));
    snprintf(x_str, sizeof(x_str), "%s",    gtk_entry_get_text(GTK_ENTRY(entry_x)));

    double result;
    if (calculator(expression, x_str, &result) != OK) {
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(entry), "error", 6);
    } else {
        g_snprintf(expression, sizeof(expression), "%g", result);
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(entry), expression, strlen(expression));
    }
}

void on_button_EQ_clicked(GtkButton *b, gpointer input_box) {
    UNUSED(b);
    on_press_enter(
        GTK_ENTRY(find_child(GTK_WIDGET(input_box), "id@gtk_entry_expression")),
        GTK_ENTRY(find_child(GTK_WIDGET(input_box), "id@gtk_entry_x")));
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
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "sqrt()", 6, &cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
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

void on_botton_SUB_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "-", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_ADD_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "+", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_MUL_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "*", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on_botton_DIV_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "/", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}
