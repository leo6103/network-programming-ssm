#include <stdbool.h>
#include "course_schedule.h"
#include "utils.h"
#ifndef STUDENT_REGISTRATION_H
#define STUDENT_REGISTRATION_H

#define MAX_REGISTRATIONS 10000
#define MAX_REGISTRATION_LINE_LENGTH 100
#define REGISTRATION_COLUMN_NUM 2

extern const char *const REGISTRATION_FILE_NAME;
extern int registrationNum;

typedef struct Registration {
    char *studentId;
    char *classCode;
} Registration;

extern Registration registrations[MAX_REGISTRATIONS];

void readRegistrations();
StringList getRegisteredClasses(char *studentId);
bool courseInRegisterdClasss(StringList classes, Course course);

#endif