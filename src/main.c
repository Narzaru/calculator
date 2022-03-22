#include <gtk/gtk.h>
#include <math.h>
#include "plotter/plotter.h"

double *x;
double *y;
int count_of_dots = 500000;

int main(int argc, char *argv[]) {
    x = calloc(sizeof(double), count_of_dots);
    y = calloc(sizeof(double), count_of_dots);

    GtkBuilder *builder;
    GtkWindow *window;

    /* init gtk */
    gtk_init(&argc, &argv);

    /* init plotter */
    plotter_init();

    /* builder init */
    builder = gtk_builder_new_from_file("./ui/main_window.ui");

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
