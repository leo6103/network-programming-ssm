#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "utils.h"

StringList parseStrings(const char* str, const char *delim) {
    char **result;
    StringList p;

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

void displayStringList(StringList strList) {
    for (int i = 0; i < strList.size; i++) {
        printf("%s\n", strList.strings[i]);
    }
    freeStringList(strList.strings, strList.size);
}

void freeStringList(char **array, int size) {
    if (array == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        free(array[i]);
    }

    free(array);
}

char* mergeStrings(char **strs, int start, int end, char *delim) {
    int strLength = 0;
    for (int i = start; i <= end; ++i) {
        strLength += strlen(strs[i]);
    }
    strLength += end - start;

    char *result = malloc(strLength + 1);

    strcpy(result, strs[start]);
    for (int i = start + 1; i <= end; ++i) {
        strcat(result, delim);
        strcat(result, strs[i]);
    }

    return result;
}

void printSystemTitle() {
    printf(" _____ ________  ___           _____           _                 \n");
    printf("/  ___/  ___|  \\/  |          /  ___|         | |                \n");
    printf("\\ `--.\\ `--.| .  . |  ______  \\ `--. _   _ ___| |_ ___ _ __ ___  \n");
    printf(" `--. \\`--. \\ |\\/| | |______|  `--. \\ | | / __| __/ _ \\ '_ ` _ \\ \n");
    printf("/\\__/ /\\__/ / |  | |          /\\__/ / |_| \\__ \\ ||  __/ | | | | |\n");
    printf("\\____/\\____/\\_|  |_/          \\____/ \\__, |___/\\__\\___|_| |_| |_|\n");
    printf("                                      __/ |                      \n");
    printf("                                     |___/                       \n");
}

void printLoginSuccessfulMessage() {
    printf("  _              _                                 __      _ \n");
    printf(" | |   ___  __ _(_)_ _    ____  _ __ __ ___ ______/ _|_  _| |\n");
    printf(" | |__/ _ \\/ _` | | ' \\  (_-< || / _/ _/ -_|_-<_-<  _| || | |\n");
    printf(" |____\\___/\\__, |_|_||_| /__/\\_,_\\__\\__\\___/__/__/_|  \\_,_|_|\n");
    printf("           |___/                                              \n");
}

void disableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
