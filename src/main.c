#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course_schedule.h"
#include "student_registration.h"
#include "user_account.h"


void initializeData() {
    readCourses();
    readRegistrations();
    readUsers();
}

void searchScheduleOnWeekDay(const char *searchWeekDay) {
    printf("+---------+----------+---------------------------+-----------+---------+-------+-------+----------+------------------------+\n");
    printf("| Class   | Course   | Course Name               | Week Day  | Time    | Start | End   | Room     | Active Weeks           |\n");
    printf("+---------+----------+---------------------------+-----------+---------+-------+-------+----------+------------------------+\n");

    for (int i = 0; i < courseNum; i++) {
        if (courses[i].classCode[0] == '\0') {
            continue;
        }

        if (strcmp(searchWeekDay, "ALL") != 0 && strcmp(courses[i].schedule.weekDay, searchWeekDay) != 0) {
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

int main() {
    initializeData();
    searchScheduleOnWeekDay("ALL");
    return 0;
}