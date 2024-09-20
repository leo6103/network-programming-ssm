#include <string.h>
#include <stdlib.h>
#include "utils.h"

ParsedStrings parseStrings(const char* str, const char *delim) {
    char **result;
    ParsedStrings p;

    int size = 1;
    for (const char *s = str; *s; s++) {
        if (strchr(delim, *s)) size++;
    }

    result = malloc(size * sizeof(char*));
    if (result == NULL) {
        p.size = 0;
        p.strings = NULL;

        return p;
    }

    int i = 0;
    char *token = strtok(str, delim);
    while (token != NULL && i < size) {
        result[i++] = strdup(token);
        token = strtok(NULL, delim);
    }
    result = realloc(result, i * sizeof(char*));
    p.size = i;
    p.strings = result;

    return p;
}

void freeParsedStrings(char **array, int size) {
    if (array == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        free(array[i]);
    }

    free(array);
}