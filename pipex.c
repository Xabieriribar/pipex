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
    int execve_return;
    pid_t id;
    pid_t id2;

    if (!argv[2] || !argv[4])
        return (0);
    if (ac != 5)
        return (printf("The program should be executed as follows: ./pipex file1 cmd1 cmd2 file2\n"), 1);

    // if (!ft_file_exists(argv))
    //     return (0);
    status = 0;
    infile = open(argv[1], O_RDONLY, 0644);
    if (infile < 0)
        perror("open");
    if ((outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
        return (perror("open"), 0);
    if (pipe(fdes) < 0)
    {
        perror("pipe");
        return (-2);
    }
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

        
        execve_return = execve(pathname, cmd_args, envp)
        if (execve_return < 0)
            ft_handle_execve_error(pathname, cmd_args);
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
