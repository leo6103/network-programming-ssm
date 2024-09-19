#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"course_schedule.h"
#include"student_registration.h"
#include"user_account.h"


void initializeData() {
    readCourses();
    readRegistrations();
    readUsers();
}

int main() {
    initializeData();
    return 0;
}