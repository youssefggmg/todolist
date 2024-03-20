#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task.h"

int main() {
    time_t tm = time(NULL);
    struct tm date = *localtime(&tm);
    char mode, filename[255], choix[4], taskTitle[30], userTask[255], dueDate[20];
    int priority, line_number, complated=0;
    FILE *file;

    
    do {
        system("clear");
        printf("Welcome to the todolist program\n");
        printf("\t a: add task\n\t d: delete task\n\t l: list all tasks\n\t e: edit task\n\t p: filter tasks by priority\n\t t: filter tasks by due date\n\t m: mark task as done \n\t q: quit\n");
        scanf(" %c", &mode);

        if (mode == 'a') {
            do {
                system("clear");
                printf("\nAdding a new task:\n");
                printf("Enter the name of the file: ");
                scanf("%s", filename);

                printf("Enter the title of the task you want to add: ");
                scanf(" %[^\n]", taskTitle);

                printf("Enter your task: ");
                scanf(" %[^\n]", userTask);

                printf("Enter the priority of the task (1: Low, 2: Medium, 3: High): ");
            do {
                if (scanf("%d", &priority) != 1 || priority < 1 || priority > 3) {
                    printf("Invalid input! Priority must be 1, 2, or 3. Please try again: ");
                    while (getchar() != '\n'); // Clear input buffer
                }
            } while (priority < 1 || priority > 3);
                

                printf("Enter the due date of the task (YYYY-MM-DD): ");
                scanf("%s", dueDate);

                Task newTask;
                strcpy(newTask.taskTitle, taskTitle);
                strcpy(newTask.userTask, userTask);
                newTask.priority = priority;
                strcpy(newTask.dueDate, dueDate);
                newTask.completed=complated;

                add(filename, newTask, file);
                printf("Do you want to add something else? (yes/no) ");
                scanf("%s", choix);
            } while (strcmp(choix, "yes") == 0);
        } else if (mode == 'l') {
            do {
                system("cls");
                printf("\nReading a list:\n");
                printf("Enter the name of the file: ");
                scanf("%s", filename);
                list(filename, file);
                printf("\nDo you want to read another list? (yes/no) ");
                scanf("%s", choix);
            } while (strcmp(choix, "yes") == 0);
        } else if (mode == 'p') {
            do {
                system("cls");
                printf("\nFiltering tasks by priority:\n");
                printf("Enter the name of the file: ");
                scanf("%s", filename);
                printf("Enter priority level (1: Low, 2: Medium, 3: High): ");
                scanf("%d", &priority);
                filterByPriority(filename, priority, file);
                printf("\nDo you want to filter by priority again? (yes/no) ");
                scanf("%s", choix);
            } while (strcmp(choix, "yes") == 0);
        } else if (mode == 't') {
            do {
                system("cls");
                printf("\nFiltering tasks by due date:\n");
                printf("Enter the name of the file: ");
                scanf("%s", filename);
                printf("Enter due date (YYYY-MM-DD): ");
                scanf("%s", dueDate);
                filterByDueDate(filename, dueDate, file);
                printf("\nDo you want to filter by due date again? (yes/no) ");
                scanf("%s", choix);
            } while (strcmp(choix, "yes") == 0);
        } else if (mode == 'e') {
            do {
                system("cls");
                printf("\nEditing a task:\n");
                printf("Enter the name of the file: ");
                scanf("%s", filename);

                printf("\n");

                printf("Enter the line number you want to edit: ");
                scanf("%d", &line_number);
                printf("Enter the new content: ");
                scanf(" %[^\n]", userTask);

                editLine(filename, line_number, userTask);

                printf("Task edited successfully.\n");
                printf("Do you want to edit another task? (yes/no) ");
                scanf("%s", choix);
            } while (strcmp(choix, "yes") == 0);
        }else if (mode == 'd') {
            do {
                system("cls");
                printf("\nDeleting a task:\n");
                printf("Enter the name of the file: ");
                scanf("%s", filename);

                file = fopen(filename, "r+");

                printf("\nEnter the line number you want to delete: ");
                scanf("%d", &line_number);

                deletingatask(filename, line_number, file);

                fclose(file);

                printf("Task deleted successfully.\n");
                printf("Do you want to delete another task? (yes/no) ");
                scanf("%s", choix);
    } while (strcmp(choix, "yes") == 0); 
}else if (mode == 'm') { // 'm' for marking tasks as completed
        do {
            system("clear");
            printf("\nMarking a task as completed:\n");
            printf("Enter the name of the file: ");
            scanf("%s", filename);

            printf("\nEnter the line number of the task you want to mark as completed: ");
            scanf("%d", &line_number);

            markCompleted(filename, line_number, file);

            printf("Task marked as completed successfully.\n");
            printf("Do you want to mark another task as completed? (yes/no) ");
            scanf("%s", choix);
        } while (strcmp(choix, "yes") == 0); 
    }else if (mode == 'q') {
            printf("All your tasks have been saved. See you soon!\n");
            return 0;
        } else {
            printf("You have entered an invalid command\n");
            return 0;
        }
    } while (1);

    return 0;
}