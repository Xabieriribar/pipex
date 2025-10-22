// #include "pipex.h"
// #include <fcntl.h>
// int main(int argc, char **argv, char **envp)
// {
//     int fdes[2];
//     pid_t id;

//     if (ft_check_access(argc, argv) == -1)
//     {
//         return (-1);
//     }
//     if (pipe(fdes) < 0)
//     {
//         perror("pipe");
//         return (-2);
//     }
//     id = fork();
//     if (id == 0)
//     {
//         dup2(fdes[1], STDIN_FILENO);
//         execve()
//     }


//     waitpid(id);//Waits for first child to finish
//     waitpid(id);//Waits for second child to finish
//     return (0);
// }
// {
//     (void)argc;
//     const char *filename = "usr/bin/grep";
//     char *const av[] = {"usr/bin/grep", "adios", NULL};
//     execve(filename, argv, envp);
// }
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
    char *cmd_path = "/bin/ls";
    char *cmd_args[] = { "ls", "-l", NULL };

    for (int i = 0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);
    printf("Antes de execve\n");

    if (execve(cmd_path, cmd_args, envp) == -1)
    {
        perror("execve fallo");
        exit(EXIT_FAILURE);
    }

    return 0; // nunca se ejecuta si execve tiene éxito
}
