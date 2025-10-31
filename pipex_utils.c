#include "pipex.h"


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

void	free_splits(char **strs)
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

int ft_check_and_split(char **temp, char ***dirs, char **envp)
{
	*temp = ft_check_routes(envp);
	*dirs = ft_split(*temp, ':');	
	if (!*dirs)
		return (1);
	return (0);
}

char *ft_search_pathname(char **envp, char *cmd)
{
	char *temp;
	char **dirs;
	char *full_path;
	char *candidate;
	int i;

	i = -1;
	full_path = NULL;
	if (ft_check_and_split(&temp, &dirs, envp))
		return (NULL);
	while (dirs[++i])
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
	}
	return (free_splits(dirs), full_path);
}

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
void	ft_close_fdes(int fdes[2])
{
	close(fdes[0]);
	close(fdes[1]);
}