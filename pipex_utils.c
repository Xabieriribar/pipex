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

char *ft_search_pathname(char **envp, char *argv)
{
	char *path;
	char **pathname;
	char **argv_split;
	int  i;

	i = 0;
	argv_split = ft_split(argv, ' ');
	path = ft_check_routes(envp);
	pathname = ft_split(path, ':');
	while (pathname[i])
	{
		pathname[i] = ft_strjoin(pathname[i], "/");
		pathname[i] = ft_strjoin(pathname[i], argv_split[0]);
		i++;
	}
	i = 0;
	while (pathname[i])
	{
		if (ft_check_access(pathname[i]) == 0)
			return (pathname[i]);
		i++;
	}
	return (NULL);
}

int	ft_file_exists(int ac, char **argv)
{
	if (ft_check_access(argv[1]) == -1 || ft_check_access(argv[ac - 1])== -1)
	{
		ft_printf("errno: %s", strerror(errno));
		exit(-1);
	}
	return (-1);
}