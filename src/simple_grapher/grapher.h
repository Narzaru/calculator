#ifndef SRC_SIMPLE_GRAPHER_GRAPHER_H_
#define SRC_SIMPLE_GRAPHER_GRAPHER_H_

/************
 * INCLUDES *
 ************/
#include <gtk/gtk.h>

/***********
 * DEFINES *
 ***********/
#ifndef PI
#define PI 3.141592653589793238
#endif  /* PI */

#ifndef NAN
#define NAN 0.0 / 0.0
#endif  /* NAN */

#ifndef INF
#define INF 1.0 / 0.0
#endif  /* INF */

/************************
 * FUNCTION DECLARATION *
 ************************/
void linspace(double *x, double x_start, double x_end, unsigned count_of_dots);

void plotter_init();

void plotter_set_function(double *x, double *y, unsigned count_of_dots);

void plotter_set_range(double x_min, double x_max);

void plotter_set_domain(double y_min, double y_max);

void plotter_signal_connect_on_close(void (*on_close)(GtkWidget *widget, gpointer pointer), gpointer data);

void plotter_draw();

gboolean on_draw_call(GtkWidget *widget, cairo_t *cr, gpointer data);

#endif /* SRC_SIMPLE_GRAPHER_GRAPHER_H_ */
