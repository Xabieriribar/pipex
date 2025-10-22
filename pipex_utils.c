#include "pipex.h"
// int ft_check_access(int ac, char **av)
// {
//     if ((access(av[0], F_OK)) == -1)
//     {
//         perror(av[0]);
//         return (-1);
//     }
//     else if ((access(av[ac - 1], F_OK)) == -1)
//     {
//         perror(av[ac - 1]);
//         return (-1);
//     }
//     else
//         return (1);
// }
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[j + i] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

int ft_check_routes(char **envp)
{
    int i;
    char *path;
    
    i = 0;
    while (envp[i] != NULL)
    {
        if ((path = ft_strnstr(envp[i], "PATH=", 6)) != NULL)
        {
            printf("%s", path + 5);
            return (1);
        }
        i++;
    }
    return (0);
}
int main(int ac, char **argv, char **envp)
{
    ft_check_routes(envp);
    return (0);
}

