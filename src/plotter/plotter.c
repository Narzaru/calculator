#include <math.h>

#include "plotter.h"

#ifndef PI
#define PI 3.141592653589793238
#endif  //!PI

#ifndef NAN
#define NAN 0.0 / 0.0
#endif  //!NAN

#ifndef INF
#define INF 1.0 / 0.0
#endif  //!INF

typedef struct {
	GtkWidget *drow_area;           /* plot area */
    GtkWindow *window;              /* plotting window */
	double *x;                      /* array of x */
	double *y;                      /* array of y */
    double range[2];                /* all x`s values */
    double domain[2];               /* all y`s values */
	unsigned int count_of_dots;     /* length of arrays */
} plotter_t;

static plotter_t plotter;


void linspace(double *x, double x_start, double x_end, unsigned count_of_dots) {
    count_of_dots = count_of_dots - 1;
    double dx = (x_end - x_start) / count_of_dots;

    x[0] = x_start;
    for (unsigned i = 1; i < count_of_dots; ++i) {
        x[i] = x[i - 1] + dx;
    }

    x[count_of_dots] = x_end;
}

void slice_peak(double *y, unsigned count_of_dots, double y_min, double y_max) {
    for (unsigned i = 0; i < count_of_dots; ++i) {
        if (y[i] > y_max || y[i] < y_min) {
            y[i] = NAN;
        }
    }
}


double func_max(double *array, unsigned array_length) {
    double max = array[0];
    for (unsigned i = 1; i < array_length; ++i) {
        if (isinf(array[i])) {
            array[i] = nan(NULL);
        } else if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}


double func_min(double *x, unsigned count_of_dots) {
    double min = x[0];
    for (unsigned i = 1; i < count_of_dots; ++i) {
        if (x[i] < min) {
            min = x[i];
        }
    }
    return min;
}


/* code description with define */
#define _MATH_ROUND(x) (int)(x + 0.5)
int real_to_screen_point(double *x, double stretching, double x_const) {
    return _MATH_ROUND(*x * stretching + x_const);
}
#undef _MATH_ROUND


void plotter_init() {
    plotter.drow_area = NULL;
    plotter.window = NULL;
}


void plotter_set_function(double *x, double *y, unsigned count_of_dots) {
    plotter.x = x;
    plotter.y = y;
    plotter.count_of_dots = count_of_dots;
}


void plotter_set_range(double x_min, double x_max) {
    plotter.range[0] = x_min;
    plotter.range[1] = x_max;
}


void plotter_set_domain(double y_min, double y_max) {
    plotter.domain[0] = y_min;
    plotter.domain[1] = y_max;
}


void plotter_draw(){
    if (plotter.window != NULL) {
        gtk_window_close(plotter.window);
        plotter.window = NULL;
    }

    plotter.drow_area = gtk_drawing_area_new();
    plotter.window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_widget_set_size_request(GTK_WIDGET(plotter.window), 640, 480);

    gtk_window_set_title(GTK_WINDOW(plotter.window), "plote");
	gtk_window_set_default_size(GTK_WINDOW(plotter.window), 640, 480);

	gtk_container_add(GTK_CONTAINER(plotter.window), plotter.drow_area);
	g_signal_connect(GTK_DRAWING_AREA(plotter.drow_area), "draw", G_CALLBACK(on_draw_call), NULL);

	gtk_widget_show_all(GTK_WIDGET(plotter.window));
}

gboolean on_draw_call(GtkWidget *draw_area, cairo_t *cr, gpointer data) {
	int X = gtk_widget_get_allocated_width(draw_area);
	int Y = gtk_widget_get_allocated_height(draw_area);

	int Xleft = 0.1*X, Xright = 0.9*X;
	int Ytop = 0.1*Y, Ybot = 0.9*Y;

	double yminGlobal = func_min(plotter.y, plotter.count_of_dots);
	double ymaxGlobal = func_max(plotter.y, plotter.count_of_dots);

	double xmin = func_min(plotter.x, plotter.count_of_dots);
	double xmax = func_max(plotter.x, plotter.count_of_dots);

    double ymin = -3;
    double ymax = 0;


    double x_stretching_koef = (Xright - Xleft) / (xmax - xmin);
    double y_stretching_koef = (Ytop - Ybot) / (ymax - ymin);
    double x_start = -x_stretching_koef*xmin + Xleft;
    double y_start = -y_stretching_koef*ymin + Ybot;

    slice_peak(plotter.y, plotter.count_of_dots, ymin, ymax);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1);
    cairo_move_to(
        cr,
        (plotter.x[0] * x_stretching_koef + x_start),
        (plotter.y[0] * y_stretching_koef + y_start));

    for(unsigned i = 0; i < plotter.count_of_dots; ++i) {
        if (isnan(plotter.y[i]) || isinf(plotter.y[i])) {
            while (i  < plotter.count_of_dots - 1 && (isnan(plotter.y[i]) || isinf(plotter.y[i]))) {
                    i++;
            }
            cairo_move_to(
                cr,
                (plotter.x[i] * x_stretching_koef + x_start),
                (plotter.y[i] * y_stretching_koef + y_start));
        }
        cairo_line_to(
            cr,
            (plotter.x[i] * x_stretching_koef + x_start),
            (plotter.y[i] * y_stretching_koef + y_start));
    }
    cairo_stroke(cr);

    if (1) {
        /* box */
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 1);
        cairo_move_to(cr, Xleft, Ytop); 	// Top border
        cairo_line_to(cr, Xright, Ytop);	// Right border
        cairo_line_to(cr, Xright, Ybot); // Bottom border
        cairo_line_to(cr, Xleft, Ybot);	// Left border
        cairo_line_to(cr, Xleft, Ytop);
        cairo_stroke(cr);

        /* axises */
        gchar str_num[32];
        cairo_text_extents_t extents;

        cairo_set_source_rgb(cr, 128.0, 128.0, 0);
        cairo_select_font_face(cr, "Helvetica", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 24);
        cairo_text_extents(cr, "x", &extents);
        cairo_move_to(cr, Xright, Ybot);
        cairo_show_text(cr, "x");
        cairo_stroke(cr);

        cairo_select_font_face(cr, "Helvetica", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 24);
        cairo_text_extents(cr, "y", &extents);
        cairo_move_to(cr, Xleft + extents.height*0.8, Ytop);
        cairo_save(cr);
        cairo_rotate(cr, -PI/2);
        cairo_show_text(cr, "y");
        cairo_stroke(cr);
        cairo_restore(cr);

        double dgrid_x = (xmax - xmin) / 6;
        double dgrid_y = (ymax - ymin) / 6;

        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_set_line_width(cr, 1);
        for (int i = 1; i < 6; ++i) {
            cairo_move_to(cr, Xleft, Ybot - i * (Ybot - Ytop)/6);
            cairo_line_to(cr, Xright, Ybot - i * (Ybot - Ytop)/6);
        }

        for (int i = 1; i < 6; ++i) {
            cairo_move_to(cr, Xleft + (Xright - Xleft)/6 * i, Ybot);
            cairo_line_to(cr, Xleft + (Xright - Xleft)/6 * i, Ytop);
        }
        cairo_stroke(cr);

        /* values x */
        cairo_set_source_rgb(cr, 128.0,128.0, 0.0);
        cairo_select_font_face(cr, "Helvetica", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 12.0);
        for (int i = 0; i < 7; ++i) {
            g_snprintf(str_num, 32, "%.2g", dgrid_x * i);
            cairo_save(cr);
            cairo_text_extents(cr, str_num, &extents);
            cairo_move_to(cr, Xleft + ((Xright - Xleft) / 6 * i) - extents.height / 2, ((double)Ybot) + extents.height + 1);
            cairo_show_text(cr, str_num);
            cairo_restore(cr);
        }

        /* values y */
        for (int i = 0; i < 7; ++i) {
            g_snprintf(str_num, 32, "%.2g", ymax - i * dgrid_y);
            cairo_save(cr);
            cairo_text_extents(cr, str_num, &extents);
            cairo_move_to(cr, Xleft-extents.width*1.1, Ytop + (Ybot - Ytop) / 6 * i + extents.height / 2);
            cairo_show_text(cr, str_num);
            cairo_restore(cr);
        }
        cairo_stroke(cr);
    }

    return TRUE;
}

void drow_box(GtkWidget *draw_area, cairo_t *cr) {
    
}