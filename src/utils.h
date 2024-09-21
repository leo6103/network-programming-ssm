#ifndef UTILS_H
#define UTILS_H

typedef struct StringList {
    int size;
    char **strings;
} StringList;

StringList parseStrings(const char* str, const char *delim);
void displayStringList(StringList strList);
void freeStringList(char **array, int size);
char* mergeStrings(char **strs, int start, int end, char *delim);
void printSystemTitle();
void printLoginSuccessfulMessage();
void disableEcho();
void enableEcho();
#endif