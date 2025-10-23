#include "pipex.h"
#include <fcntl.h>
int main(int argc, char **argv, char **envp)
{
    int fdes[2];
    int fd;
    char *pathname;
    char **cmd_args;
    pid_t id;

    fd = open("infile", O_RDONLY);
    (void)argc;
    if (pipe(fdes) < 0)
    {
        perror("pipe");
        return (-2);
    }
    id = fork();
    if (id == 0)
    {
        close(fdes[0]);
        fdes[1]= dup(0);
        pathname = ft_search_pathname(envp, argv[1]);
        cmd_args = ft_split(argv[1], ' ');
        execve(pathname, cmd_args, envp);
        close(fdes[1]);
        exit(0);
    }
    // id = fork();
    // if (id == 0)
    // {
    //     dup(2)
    // }
    // waitpid(id);//Waits for first child to finish
    wait(&id);//Waits for second child to finish
    return (0);
}
// {
//     (void)argc;
// 	char *pathname = ft_search_pathname(envp, argv[1]);
//     // char *cmd_args[] = ft_split(argv[1], ' ');
//     char **cmd_args = ft_split(argv[1], ' ');
//     printf("%s\n%s\n%s\n", cmd_args[0], cmd_args[1], cmd_args[2]);
// 	printf("My pathanme is %s\n", pathname);
// 	execve(pathname, cmd_args, envp);
// }
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char **argv, char **envp)
// {
//     char *cmd_path = "/bin/ls";
//     char *cmd_args[] = { "ls", "-l", NULL };

//     for (int i = 0; envp[i] != NULL; i++)
//         printf("%s\n", envp[i]);
//     printf("Antes de execve\n");

//     if (execve(cmd_path, cmd_args, envp) == -1)
//     {
//         perror("execve fallo");
//         exit(EXIT_FAILURE);
//     }

//     return 0; // nunca se ejecuta si execve tiene éxito
// }
