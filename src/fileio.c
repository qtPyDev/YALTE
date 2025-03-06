#include "fileio.h"



void save_text_to_file(char* text) {
    FILE *fptr;
    // make this take a param from the UI popup
    fptr = fopen("hello_world.c", "w");
    fprintf(fptr, "%s", text);
    fclose(fptr);
}


void load_text_from_file() {
    // make this take a param from the UI popup
    // FILE *fptr;
    // fptr = fopen("hello_world.c", "r");

    // if(fptr == NULL) {
    //     printf("Not able to open the file.");
    // };

    // char* file_text;

    // fgets(file_text, sizeof(file_text), fptr);
    // printf("%s", file_text);
}
