#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "course_schedule.h"
#include "student_registration.h"
#include "utils.h"

const char *const REGISTRATION_FILE_NAME = "./data/student_registration.txt";
int registrationNum;
Registration registrations[MAX_REGISTRATIONS];

StringList getRegisteredClasses(char *studentId) {
    char **classes = malloc(registrationNum * sizeof(char *));

    int index = 0;
    for (int i = 0; i < registrationNum; i++) {
        if (strcmp(registrations[i].studentId, studentId) == 0) {
            char *classCode = strdup(registrations[i].classCode);
            classes[index] = classCode;
            index++;
        }
    }

    realloc(classes, index * sizeof(char *));
    StringList l = {
        .size = index,
        .strings = classes
    };

    return l;
}

bool courseInRegisterdClasss(StringList classes, Course course) {
    for (int i = 0; i < classes.size; i++) {
        if (strcmp(classes.strings[i], course.classCode) == 0) {
            return true;
        }
    }

    return false;
}

void readRegistrations() {
    FILE *file = fopen(REGISTRATION_FILE_NAME, "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", REGISTRATION_FILE_NAME);
        return;
    }

    char *line = malloc(MAX_REGISTRATION_LINE_LENGTH);
    int row = 0;

    while(fgets(line, MAX_REGISTRATIONS, file) && row < MAX_REGISTRATIONS) {
        StringList columns = parseStrings(line, " \t\n");

        char *studentId = strdup(columns.strings[0]);
        char *classCode = strdup(columns.strings[1]);

        Registration registration = {
            .studentId = studentId,
            .classCode = classCode
        };
        registrations[row] = registration;

        freeStringList(columns.strings, columns.size);
        row++;
    }
    registrationNum = row;

    free(line);
    fclose(file);
}