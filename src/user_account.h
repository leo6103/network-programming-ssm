#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

extern const char *const USER_FILE_NAME;

typedef struct User {
    char studentId[9];
    char classCode[7];
} User;

extern User users[20];

void readUsers();

#endif