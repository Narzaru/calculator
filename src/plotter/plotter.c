#include <math.h>
#include <stdint.h>

#include "plotter.h"

/* like a private things */

#define UNUSED(expr) (void)(expr)

typedef struct {
    GtkDrawingArea *draw_area;
    GtkWindow *window;
    double *x;
    double *y;
    double range[2];
    double domain[2];
    uint64_t count_of_dots;
} plotter_t;

typedef struct {
    double box_left;
    double box_right;
    double box_top;
    double box_bot;
    double x_min;
    double x_max;
    double y_min;
    double y_max;
} packed_data_t;

static plotter_t plotter;

void draw_function(cairo_t *cr, packed_data_t *data);
void draw_box(cairo_t *cr, packed_data_t *data);
void draw_axes(cairo_t *cr, packed_data_t *data);
void draw_labels(cairo_t *cr, packed_data_t *data);

void cut_tops(double *y, unsigned count_of_dots, double y_min, double y_max) {
    for (unsigned i = 0; i < count_of_dots; ++i) {
        if (y[i] > y_max || y[i] < y_min) {
            y[i] = NAN;
        }
    }
}

double find_max(double *array, uint64_t array_length) {
    double max = array[0];
    uint64_t i = 0;

    while (i < array_length) {
        while ((i < (array_length)) && (isinf(array[i]) || isnan(array[i]))) {
            ++i;
        }
        if (i < array_length && array[i] > max) {
            max = array[i];
        }
        ++i;
    }
    return max;
}

double find_min(double *array, uint64_t array_length) {
    double min = array[0];
    uint64_t i = 0;

    while (i < array_length) {
        while ((i < (array_length)) && (isinf(array[i]) || isnan(array[i]))) {
            ++i;
        }
        if (i < array_length && array[i] < min) {
            min = array[i];
        }
        ++i;
    }
    return min;
}

void linspace(double *x, double x_start, double x_end, unsigned count_of_dots) {
    count_of_dots = count_of_dots - 1;
    double dx = (x_end - x_start) / count_of_dots;

    x[0] = x_start;
    for (unsigned i = 1; i < count_of_dots; ++i) {
        x[i] = x[i - 1] + dx;
    }

    x[count_of_dots] = x_end;
}

void plotter_init() {
    memset(&plotter, 0, sizeof(plotter_t));
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

void plotter_draw() {
    plotter.draw_area = GTK_DRAWING_AREA(gtk_drawing_area_new());
    plotter.window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));

    /* set minimum window size */
    gtk_widget_set_size_request(GTK_WIDGET(plotter.window), 640, 480);

    /* set window title */
    gtk_window_set_title(GTK_WINDOW(plotter.window), "plote");

    /* set default window size */
    gtk_window_set_default_size(GTK_WINDOW(plotter.window), 640, 480);

    /* add drawing area to window */
    gtk_container_add(GTK_CONTAINER(plotter.window), GTK_WIDGET(plotter.draw_area));

    /* connect the draw signal to the drawing area */
    g_signal_connect(GTK_DRAWING_AREA(plotter.draw_area), "draw", G_CALLBACK(on_draw_call), NULL);

    /* show all window parents */
    gtk_widget_show_all(GTK_WIDGET(plotter.window));
}

gboolean on_draw_call(GtkWidget *draw_area, cairo_t *cr, gpointer null) {
    UNUSED(null);
    int X = gtk_widget_get_allocated_width(draw_area);
    int Y = gtk_widget_get_allocated_height(draw_area);

    double box_left = 75;
    double box_right = X - 75;
    double box_top = 25;
    double box_bot = Y - 25;

    double xmin = plotter.range[0];
    double xmax = plotter.range[1];

    double ymin = plotter.domain[0];
    double ymax = plotter.domain[1];

    packed_data_t data = {
        box_left,
        box_right,
        box_top,
        box_bot,
        xmin,
        xmax,
        ymin,
        ymax
    };

    /* draw function */
    draw_function(cr, &data);

    /* draw box */
    draw_box(cr, &data);

    /* draw axes */
    draw_axes(cr, &data);

    /* draw labels */
    draw_labels(cr, &data);

    return TRUE;
}

void draw_function(cairo_t *cr, packed_data_t *data) {
    double x_stretching_koef = (data->box_right - data->box_left) / (data->x_max - data->x_min);
    double y_stretching_koef = (data->box_top - data->box_bot) / (data->y_max - data->y_min);

    double x_start = -x_stretching_koef * data->x_min + data->box_left;
    double y_start = -y_stretching_koef * data->y_min + data->box_bot;

    cut_tops(plotter.y, plotter.count_of_dots, data->y_min, data->y_max);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_move_to(
        cr,
        (plotter.x[0] * x_stretching_koef + x_start),
        (plotter.y[0] * y_stretching_koef + y_start));

    uint64_t i = 1;
    while (i < plotter.count_of_dots) {
        if (isnan(plotter.y[i]) || isinf(plotter.y[i])) {
            while (i < plotter.count_of_dots - 1 && (isnan(plotter.y[i]) || isinf(plotter.y[i]))) {
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
        ++i;
    }
    cairo_stroke(cr);
}

void draw_box(cairo_t *cr, packed_data_t *data) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1);
    cairo_move_to(cr, data->box_left, data->box_top);
    cairo_line_to(cr, data->box_right, data->box_top);
    cairo_line_to(cr, data->box_right, data->box_bot);
    cairo_line_to(cr, data->box_left, data->box_bot);
    cairo_line_to(cr, data->box_left, data->box_top);
    cairo_stroke(cr);
}

void draw_axes(cairo_t *cr, packed_data_t *data) {
    cairo_text_extents_t extents;

    cairo_set_source_rgb(cr, 128.0, 128.0, 0);
    cairo_select_font_face(cr, "Helvetica", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 24);
    cairo_text_extents(cr, "x", &extents);
    cairo_move_to(cr, data->box_right, data->box_bot);
    cairo_show_text(cr, "x");

    cairo_select_font_face(cr, "Helvetica", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 24);
    cairo_text_extents(cr, "y", &extents);
    cairo_move_to(cr, data->box_left + extents.height*0.8, data->box_top);
    cairo_save(cr);
    cairo_rotate(cr, -PI/2);
    cairo_show_text(cr, "y");
    cairo_restore(cr);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_set_line_width(cr, 1);
    for (int i = 1; i < 6; ++i) {
        cairo_move_to(cr, data->box_left, data->box_bot - i * (data->box_bot - data->box_top)/6);
        cairo_line_to(cr, data->box_right, data->box_bot - i * (data->box_bot - data->box_top)/6);
    }

    for (int i = 1; i < 6; ++i) {
        cairo_move_to(cr, data->box_left + (data->box_right - data->box_left)/6 * i, data->box_bot);
        cairo_line_to(cr, data->box_left + (data->box_right - data->box_left)/6 * i, data->box_top);
    }
    cairo_stroke(cr);
}

void draw_labels(cairo_t *cr, packed_data_t *data) {
    double dgrid_x = (data->x_max - data->x_min) / 6;
    double dgrid_y = (data->y_max - data->y_min) / 6;

    gchar str_num[32];
    cairo_text_extents_t extents;

    /* label axis x from below */
    cairo_set_source_rgb(cr, 128.0, 128.0, 0.0);
    cairo_select_font_face(cr, "Helvetica", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);
    for (int i = 0; i < 7; ++i) {
        g_snprintf(str_num, sizeof(str_num), "%.6g", data->x_min + dgrid_x * i);
        cairo_save(cr);
        cairo_text_extents(cr, str_num, &extents);
        cairo_move_to(
            cr,
            data->box_left + ((data->box_right - data->box_left) / 6 * i) - extents.height / 2,
            data->box_bot + extents.height + 1);
        cairo_show_text(cr, str_num);
        cairo_restore(cr);
    }

    /* label axis x from left */
    for (int i = 0; i < 7; ++i) {
        g_snprintf(str_num, sizeof(str_num), "%.6g", data->y_max - i * dgrid_y);
        cairo_save(cr);
        cairo_text_extents(cr, str_num, &extents);
        cairo_move_to(
            cr,
            data->box_left - extents.width * 1.1,
            data->box_top + (data->box_bot - data->box_top) / 6 * i + extents.height / 2);
        cairo_show_text(cr, str_num);
        cairo_restore(cr);
    }
    cairo_stroke(cr);
}
