#include <unistd.h>   // execve, fork
#include <stdio.h>    // perror
#include <stdlib.h>   // exit
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    if (pid == -1)
        return perror("fork"), 1;

    if (pid == 0)      // child process
    {
        char *argv[] = { "ls", "-l", NULL };
        char *envp[] = { NULL };   // inherit nothing extra for clarity

        execve("/bin/ls", argv, envp);
        perror("execve");          // only runs if execve failed
        exit(EXIT_FAILURE);
    }

    // parent keeps running here: wait, pipeline logic, etc.
    wait(NULL);
    return 0;
}
