#include "pipex.h"
#include "pipex_utils.c"
#include "stdio.h"

// void    run_child(int file, int fdes[], int mode, char **envp, char **argv)
// {
//     char *pathname;
//     char **cmd_args;

//     if (mode == WRITE)
//     {
//         close(fdes[0]);
//         dup2(file, STDIN_FILENO);
//         dup2(fdes[1], STDOUT_FILENO);
//         pathname = ft_search_pathname(envp, argv[2], &pathname);
//         cmd_args = ft_split(argv[2], ' ');
//         if (execve(pathname, cmd_args, envp) == -1)
//         {
//             perror("Execve failed");
//             exit(127);
//         }
//     }
//     else if (mode == READ)
//     {
//         close(fdes[1]);
//         dup2(file, STDOUT_FILENO);
//         dup2(fdes[0], STDIN_FILENO);
//         pathname = ft_search_pathname(envp, argv[3]);
//         cmd_args = ft_split(argv[3], ' ');
//         close(fdes[0]);
//         if (execve(pathname, cmd_args, envp) == -1)
//         {
//             perror("Execve failed");
//             exit(127);
//         }
//     }




// }
// int run_childs(int infile, int outfile, char **envp, char **argv)
// {
//     int fdes[2];
//     // char *pathname;
//     int status;
//     // char **cmd_args;
//     pid_t id;
//     pid_t id2;

//     if (pipe(fdes) < 0)
//     {
//         perror("pipe");
//         return (1);
//     }
//     if (infile >= 0)
//     {
//         id = fork();
//         if (id == 0)
//         {
//             run_child(infile, fdes, READ, envp, char **argv)
//             // close(fdes[0]);
//             // dup2(infile, STDIN_FILENO);
//             // dup2(fdes[1], STDOUT_FILENO);
//             // pathname = ft_search_pathname(envp, argv[2]);
//             // cmd_args = ft_split(argv[2], ' ');
//             // close(fdes[1]);
//             // if (execve(pathname, cmd_args, envp) == -1)
//             // {
//             //     perror("Execve failed");
//             //     exit(127);
//             // }
//         }
//     }
//     id2 = fork();
//     if (id2 == 0)
//     {
//         run_child(outfile, fdes, WRITE, envp);
//         // close(fdes[1]);
//         // dup2(outfile, STDOUT_FILENO);
//         // dup2(fdes[0], STDIN_FILENO);
//         // pathname = ft_search_pathname(envp, argv[3]);
//         // cmd_args = ft_split(argv[3], ' ');
//         // close(fdes[0]);
//         // if (execve(pathname, cmd_args, envp) == -1)
//         // {
//         //     perror("Execve failed");
//         //     exit(127);
//         // }
//     }
//     close(fdes[1]);
//     close(fdes[0]);
//     waitpid(id, &status, 0);
//     waitpid(id2, &status, 0);
//     if (WIFEXITED(status))
//         return (WEXITSTATUS(status));
//     exit(EXIT_SUCCESS);
// }
int main(int ac, char **argv, char **envp)
{
    int infile;
    int outfile;
    int fdes[2];
    char *pathname;
    int status;
    char **cmd_args;
    pid_t id;
    pid_t id2;

    if (!ft_parse_input(&infile, &outfile, ac, argv))
        return (1);
    if (!ft_initialise_pipes(fdes))
        return (1);
    if (infile >= 0)
    {
        id = fork();
        if (id == 0)
        {
            // run_child(infile, fdes, READ)
            close(fdes[0]);
            dup2(infile, STDIN_FILENO);
            dup2(fdes[1], STDOUT_FILENO);
            cmd_args = ft_split(argv[2], ' ');
            pathname = ft_search_pathname(envp, cmd_args[0]);
            if (!pathname)
            {
                perror("First fail");
                free_splits(cmd_args);
                exit(127);
            }
            cmd_args = ft_split(argv[2], ' ');
            close(fdes[1]);
            if (execve(pathname, cmd_args, envp) == -1)
            {
                free(pathname);
                free_splits(cmd_args);
                perror("Execve failed");
                exit(127);
            }
        }
    }
    id2 = fork();
    if (id2 == 0)
    {
        // run_child(outfile, fdes, WRITE);
        close(fdes[1]);
        dup2(outfile, STDOUT_FILENO);
        dup2(fdes[0], STDIN_FILENO);
        cmd_args = ft_split(argv[3], ' ');
        pathname = ft_search_pathname(envp, cmd_args[0]);
        if (!pathname)
        {
            perror("Path fail");
            free_splits(cmd_args);
            exit(127);
        }
        close(fdes[0]);
        if (execve(pathname, cmd_args, envp) < 0)
        {
            free(pathname);
            free_splits(cmd_args);
            perror("Execve failed");
            exit(127);
        }
    }
    close(fdes[1]);
    close(fdes[0]);
    if (infile >= 0)
        waitpid(id, &status, 0);
    waitpid(id2, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    exit(EXIT_SUCCESS);
}
