#include "window.h"



void save_file(GtkWidget* _button, GtkWidget* text_view) {
    (void)_button;

    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(
        GTK_TEXT_VIEW(text_view));
    gchar *text;

    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    printf("%s", text);

    save_text_to_file(text);
}


GtkWidget* create_text_view() {
    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(
        GTK_TEXT_VIEW(text_view));

    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);

    gtk_text_buffer_set_text(buffer, "Hello, this is some text", -1);

    gtk_text_view_set_wrap_mode(
        GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);

    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_view), 10);

    // gtk_text_buffer_create_tag(buffer, "gap",
    //     "pixels_above_lines", 30, NULL);

    // gtk_text_buffer_create_tag(buffer, "lmarg",
    //     "left_margin", 5, NULL);

    // gtk_text_buffer_create_tag(buffer, "gray_bg",
    //     "background", "gray", NULL);
    // gtk_text_buffer_create_tag(buffer, "italic",
    //     "style", PANGO_STYLE_ITALIC, NULL);
    // gtk_text_buffer_create_tag(buffer, "bold",
    //     "weight", PANGO_WEIGHT_BOLD, NULL);

    // gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    // gtk_text_buffer_insert(buffer, &iter, "Plain text\n", -1);
    // gtk_text_buffer_insert_with_tags_by_name(buffer, &iter,
    //     "Colored Text\n", -1, "blue_fg", "lmarg",  NULL);
    // gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
    //     "Text with colored background\n", -1, "lmarg", "gray_bg", NULL);

    // gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
    //     "Text in italics\n", -1, "italic", "lmarg",  NULL);

    // gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
    //     "Bold text\n", -1, "bold", "lmarg",  NULL);

    return text_view;
}

// , gpointer user_data
static void activate(GtkApplication* app) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), APP_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), APP_SIZE_X, APP_SIZE_Y);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkCssProvider *provider = gtk_css_provider_new ();
    printf("%s", CSS);
    GFile *css_file = g_file_new_for_path(CSS);
    gtk_css_provider_load_from_file(provider, css_file, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    GtkWidget *layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *layout_menubar = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(layout_menubar), 5);
    gtk_grid_set_column_spacing(GTK_GRID(layout_menubar), 5);
    gtk_widget_set_size_request(layout_menubar, 10,10);

    GtkWidget *layout_main = gtk_grid_new();

    GtkWidget *layout_bottom = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(layout_bottom), 5);
    gtk_grid_set_column_spacing(GTK_GRID(layout_bottom), 5);
    // gtk_widget_set_size_request(layout_bottom, 10,10);

    gtk_container_add(GTK_CONTAINER(window), layout);

    // text view stuff
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);

    gtk_widget_set_hexpand(scrolled_window, TRUE);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(layout_main), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(layout_main), TRUE);

     GtkWidget *text_view = create_text_view();

    gtk_container_add(
        GTK_CONTAINER(scrolled_window), text_view);

    gtk_grid_attach(GTK_GRID(layout_main), scrolled_window, 0, 1, 2, 2);

    GtkWidget *btn_save = gtk_button_new_with_label("save");
    g_signal_connect(btn_save, "clicked", G_CALLBACK(
        save_file), text_view);

    gtk_widget_set_size_request(btn_save, 100, 50);
    gtk_grid_attach(GTK_GRID(layout_menubar), btn_save, 0, 0, 1, 1);

    GtkWidget *btn_quit = gtk_button_new_with_label("quit");
    g_signal_connect_swapped(btn_quit, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_widget_set_size_request(btn_quit, 100, 50);
    gtk_grid_attach(GTK_GRID(layout_menubar), btn_quit, 1, 0, 1, 1);

    GtkWidget *file_info = gtk_label_new(
        "   C           | ch: 0 |       | ln: 1     col: 1      "
    );
    gtk_widget_set_halign(file_info, GTK_ALIGN_START);

    GtkWidget *cmdline = gtk_entry_new();
    gtk_widget_set_size_request(cmdline, APP_SIZE_X/2, -1);
    gtk_widget_set_halign(cmdline, GTK_ALIGN_END);
    gtk_widget_set_hexpand(cmdline, TRUE);

    gtk_grid_attach(GTK_GRID(layout_bottom), file_info, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(layout_bottom), cmdline, 1, 0, 1, 1);

    gtk_box_pack_start(GTK_BOX(layout), layout_menubar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(layout), layout_main, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(layout), layout_bottom, FALSE, FALSE, 0);

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
