#include "cmd.h"



int parse_cmd(struct token_struct tokens, char* text, GtkTextBuffer* buffer) {
    char *delimiter = " ";
    int count = 0;
    char* token;

    token = strtok(text, delimiter);
    tokens.keyword = token;

    while(token != NULL && count < 2) {
        token = strtok(NULL, delimiter);
        if(count == 0) {
            tokens.identifier = token;
        }
        count++;
    }

    if(strcmp(tokens.keyword, "ed") == 0 || strcmp(tokens.keyword, "open") == 0) {
        char* file_text = read_text_from_file(tokens.identifier);
        if (file_text != NULL) {
            gtk_text_buffer_set_text(buffer, file_text, -1);
            free(file_text);
        }
    }
    else if(strcmp(tokens.keyword, "w") == 0 || strcmp(tokens.keyword, "save") == 0) {
        GtkTextIter start, end;
        char *text;

        gtk_text_buffer_get_bounds(buffer, &start, &end);
        text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

        save_text_to_file(tokens.identifier, text);
    }
    else if(strcmp(tokens.keyword, "theme") == 0) {
        GtkCssProvider *provider = gtk_css_provider_new ();
        GFile *css_file = g_file_new_for_path(tokens.identifier);

        gtk_css_provider_load_from_file(provider, css_file, NULL);
        gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_USER
        );
    }
    else if(strcmp(tokens.keyword, "quit") == 0) {
        printf("gracefully shutting down YALTE...");
        return 1;
    }
    else {
        printf("Invalid cmd '%s': Try using 'help'!\n", tokens.keyword);
    }

    return 0;
}


