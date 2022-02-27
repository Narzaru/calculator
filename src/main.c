#include <gtk/gtk.h>


void on_botton_LOG_clicked(GtkButton *b, gpointer user_data);
void on_botton_LN_clicked(GtkButton *b, gpointer user_data);
void on_enter(GtkEntry *entry, gpointer  user_data);

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // init gtk

    GtkTextView *io_field;
    GtkBuilder *builder;
    GtkWindow *window;
    GtkButton *button_ln;
    GtkButton *button_log;

    builder = gtk_builder_new_from_file("form.glade");

    window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, &io_field);

    gtk_window_set_focus_visible(GTK_WINDOW(window), FALSE);

    gtk_widget_show(GTK_WIDGET(window));
    gtk_main();
    return 0;
}

void on_botton_LOG_clicked(GtkButton *b, gpointer io_field) {
    gtk_widget_set_visible(io_field, FALSE);
}

void on_botton_LN_clicked(GtkButton *b, gpointer io_field) {
    gtk_widget_set_visible(io_field, TRUE);
}

void on_enter(GtkEntry *entry, gpointer  user_data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    gchar *str = gtk_entry_buffer_get_text(buffer);
    g_print("%s", str);
}
