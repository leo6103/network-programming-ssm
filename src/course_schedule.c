#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user_account.h"
#include "student_registration.h"
#include "course_schedule.h"
#include "utils.h"

const char *const COURSE_FILE_NAME = "./data/course_schedule.txt";
int courseNum;

Course courses[MAX_COURSES];

Schedule parseSchedule(char *schedule) {
    StringList tokens = parseStrings(schedule, ",;");

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

void searchSchedule() {
    printf("Search schedule with day of the week (Monday, Tuesday, ...) or \"ALL\" :\n");
    char weekDay[20];
    fgets(weekDay, 20, stdin);
    weekDay[strcspn(weekDay, "\n")] = '\0';

    StringList registeredClasses = getRegisteredClasses(currentUser.studentId);

    printf("+---------+----------+---------------------------+-----------+---------+-------+-------+----------+------------------------+\n");
    printf("| Class   | Course   | Course Name               | Week Day  | Time    | Start | End   | Room     | Active Weeks           |\n");
    printf("+---------+----------+---------------------------+-----------+---------+-------+-------+----------+------------------------+\n");

    for (int i = 0; i < courseNum; i++) {
        if (courses[i].classCode[0] == '\0') {
            continue;
        }

        if (!courseInRegisterdClasss(registeredClasses, courses[i])) {
            continue;
        }

        if (strcmp(weekDay, "ALL") != 0 && strcmp(courses[i].schedule.weekDay, weekDay) != 0) {
            continue;
        }

        char truncatedName[26];
        strncpy(truncatedName, courses[i].courseName, 25);
        truncatedName[25] = '\0';
        if (strlen(courses[i].courseName) > 25) {
            truncatedName[22] = '.';
            truncatedName[23] = '.';
            truncatedName[24] = '.';
        }

        printf("| %-7s | %-8s | %-25s | %-9s | %-7s | %-5d | %-5d | %-8s | %-22s |\n",
               courses[i].classCode,
               courses[i].courseCode,
               truncatedName,
               courses[i].schedule.weekDay,
               courses[i].schedule.session,
               courses[i].schedule.startPeriod,
               courses[i].schedule.endPeriod,
               courses[i].schedule.room,
               courses[i].schedule.activeWeeks);
    }

    printf("+---------+----------+---------------------------+-----------+---------+-------+-------+----------+------------------------+\n");
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
        StringList columns = parseStrings(line, " \t\n");

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

        freeStringList(columns.strings, columns.size);
        row++;
    }
    courseNum = row;

    free(line);
    fclose(file);
}