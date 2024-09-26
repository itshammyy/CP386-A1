//Assignment 1
//By: Michael Tahirovic, Ben Hamilton, Zach Pereira
//Emails: tahi9525@mylaurier.ca, hami5217@mylaurier.ca, pere
//Date: 2024-09-26
//------------------------------------------------------------------------------------------
//Question 2b:
//Suppose we have n programs p1,...,pn to be executed. The programs are described in an input text file. 
//(b) Now suppose each program pi depends on all the programs p1,...,pi−1. This means the programs
//should be executed sequentially, first completing p1, then p2 and so on. Modify the parallel
//program executor you designed in part (a) to obtain a sequential program executor.
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    // Open input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Read number of programs
    int n;
    if (fscanf(input_file, "%d", &n) != 1) {
        fprintf(stderr, "Error reading the number of programs\n");
        fclose(input_file);
        exit(1);
    }

    // Dynamically allocate memory for program paths
    char **paths = malloc(n * sizeof(char *));
    if (paths == NULL) {
        perror("Memory allocation failed");
        fclose(input_file);
        exit(1);
    }

    // Read program paths
    for (int i = 0; i < n; i++) {
        paths[i] = malloc(256 * sizeof(char)); // Allocate memory for each path
        if (paths[i] == NULL || fscanf(input_file, "%255s", paths[i]) != 1) {
            fprintf(stderr, "Error reading program path\n");
            fclose(input_file);
            for (int j = 0; j <= i; j++) free(paths[j]); // Free allocated memory
            free(paths);
            exit(1);
        }
    }
    fclose(input_file);

    // Execute programs sequentially
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            // Fork failed
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process: Execute the program
            char *args[] = {paths[i], NULL};
            execvp(args[0], args);
            // If execvp fails
            perror("Error executing program");
            exit(1);
        } else {
            // Parent process: Wait for the current child to finish
            wait(NULL);
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(paths[i]);
    }
    free(paths);

    printf("All programs executed sequentially.\n");
    return 0;
}
