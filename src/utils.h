#ifndef UTILS_H
#define UTILS_H

typedef struct ParsedStrings {
    int size;
    char **strings;
} ParsedStrings;

ParsedStrings parseStrings(const char* str, const char *delim);

void freeParsedStrings(char **array, int size);
#endif