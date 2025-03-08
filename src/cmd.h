#ifndef cmd_h
#define cmd_h


#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "fileio.h"


struct token_struct {
    char *keyword;
    char *identifier;
};


int parse_cmd(struct token_struct token, char* text, GtkTextBuffer* buffer);


#endif
