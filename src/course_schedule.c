#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "course_schedule.h"
#include "utils.h"

const char *const COURSE_FILE_NAME = "./data/course_schedule.txt";
int courseNum;

Course courses[MAX_COURSES];

char* mergeStrings(char **strs, int start, int end, char *delim) {
    int strLength = 0;
    for (int i = start; i <= end; ++i) {
        strLength += strlen(strs[i]);
    }
    strLength += end - start;

    char *result = malloc(strLength + 1);

    strcpy(result, strs[start]);
    for (int i = start + 1; i <= end; ++i) {
        strcat(result, delim);
        strcat(result, strs[i]);
    }

    return result;
}

Schedule parseSchedule(char *schedule) {
    ParsedStrings tokens = parseStrings(schedule, ",;");

    char *room = strdup(tokens.strings[tokens.size - 1]);
    char *activeWeeks = mergeStrings(tokens.strings, 2, tokens.size - 2, ",");

    char weekDayIndex = tokens.strings[0][0];
    char *weekDay;
    switch(weekDayIndex) {
        case '2':
            weekDay = "Monday";
            break;
        case '3':
            weekDay = "Tuesday";
            break;
        case '4':
            weekDay = "Wednesday";
            break;
        case '5':
            weekDay = "Thursday";
            break;
        case '6':
            weekDay = "Friday";
            break;
        case '7':
            weekDay = "Saturday";
            break;
        default:
            weekDay = "Unkown";
            break;
    }

    char *session = tokens.strings[0][1] == '1' ? "AM" : "PM";
    int startPeriod = tokens.strings[0][2] - '0';
    int endPeriod = tokens.strings[1][2] - '0';

    Schedule s = {
        .weekDay = weekDay,
        .room = room,
        .session = session,
        .startPeriod = startPeriod,
        .endPeriod = endPeriod,
        .activeWeeks = activeWeeks
    };

    free(tokens.strings);

    return s;
}

void readCourses() {
    FILE *file = fopen(COURSE_FILE_NAME, "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", COURSE_FILE_NAME);
        return;
    }

    char *line = malloc(MAX_COURSE_LINE_LENGTH);
    int row = 0;

    while (fgets(line, MAX_COURSES, file) && row < MAX_COURSES) {
        ParsedStrings columns = parseStrings(line, " \t\n");

        char *classCode = strdup(columns.strings[0]);
        char *courseCode = strdup(columns.strings[1]);
        char *courseName = mergeStrings(columns.strings, 2, columns.size - 2, " ");
        Schedule schedule = parseSchedule(columns.strings[columns.size - 1]);

        Course course = {
            .classCode = classCode,
            .courseCode = courseCode,
            .courseName = courseName,
            .schedule = schedule
        };
        courses[row] = course;

        freeParsedStrings(columns.strings, columns.size);
        row++;
    }
    courseNum = row;

    free(line);
    fclose(file);
}