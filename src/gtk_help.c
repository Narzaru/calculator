#include "gtk_help.h"

GtkWidget* find_child(GtkWidget* parent, const gchar* name) {
    if (strcmp(gtk_widget_get_name(parent), name) == 0)
        return parent;

    GList* children = NULL;
    if (GTK_IS_CONTAINER(parent))
        children = gtk_container_get_children(GTK_CONTAINER(parent));

    while (children != NULL) {
        GtkWidget* widget = find_child(GTK_WIDGET(children->data), name);

        if (widget != NULL)
            return widget;

        children = children->next;
    }

    return NULL;
}