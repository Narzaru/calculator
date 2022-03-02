#include <gtk/gtk.h>
#include <math.h>
#include "plotter/plotter.h"

void on_botton_LOG_clicked(GtkButton *b, gpointer user_data);
void on_botton_LN_clicked(GtkButton *b, gpointer user_data);
void on_enter(GtkEntry *entry, gpointer  user_data);

double *x;
double *y;
int count_of_dots = 10000;

int main(int argc, char *argv[]) {
    x = calloc(sizeof(double), count_of_dots);
    y = calloc(sizeof(double), count_of_dots);

    g_print("%f", nan(""));

    GtkBuilder *builder;
    GtkWindow *window;

    /* init gtk */
    gtk_init(&argc, &argv);

    /* init plotter */
    // plotter_init();

    /* builder init */
    builder = gtk_builder_new_from_file("./ui/main_window.glade");

    /* get window object from the builder */
    window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

    /* connect gtk_main_quit on window close */
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* enable all signals from builder */
    gtk_builder_connect_signals(builder, NULL);

    /* show window */
    gtk_widget_show_all(GTK_WIDGET(window));

    /* give control to the gtk */
    gtk_main();
    free(x);
    free(y);

    return 0;
}

void on_botton_LOG_clicked(GtkButton *b, gpointer io_field) {
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "log()", 5, &cursor_position);
    g_print("%d\n", cursor_position);
    if (gtk_entry_get_text_length(io_field) != 255) {
        gtk_editable_set_position(io_field, cursor_position - 1);
    }
}

void on_botton_LN_clicked(GtkButton *b, gpointer io_field) {
    g_print("CALL BUTTON LN\n");

	double from_x = -3.14;
	double to_x = 3.14;

	double from_y = -3;
	double to_y = 3;

	linspace(x, from_x, to_x, count_of_dots);

	for(int i = 0; i < count_of_dots; ++i) { 
        y[i] = pow(cos(1-fabs(x[i])), -1) - 3.14;
    }

    plotter_set_function(x, y, count_of_dots);
	plotter_set_range(from_x, to_x);
    plotter_set_domain(from_y, to_y);

    plotter_draw();
}

void on_press_enter(GtkEntry *entry, gpointer user_data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    const gchar *str = gtk_entry_buffer_get_text(buffer);
    g_print("%s\n", str);
}
