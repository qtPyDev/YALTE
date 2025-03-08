#include "cmd.h"



void parse_cmd(struct token_struct tokens, char* text, GtkTextBuffer* buffer) {
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

    char* help =    "[ ed | open ]  >   edits the listed file.......\n"
                    "[ w  | save ]  >   writes the current file.....\n"
                    "[ help | h  ]  >   display help................\n";

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
    else if(strcmp(tokens.keyword, "help") == 0) {
        printf("help:\n\n%s", help);
    }
    else {
        printf("Invalid cmd '%s': Try using 'help'!\n", tokens.keyword);
    }
}


