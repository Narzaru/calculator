#ifndef SRC_GTK_HELP_H_
#define SRC_GTK_HELP_H_

#include <gtk/gtk.h>

#define UNUSED(expr) (void)(expr)

GtkWidget* find_child(GtkWidget* parent, const gchar* name);

#endif  /* SRC_GTK_HELP_H_ */
