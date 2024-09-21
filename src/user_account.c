#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user_account.h"
#include "utils.h"

const char *const USER_FILE_NAME = "./data/user_account.txt";
int userNum;
bool loggedIn;
User currentUser;
User users[MAX_USERS];

const char *INPUT_ID_MESSAGE = "Student ID :\n";
const char *INPUT_PW_MESSAGE = "Password :\n";

bool findUserById(char *id) {
    for (int i = 0; i < userNum; i++) {
        if (strcmp(users[i].studentId, id) == 0) {
            currentUser = users[i];
            return true;
        }
    }
    return false;
}

void readUsers() {
    FILE *file = fopen(USER_FILE_NAME, "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", USER_FILE_NAME);
        return;
    }

    char *line = malloc(MAX_USER_LINE_LENGTH);
    int row = 0;

    while(fgets(line, MAX_USERS, file) && row < MAX_USERS) {
        StringList columns = parseStrings(line, " \t\n");

        char *studentId = strdup(columns.strings[0]);
        char *password = strdup(columns.strings[1]);

        User user = {
            .studentId = studentId,
            .password = password
        };
        users[row] = user;

        freeStringList(columns.strings, columns.size);
        row++;
    }
    userNum = row;

    free(line);
    fclose(file);
}

void authenticate() {
    loggedIn = false;
    while (!loggedIn) {
        printf("%s",INPUT_ID_MESSAGE);
        char studentIdInp[20];
        fgets(studentIdInp, 20, stdin);
        studentIdInp[strcspn(studentIdInp, "\n")] = '\0';
        loggedIn = findUserById(studentIdInp);

        bool correctPw = false;
        int incorrectCount = 0;
        while (loggedIn && !correctPw) {
            printf("%s", INPUT_PW_MESSAGE);
            char passwordInp[20];
            disableEcho();
            fgets(passwordInp, 20, stdin);
            enableEcho();
            passwordInp[strcspn(passwordInp, "\n")] = '\0';

            if (strcmp(currentUser.password, passwordInp) != 0) {
                printf("%s", INPUT_PW_MESSAGE);

                incorrectCount++;
                if (incorrectCount == MAX_PASSWORD_ATTEMPTS) {
                    loggedIn = false;
                    exit(0);
                }
            } else {
                loggedIn = true;
                break;
            }
        }
    }
    printLoginSuccessfulMessage();
}