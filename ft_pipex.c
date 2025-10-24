#include "pipex.h"
#include <fcntl.h>
int main(int ac, char **argv, char **envp)
{
    int fdes[2];
    char *pathname;
    int fd;
    char **cmd_args;
    pid_t id;

    if (!ac)
        return (0);
    if (pipe(fdes) < 0)
    {
        perror("pipe");
        return (-2);
    }
    id = fork();
    if (id == 0)
    {
        close(fdes[0]);
        // fd = dup(STDOUT_FILENO);
        dup2(fdes[1], STDOUT_FILENO);
        pathname = ft_search_pathname(envp, argv[2]);
        cmd_args = ft_split(argv[2], ' ');
        close(fdes[1]);
        // close(fdes[1]);
        // printf("This will be written\n");
        execve(pathname, cmd_args, envp);
        exit(0);
    }
    else
    {
        char buffer[1024];
        close(fdes[1]);
        fd = open(argv[1], O_RDWR | O_CREAT);
        dup2(fd, STDIN_FILENO);
        while (read(fdes[0], buffer, sizeof(buffer)) != 0)
            write(fd, buffer, sizeof(buffer));
        close(fd);
        close(fdes[0]);
    }
    // id = fork();
    // if (id == 0)
    // {
    //     dup(2)
    // }
    // waitpid(id);//Waits for first child to finish
    // wait(&id);//Waits for second child to finish
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
