#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#define MAX_USERS

extern const char *const USER_FILE_NAME;

typedef struct User {
    char *studentId;
    char *classCode;
} User;

extern User users[MAX_USERS];

void readUsers();

#endif