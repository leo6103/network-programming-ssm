#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user_account.h"
#include "utils.h"

const char *const USER_FILE_NAME = "./data/user_account.txt";
int userNum;
User users[MAX_USERS];

void readUsers() {
    FILE *file = fopen(USER_FILE_NAME, "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", USER_FILE_NAME);
        return;
    }

    char *line = malloc(MAX_USER_LINE_LENGTH);
    int row = 0;

    while(fgets(line, MAX_USERS, file) && row < MAX_USERS) {
        ParsedStrings columns = parseStrings(line, " \t\n");

        char *studentId = strdup(columns.strings[0]);
        char *password = strdup(columns.strings[1]);

        User user = {
            .studentId = studentId,
            .password = password
        };
        users[row] = user;

        freeParsedStrings(columns.strings, columns.size);
        row++;
    }
    userNum = row;

    free(line);
    fclose(file);
}