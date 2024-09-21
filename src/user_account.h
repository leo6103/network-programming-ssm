#include <stdbool.h>
#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#define MAX_USERS 100
#define MAX_USER_LINE_LENGTH 100
#define USER_COLUMN_NUM 2

#define MAX_PASSWORD_ATTEMPTS 5

extern const char *const USER_FILE_NAME;
extern int userNum;
extern bool loggedIn;

typedef struct User {
    char *studentId;
    char *password;
} User;

extern User currentUser;
extern User users[MAX_USERS];

void readUsers();
void authenticate();
bool findUserById(char *id);

#endif