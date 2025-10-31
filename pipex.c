#include "pipex.h"
#include "pipex_utils.c"
#include "stdio.h"

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
            close(fdes[0]);
            infile = ft_dup_it(infile);
            dup2(infile, STDIN_FILENO);
            dup2(fdes[1], STDOUT_FILENO);
            ft_get_execve_args(&cmd_args, &pathname, argv[2], envp);
            if (!pathname)
                ft_handle_exit("Pathname failed", cmd_args, pathname);
            close(fdes[1]);
            if (execve(pathname, cmd_args, envp) == -1)
                ft_handle_exit("Execve failed", cmd_args, pathname);
        }
    }
    id2 = fork();
    if (id2 == 0)
    {
        close(fdes[1]);
		dup2(outfile, STDOUT_FILENO);
		dup2(fdes[0], STDIN_FILENO);
        ft_get_execve_args(&cmd_args, &pathname, argv[3], envp);
        if (!pathname)
            ft_handle_exit("Path failed", cmd_args, NULL);
        close(fdes[0]);
        if (execve(pathname, cmd_args, envp) < 0)
            ft_handle_exit("Execve failed", cmd_args, pathname);
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
