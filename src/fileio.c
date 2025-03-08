#include "fileio.h"



void save_text_to_file(char* path, char* text) {
    FILE *fptr;
    // make this take a param from the UI popup
    fptr = fopen(path, "w");
    if(fptr == NULL) {
        perror("(aborted)");
        printf("%s", path);
        return;
    }
    fprintf(fptr, "%s", text);
    fclose(fptr);
}


char* read_text_from_file(char* path) {
    FILE *fptr;
    char file_text[10000];
    char* result;

    fptr = fopen(path, "r");
    if(fptr == NULL) {
        perror("(aborted)");
        printf("%s", path);
        return NULL;
    }

    fread(file_text, sizeof(int), sizeof(file_text), fptr);

    // Allocate memory for the result string and copy the contents
    result = malloc(strlen(file_text) + 1);
    if (result == NULL) {
        fclose(fptr);
        return NULL;
    }
    strcpy(result, file_text);

    fclose(fptr);
    return result;
}
