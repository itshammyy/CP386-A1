# CP386-A1-Q1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // Parent forks a child
    pid1 = fork();

    if (pid1 < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid1 == 0) {
        // Inside child process
        pid_t parent_id = getppid();  // Get the grandparent (parent's) ID

        // Child forks the grandchild
        pid2 = fork();

        if (pid2 < 0) {
            // Fork failed
            fprintf(stderr, "Fork failed\n");
            exit(1);
        } else if (pid2 == 0) {
            // Inside grandchild process
            printf("My process id is %d, my parent’s id is %d, and my grandparent’s id is %d\n", getpid(), getppid(), parent_id);
            exit(0);  // Grandchild exits after printing
        } else {
            // Inside child process
            wait(NULL);  // Wait for grandchild to finish
            exit(0);     // Child exits after forking grandchild
        }
    } else {
        // Inside parent process
        wait(NULL);  // Wait for child to finish
        exit(0);     // Parent exits
    }

    return 0;
}


Problem Recap:
We need to create a program where:
	1. A parent process forks a child process.
	2. The child forks a grandchild.
	3. The grandchild prints its process ID (X), its parent’s process ID (Y), and its grandparent's process ID (Z).

Summary:

	1. Parent Process:
		○ Creates a child using fork().
		○ Waits for the child to finish using wait(NULL) and then exits.
	2. Child Process:
		○ Creates its own child (grandchild) using fork().
		○ Waits for the grandchild to finish using wait(NULL) and then exits.
	3. Grandchild Process:
		○ Prints its own process ID, its parent’s (child’s) process ID, and its grandparent’s (parent’s) process ID.
		○ Exits after printing.
![image](https://github.com/user-attachments/assets/616a6c85-7dc9-47e4-9008-2026ca818987)
