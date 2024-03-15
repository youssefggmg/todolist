#include <stdio.h>
void add(char filename[50],char userTask[255]){
    FILE *file;

        strcat(filename, ".txt");  /* Concatenates "todo_" and the entered string */
        
        file = fopen(filename, "a+");     /* Opens or creates the file in write + binary format */
	if (!file) {                          /* If there was an error opening/creating the file... */
            printf("Error creating/opening the file!\n");
            exit(1);                       /* ...then terminate the program with status 1 */
        }
        fputs(userTask, file);
        printf("%s has been added.\n", userTask);
}