#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_GRADES 3

typedef struct _Student {
    char *firstName;
    char *lastName;
    unsigned char age;
    int *grades;
    float average;
} Student;

STATUS createStudent(FILE *fin, Student **student) {
    Student *stud = NULL;

    stud = malloc(sizeof(Student));
    if (stud == NULL) {
        return STATUS_ERROR_MEMORY;
    }

    memset(stud, 0, sizeof(Student));

    char lastName[50] = {0};
    fscanf(fin, "%s", lastName);

    //TODO: Check
    stud->lastName = malloc(strlen(lastName));
    if (stud->lastName == NULL) {
        return STATUS_ERROR_MEMORY;
    }

    memcpy(stud->lastName, lastName, strlen(lastName) + 1);
    stud->lastName[strlen(stud->lastName)] = '\0';

    char firstName[50] = {0};
    fscanf(fin, "%s", firstName);

    //TODO: Check
    stud->firstName = malloc(strlen(firstName));
    if (stud->firstName == NULL) {
        return STATUS_ERROR_MEMORY;
    }

    memcpy(stud->firstName, firstName, strlen(firstName) + 1);
    stud->firstName[strlen(stud->firstName)] = '\0';

    int age = 0;
    fscanf(fin, "%d", &age);
    stud->age = (char) age;


    stud->grades = malloc(sizeof(int) * NO_GRADES);
    if (stud->grades == NULL) {
        return STATUS_ERROR_MEMORY;
    }

    int sum = 0;
    for (int i = 0; i < NO_GRADES; i++) {
        fscanf(fin, "%d", &stud->grades[i]);
        sum += stud->grades[i];
    }

    stud->average = (float) sum / NO_GRADES;

    *student = stud;
    return STATUS_SUCCESS;
}

void printStudent(Student *student) {
    printf("Name: %s %s\nAge: %d\nAverage: %f\n", student->firstName, student->lastName, student->age, student->average);
}

void printAverage(Student *student) {
    printf("%s %s %f\n", student->firstName, student->lastName, student->average);
}

STATUS fprintStudent(FILE *fin, Student *student) {
    if (fin == NULL) {
        return STATUS_ERROR;
    }

    fprintf(fin,"%s %s %.2f\n", student->firstName, student->lastName, student->average);
    return STATUS_SUCCESS;
}

STATUS incrementByOne(Student *student) {
    int sum = 0;
    for (int i = 0; i < NO_GRADES; i++) {
        if (student->grades[i] < 10) student->grades[i]++;
        sum += student->grades[i];
    }
    student->average = (float) sum / NO_GRADES;

    return STATUS_SUCCESS;
};