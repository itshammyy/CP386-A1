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
        // Fork failed for the parent
        perror("Fork failed for parent");
        exit(1);
    } else if (pid1 == 0) {
        // Inside child process
        pid_t parent_id = getppid();  // Get the grandparent (parent's) ID

        // Child forks the grandchild
        pid2 = fork();

        if (pid2 < 0) {
            // Fork failed for the child
            perror("Fork failed for child");
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
        // Parent exits after child is done
        exit(0);
    }

    return 0;
}
