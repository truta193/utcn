#pragma once
#include <stdio.h>

typedef enum {
    STATUS_SUCCESS = 0,
    STATUS_ERROR = -1,
    STATUS_ERROR_MEMORY = -2
} STATUS;

typedef struct _Student Student;

STATUS createStudent(FILE *fin, Student **student);
void printStudent(Student *student);
STATUS fprintStudent(FILE *fin, Student *student);
void printAverage(Student *student);
STATUS incrementByOne(Student *student);