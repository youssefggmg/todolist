#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add( char filename[50],  char userTask[255], FILE *file) {

    strcat(filename,".txt");  /* Concatenates "todo_" and the entered string */
    
    file = fopen(filename, "a+"); /* Opens or creates the file in append + read/write mode */
    if (!file) { /* If there was an error opening/creating the file... */
        printf("Error creating/opening the file!\n");
        exit(1); /* ...then terminate the program with status 1 */
    }
    fputs(userTask, file);
    fputs( "\n\n\n\n", file); /* Add a new line after each task */
    printf("%s has been added.\n", userTask);
    fclose(file); /* Close the file after writing */

}

int main() {
    system("cntrl +c");
    char mode, filename [255] , userTask[255] , choix[4];
    FILE *file;
// the program will run until the user decide to quit
    do{
    system("clear"); // Use "clear" for Unix-like systems
    system("color 20"); // Use "color 7

    printf("Welcome to the todolist program\n");
    printf("\t a: add task\n\t d: delete task\n\t l: list all tasks\n\t e: edit task\n");
    scanf(" %c", &mode);

    if (mode == 'a') { 
        do {
            system("clear");
            printf("\nAdding a new task:\n");
            printf("Enter the name of the file: ");
            scanf("%s", filename); 

            printf("Enter your task: ");
            scanf(" %[^\n]", userTask);

            add(filename, userTask, file);
            printf("Do you want to add something else? (yes/no) ");
            scanf("%s", choix);
        } while (strcmp(choix, "yes") == 0);
    }
    
    } while (1);
    
    
    

    return 0;
}
