#ifndef STUDENT_REGISTRATION_H
#define STUDENT_REGISTRATION_H

extern const char *const REGISTRATION_FILE_NAME;

typedef struct Registration {
    char studentId[9];
    char classCode[7];
} Registration;

extern Registration registrations[20];

void readRegistrations();

#endif