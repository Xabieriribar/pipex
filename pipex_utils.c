#include "pipex.h"

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
	char **cmds;
	char *candidate;
	char *full_path;
	int i;

	i = 0;
	full_path = NULL;
	temp = ft_check_routes(envp);
	dirs = ft_split(temp, ':');
	cmds = ft_split(cmd, ' ');
	if (!dirs || !cmds || !cmds[0])
		return (printf("wHAT"), NULL);
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		candidate = ft_strjoin(temp, cmds[0]);
		if (candidate && ft_check_access(candidate) == 0)	
		{
			full_path = ft_strdup(candidate);
			return (free(candidate), full_path);
		}	
		free(candidate);
		i++;
	}
	return (full_path);
}

int	ft_file_exists(char **argv)
{
	if (ft_check_access(argv[1]) == -1)
		return (ft_printf("%s: %s\n", strerror(errno), argv[1]), 0);
	return (1);
}