#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task.h"


void add(char filename[50], Task task, FILE *file) {
    time_t tm = time(NULL);
    struct tm date = *localtime(&tm);

    strcat(filename, ".txt");

    file = fopen(filename, "a+");
    if (!file) {
        printf("Error creating/opening the file!\n");
        exit(1);
    }

    // Add task to the end of the list
    fprintf(file, "\t\t%s\nPriority: %d\nDue Date: %s\n\ncomplated = %d\n\n%s\nThis task was added on %d/%d/%d\n\n",
    task.taskTitle, task.priority, 
    task.dueDate,task.completed, task.userTask,
    date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
    printf("%s: your task has been added.\n", task.userTask);
    fclose(file);
}

void list(char filename[50], FILE *file) {
    char string[100];
    int line_number = 0;

    strcat(filename, ".txt");

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error!\n");
        exit(1);
    }

    while (fgets(string, sizeof(string), file)) {
        line_number++;
        printf("%d: %s", line_number, string);
    }

    fclose(file);
}

void filterByPriority(char filename[50], int priority, FILE *file) {
    char string[100];
    int line_number = 0;

    strcat(filename, ".txt");

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error!\n");
        exit(1);
    }

    while (fgets(string, sizeof(string), file)) {
        line_number++;
        if (line_number % 7 == 2) { // Check line number corresponding to priority
            int taskPriority;
            sscanf(string, "Priority: %d", &taskPriority);
            if (taskPriority == priority) {
                printf("%s", string);
                // Print the next 6 lines of the task
                for (int i = 0; i < 6; i++) {
                    fgets(string, sizeof(string), file);
                    printf("%s", string);
                }
            }
        }
    }

    fclose(file);
}

void filterByDueDate(char filename[50], char dueDate[20], FILE *file) {
    char string[100];
    int line_number = 0;

    strcat(filename, ".txt");

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error!\n");
        exit(1);
    }

    while (fgets(string, sizeof(string), file)) {
        line_number++;
        if (line_number % 7 == 3) { // Check line number corresponding to due date
            char taskDueDate[20];
            sscanf(string, "Due Date: %s", taskDueDate);
            if (strcmp(taskDueDate, dueDate) == 0) {
                printf("%s", string);
                // Print the next 6 lines of the task
                for (int i = 0; i < 6; i++) {
                    fgets(string, sizeof(string), file);
                    printf("%s", string);
                }
            }
        }
    }

    fclose(file);
}

void deletingatask(char filename[50], int line_number, FILE *file) {
    FILE *tmp;
    char tmpfile[50] = "temp.txt";
    char buffer[255];
    int count = 0;

    strcat(filename, ".txt");

    file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening the file for editing.\n");
        exit(1);
    }

    tmp = fopen(tmpfile, "w");
    if (tmp == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count < line_number || count > line_number + 7) { 
            fprintf(tmp, "%s", buffer);
        }
    }

    fclose(file);
    fclose(tmp);

    remove(filename);
    rename(tmpfile, filename);
}

void editLine(char filename[50], int line_number, char *new_content) {
    FILE *file;
    FILE *tmp;
    char tmpfile[50] = "temp.txt";
    char buffer[255];
    int count = 0;
    time_t tm = time(NULL);
    struct tm date = *localtime(&tm);

    strcat(filename, ".txt");

    file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening the file for editing.\n");
        exit(1);
    }

    tmp = fopen(tmpfile, "w");
    if (tmp == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count == line_number) {
            fprintf(tmp, "%s\n", new_content);
            fprintf(tmp, "\nThis task was edited on %d/%d/%d\n\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
        } else {
            fprintf(tmp, "%s", buffer);
        }
    }

    fclose(file);
    fclose(tmp);

    remove(filename);
    rename(tmpfile, filename);
}

void markCompleted(char filename[50], int line_number, FILE *file) {
    FILE *tmp;
    char tmpfile[50] = "temp.txt";
    char buffer[255];
    int count = 0;
    int completed = 0; // Flag to indicate whether the current task is marked as completed

    strcat(filename, ".txt");

    file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening the file for editing.\n");
        exit(1);
    }

    tmp = fopen(tmpfile, "w");
    if (tmp == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count == line_number) {
            // Mark task as completed by setting the completed field to 1
            fprintf(tmp, "%s", buffer);
            // Replace the completion status with 1
            fprintf(tmp, "Completed: 1\n");
            completed = 1; // Set the completed flag
        } else {
            fprintf(tmp, "%s", buffer);
        }

        // If the current task is marked as completed, don't copy the next 5 lines
        if (completed && count < line_number + 5) {
            continue;
        }
    }

    fclose(file);
    fclose(tmp);

    remove(filename);
    rename(tmpfile, filename);
}