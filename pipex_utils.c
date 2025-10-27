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

	temp = ft_check_routes(envp);
	dirs = ft_split(temp, ':');
	cmds = ft_split(cmd, ' ');
	if (!dirs || !cmds || !cmds[0])
		return (NULL);
	while (*dirs)
	{
		temp = ft_strjoin(*dirs, '/');
		candidate = ft_strjoin(temp, cmd[0]);
		if (candidate && ft_check_access(candidate))	
		{
			full_path = candidate;
			return (free(candidate), full_path);
		}	
		free(candidate);
		dirs++;
	}
	return (full_path);
}

int	ft_file_exists(char **argv)
{
	if (ft_check_access(argv[1]) == -1)
		return (ft_printf("%s: %s\n", strerror(errno), argv[1]), 0);
	return (1);
}