#include <math.h>
#include <gtk/gtk.h>
#include "calculator.h"
#include "plotter.h"

#define UNUSED(expr) (void)(expr)

void on_botton_plote_clicked(GtkButton *b, gpointer io_field) {
    UNUSED(b);
    /* builder init */
    GtkBuilder *builder;
    GtkWindow *window;

    builder = gtk_builder_new_from_file("./ui/plotter.ui");

    /* get window object from the builder */
    window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

    /* enable all signals from builder */
    gtk_builder_connect_signals(builder, NULL);

    /* show window */
    gtk_widget_show_all(GTK_WIDGET(window));
}

GtkWidget* find_child(GtkWidget* parent, const gchar* name) {
    if (g_strcmp0(gtk_widget_get_name(parent), name) == 0)
        return parent;

    GList* children = NULL;
    if (GTK_IS_CONTAINER(parent))
        children = gtk_container_get_children(GTK_CONTAINER(parent));

    while (children != NULL) {
        GtkWidget* widget = find_child(children->data, name);

        if (widget != NULL)
            return widget;

        children = children->next;
    }

    return NULL;
}

extern double *x;
extern double *y;
extern int count_of_dots;

void on_plote_graph(GtkButton *b, GtkGrid *grid) {
    UNUSED(b);
    double x_max;
    double x_min;
    double y_max;
    double y_min;
    char *endptr;
    GtkWidget *widget;
    char str[256];

    widget = find_child(grid, "id@gtk_xmin");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    x_min = strtod(str, &endptr);
    g_print("%s %p %p %d\n", str, str, endptr, *endptr);
    if (endptr == str || *endptr != NULL) {
        gtk_entry_set_text(widget, "error");
        return;
    }

    widget = find_child(grid, "id@gtk_xmax");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    x_max = strtod(str, &endptr);
    if (endptr == str || *endptr != NULL) {
        gtk_entry_set_text(widget, "error");
        return;
    }

    widget = find_child(grid, "id@gtk_ymin");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    y_min = strtod(str, &endptr);
    if (endptr == str || *endptr != NULL) {
        gtk_entry_set_text(widget, "error");
        return;
    }

    widget = find_child(grid, "id@gtk_ymax");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    y_max = strtod(str, &endptr);
    if (endptr == str || *endptr != NULL) {
        gtk_entry_set_text(widget, "error");
        return;
    }

    widget = find_child(grid, "id@gtk_entry");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));


    lexemes_t *rpn;
    lexemes_t *tokens = form_tokens(str);

    if (is_valid_tokens(tokens) && x_max > x_min && y_max > x_min) {
        rpn = form_rpn(tokens);
        if (rpn != NULL) {
            linspace(x, x_min, x_max, count_of_dots);
            for (int i = 0; i < count_of_dots; ++i) {
                y[i] = calculate_rpn(rpn, &(x[i])).value;
            }
            destroy_lexemes_struct(&rpn);

            plotter_set_domain(y_min, y_max);
            plotter_set_range(x_min, x_max);
            plotter_set_function(x, y, count_of_dots);
            plotter_draw();
        } else {
            gtk_entry_set_text(widget, "error");
        }
    } else {
        gtk_entry_set_text(widget, "error");
    }
    destroy_lexemes_struct(&tokens);
}

void on_press_enter(GtkEntry *entry, gpointer null) {
    UNUSED(null);

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    const gchar *str = gtk_entry_buffer_get_text(buffer);

    char strout[256];

    if (str != NULL) {
        g_snprintf(strout, sizeof(str), "%s", str);
        lexemes_t *tokens = form_tokens(strout);

        if (is_valid_tokens(tokens)) {
            lexemes_t *rpn = form_rpn(tokens);
            if (rpn != NULL) {
                lexeme_t res = calculate_rpn(rpn, NULL);
                g_snprintf(strout, sizeof(strout), "%-f", res.value);
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
