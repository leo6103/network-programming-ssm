#ifndef COURSE_SCHEDULE_H
#define COURSE_SCHEDULE_H

extern const char *const COURSE_FILE_NAME;

typedef struct Course {
    char classCode[7];
    char courseCode[7];
    char courseName[100];
    short weekDay;
    short timeOfDay;
    short startPeriod;
    short endPeriod;
    char activeWeeks[16];
}Course;

extern Course courses[20];

void readCourses();

#endif