#ifndef SRC_PLOTTER_PLOTTER_H_
#define SRC_PLOTTER_PLOTTER_H_

#include <gtk/gtk.h>

void linspace(double *x, double x_start, double x_end, unsigned count_of_dots);

double func_max(double *x, unsigned count_of_dots);
double func_min(double *x, unsigned count_of_dots);

int real_to_screen_point(double *x, double stretching, double x_const);

/* called once in main body */
void plotter_init();
void plotter_set_function(double *x, double *y, unsigned count_of_dots);
void plotter_set_range(double x_min, double x_max);
void plotter_set_domain(double y_min, double y_max);

void plotter_draw();
gboolean on_draw_call(GtkWidget *widget, cairo_t *cr, gpointer data);
void drow_box(GtkWidget *draw_area, cairo_t *cr);

#endif //!SRC_PLOTTER_PLOTTER_H_
