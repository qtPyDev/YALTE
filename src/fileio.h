#ifndef fileio_h
#define fileio_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void save_text_to_file(char* path, char* text);
char* read_text_from_file(char* path);


#endif
