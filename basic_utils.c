#include "pipex.h"

int main(int ac, char **argv, char **envp)
{
	char	*path;
    path = ft_check_routes(envp);
	char **split = ft_split(path, ':');
	int i = 0;
	while (split[i])
	{
		split[i] = ft_strjoin(split[i], "/");
		split[i] = ft_strjoin(split[i], argv[1]);
		i++;
	}
	i = 0;
	while (split[i])
	{
		if ((access(split[i], F_OK)) == 0)
			return (split[i]);
		i++;
	}
    return (0);
}

