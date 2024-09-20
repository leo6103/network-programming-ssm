#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_registration.h"
#include "utils.h"

const char *const REGISTRATION_FILE_NAME = "./data/student_registration.txt";
int registrationNum;
Registration registrations[MAX_REGISTRATIONS];

void readRegistrations() {
    FILE *file = fopen(REGISTRATION_FILE_NAME, "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", REGISTRATION_FILE_NAME);
        return;
    }

    char *line = malloc(MAX_REGISTRATION_LINE_LENGTH);
    int row = 0;

    while(fgets(line, MAX_REGISTRATIONS, file) && row < MAX_REGISTRATIONS) {
        ParsedStrings columns = parseStrings(line, " \t\n");

        char *studentId = strdup(columns.strings[0]);
        char *classCode = strdup(columns.strings[1]);

        Registration registration = {
            .studentId = studentId,
            .classCode = classCode
        };
        registrations[row] = registration;

        freeParsedStrings(columns.strings, columns.size);
        row++;
    }
    registrationNum = row;

    free(line);
    fclose(file);
}