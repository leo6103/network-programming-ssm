#ifndef STUDENT_REGISTRATION_H
#define STUDENT_REGISTRATION_H

#define MAX_REGISTRATIONS 10000

extern const char *const REGISTRATION_FILE_NAME;

typedef struct Registration {
    char *studentId;
    char *classCode;
} Registration;

extern Registration registrations[MAX_REGISTRATIONS];

void readRegistrations();

#endif