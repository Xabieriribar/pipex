#include "pipex.h"

// void	ft_dup_it(int file, int *fdes, int mode)
// {
// 	if (mode == 1)
// 	{
//             dup2(file, STDIN_FILENO);
//             dup2(fdes[1], STDOUT_FILENO);
// 	}
// 	else if (mode == 0)
// 	{
// 		dup2(file, STDOUT_FILENO);
// 		dup2(fdes[0], STDIN_FILENO);
// 	}

// }

int	ft_parse_input(int *infile, int *outfile, int ac, char **argv)
{
	if (ac != 5)
		return (perror("Introduce at 4 arguments."), 0);
	*infile = open(argv[1], O_RDONLY, 0644);
	if (*infile < 0)
	{
		perror("Open failed");
	}
	*outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		return (perror("Open failed"), 0);
	}
	return (1);
}

int ft_initialise_pipes(int fdes[])
{
	if (pipe(fdes) < 0)
		return (perror("Pipe failed"), 0);
	return (1);
}
static void	free_splits(char **strs)
{
	size_t	index;

	index = 0;
	while (strs[index])
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}
int ft_check_access(char *pathname)
{
	if ((access(pathname, F_OK) == 0))
		return (0);
	else
		return (-1);
}

char *ft_check_routes(char **envp)
{
    int i;
    char *path;
    
    i = 0;
    while (envp[i] != NULL)
    {
        if ((path = ft_strnstr(envp[i], "PATH=", 6)) != NULL)
			return (path + 5);
        i++;
    }
    return (NULL);
}

char *ft_search_pathname(char **envp, char *cmd)
{
	char *temp;
	char **dirs;
	char *full_path;
	char *candidate;
	int i;

	i = 0;
	full_path = NULL;
	temp = ft_check_routes(envp);
	dirs = ft_split(temp, ':');
	if (!dirs)
		return (printf("wHAT"), NULL);
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		candidate = ft_strjoin(temp, cmd);
		if (candidate && ft_check_access(candidate) == 0)	
		{
			full_path = ft_strdup(candidate);
			free(temp);
			free_splits(dirs);
			return (free(candidate), full_path);
		}	
		free(temp);
		free(candidate);
		i++;
	}
	free_splits(dirs);
	return (full_path);
}

int	ft_file_exists(char **argv)
{
	if (ft_check_access(argv[1]) == -1)
		return (ft_printf("%s: %s\n", strerror(errno), argv[1]), 0);
	return (1);
}
// void ft_get_execve_args(char **cmd_args, char *pathname, char **envp)
// {
//         ft_search_pathname(envp, argv[2], &pathname);
//         cmd_args = ft_split(argv[2], ' ');
// }
void	ft_get_execve_args(char ***cmd_args, char **pathname, char *cmd, char **envp)
{
	*cmd_args = ft_split(cmd, ' ');
	*pathname = ft_search_pathname(envp, *cmd_args[0]);
}
void	ft_handle_exit(char *str, char **cmd_args, char *pathname)
{
	if (pathname != NULL)
		free(pathname);
	perror(str);
	free_splits(cmd_args);
	exit(127);
}
void	ft_close_fdes(int *fdes1, int *fdes2, int mode)
{
	if (mode == BOTH)
	{
		close(*fdes1);
		close(*fdes2);
	}
	else if (mode == WRITE)
	{
		close(*fdes1);
	}
	else if (mode == READ)
		close(*fdes2);
}