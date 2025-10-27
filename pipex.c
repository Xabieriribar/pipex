#include "pipex.h"

int main(int ac, char **argv, char **envp)
{
    int fdes[2];
    char *pathname;
    int infile;
    int outfile;
    char **cmd_args;
    pid_t id;

    if (ac != 5)
        return (printf("The program should be executed as follows: ./pipex file1 cmd1 cmd2 file2\n"), 1);
    if (!ft_file_exists(argv))
        return (0);
    if ((infile = open(argv[1], O_RDONLY | O_CREAT | O_TRUNC, 0777)) < 0)
        return (perror("open"), 0);
    if ((outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC), 0777) < 0)
        return (perror("open"), 0);
    if (pipe(fdes) < 0)
    {
        perror("pipe");
        return (-2);
    }
    id = fork();
    if (id == 0)
    {
        close(fdes[0]);
        dup2(infile, STDIN_FILENO);
        dup2(fdes[1], STDOUT_FILENO);
        pathname = ft_search_pathname(envp, argv[2]);
        cmd_args = ft_split(argv[2], ' ');
        close(fdes[1]);
        if (execve(pathname, cmd_args, envp) < 0)
            perror("Error");
        exit(0);
    }
    id = fork();
    if (id == 0)
    {
        close(fdes[1]);
        dup2(outfile, STDOUT_FILENO);
        dup2(fdes[0], STDIN_FILENO);
        pathname = ft_search_pathname(envp, argv[3]);
        cmd_args = ft_split(argv[3], ' ');
        close(fdes[0]);
        if (execve(pathname, cmd_args, envp) < 0)
            perror("Error");
        exit(0);
    }
    close(fdes[1]);
    close(fdes[0]);
    waitpid(id,NULL, 0);
    waitpid(id, NULL, 0);
    return (0);
}
