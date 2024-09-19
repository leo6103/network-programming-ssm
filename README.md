# STUDENT SCHEDULE MANAGEMENT CLI PROGRAM

## Description:
We need a small Study Schedule Management program for students in the university. The program works should allow
students to:
- login (using student ID and password).
- Read schedule of one weekday by providing the weekday. For example: student provides “Thursday” and the program.
return list of all courses and schedule of the courses of the day.

Internally, the program store the list of registered courses (by students) and their schedules in 3 text files. The structure of the file is as following:

`course_schedule.txt`
```
119747 IT3080 Computer Network 523,526,22,25-31,33-40,TC-502;
119748 IT4560 Computer Literacy 221,224,22,25-31,33-40,TC-211;
119749 IT4590 Database 524,526,22,25-31,33-40,D6-101;
119750 IT4935 Database Lab 615,616,22,25-31,D6-303;
```
`student_registration.txt`
```
20191121 119747
20191121 119750
20191121 119748
20203121 119748
20191121 119747
```
`user_account.txt`
```
20203121 passwd1
20191121 passwd2
```
## Required functionalities:
### Internal:
- Represent courses by structures.
- Represent relationship student -registered classes by structures.
- Once the program starts, read study schedule from files and represent the
38- Once the program starts, read study schedule from files and represent the information under the form of a list of courses (structure), list of registration
(structure).
### Human interface
- Login.
- Read Schedule with input : weekday (Monday, Tuesday,...) or "ALL"

## Run program
### Build executable
```
make
```
### Run program
```
make run
```
### Clean program
```
make clean
```