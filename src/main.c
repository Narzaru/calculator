#include <gtk/gtk.h>
#include <math.h>
#include "simple_grapher/grapher.h"

double *x;
double *y;
int count_of_dots = 500000;

int main(int argc, char *argv[]) {
    x = calloc(sizeof(double), count_of_dots);
    y = calloc(sizeof(double), count_of_dots);

    GtkBuilder *builder;
    GtkWindow *window;

    gtk_init(&argc, &argv);

    plotter_init();

    builder = gtk_builder_new_from_file("./ui/main_window.ui");

    window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    free(x);
    free(y);

    return 0;
}
