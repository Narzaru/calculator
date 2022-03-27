#include <math.h>
#include <gtk/gtk.h>
#include "gtk_help.h"
#include "calculator.h"
#include "simple_grapher/grapher.h"

#define repace_dot(str) { \
    for (size_t i = 0; i < strlen(str); ++i) { \
        if (str[i] == '.') { \
            str[i] = ','; \
        } \
    } \
}

extern double *x;
extern double *y;
extern int count_of_dots;

void on_plotter_window_close(GtkWidget *widget, gpointer main_window) {
    UNUSED(widget);
    gtk_widget_set_sensitive(GTK_WIDGET(main_window), TRUE);
    gtk_widget_show(main_window);
}

void on_plote_graph(GtkButton *b, GtkGrid *plotter_window) {
    UNUSED(b);
    double x_max;
    double x_min;
    double y_max;
    double y_min;
    char *endptr;
    GtkWidget *widget;
    char str[256];

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_xmin");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    repace_dot(str);
    x_min = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_xmax");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    repace_dot(str);
    x_max = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_ymin");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    repace_dot(str);
    y_min = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_ymax");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    repace_dot(str);
    y_max = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_entry");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));

    lexemes_t *tokens = form_tokens(str);
    lexemes_t *rpn;

    if (is_valid_tokens(tokens) && x_max > x_min && y_max > x_min) {
        rpn = form_rpn(tokens);
        if (rpn != NULL) {
            if (is_valid_rpn(rpn)) {
                linspace(x, x_min, x_max, count_of_dots);
                for (int i = 0; i < count_of_dots; ++i) {
                    y[i] = calculate_rpn(rpn, &(x[i])).value;
                }
                destroy_lexemes_struct(&rpn);

                plotter_set_domain(y_min, y_max);
                plotter_set_range(x_min, x_max);
                plotter_set_function(x, y, count_of_dots);
                gtk_widget_set_sensitive(GTK_WIDGET(plotter_window), FALSE);
                gtk_widget_hide(GTK_WIDGET(plotter_window));
                plotter_draw();
                plotter_signal_connect_on_close(on_plotter_window_close, (gpointer)plotter_window);
            } else {
                destroy_lexemes_struct(&rpn);
                gtk_entry_set_text(GTK_ENTRY(widget), "error");
            }
        } else {
            gtk_entry_set_text(GTK_ENTRY(widget), "error");
        }
    } else {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
    }
    destroy_lexemes_struct(&tokens);
}
