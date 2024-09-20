#ifndef COURSE_SCHEDULE_H
#define COURSE_SCHEDULE_H

#define MAX_COURSES 100
#define MAX_LINE_LENGTH 1024
#define MIN_FILE_COLUMNS 5

extern const char *const COURSE_FILE_NAME;
extern int courseNum;

typedef struct Schedule {
    char *weekDay;
    char *session; // AM or PM
    char *room;
    char *activeWeeks;
    short startPeriod, endPeriod;
} Schedule;

typedef struct Course {
    char *classCode;
    char *courseCode;
    char *courseName;
    Schedule schedule;
} Course;

extern Course courses[MAX_COURSES];

void readCourses();

#endif