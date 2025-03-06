#include "window.h"


int print_hello() {
    printf("Hello, World");
    return 0;
}

// , gpointer user_data
static void activate(GtkApplication* app) {
    GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), APP_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), APP_SIZE_X, APP_SIZE_Y);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    layout = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), layout);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_grid_attach(GTK_GRID(layout), button, 0, 0, 1, 1);

    gtk_widget_show_all(window);
}


int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("dev.qtpy.YALTE", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
