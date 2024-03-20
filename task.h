#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <stdio.h>

typedef struct {
    char taskTitle[30];
    char userTask[255];
    int priority; 
    char dueDate[20];
    int completed; // 1 - done, 0 - not done
} Task;

void add(char filename[50], Task task, FILE *file);
void list(char filename[50], FILE *file);
void filterByPriority(char filename[50], int priority, FILE *file);
void filterByDueDate(char filename[50], char dueDate[20], FILE *file);
void deletingatask(char filename[50], int line_number, FILE *file);
void editLine(char filename[50], int line_number, char *new_content);
void markCompleted(char filename[50], int line_number, FILE *file);

#endif // TASK_H_INCLUDED