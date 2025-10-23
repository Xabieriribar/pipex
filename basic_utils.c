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
static void	free_split(char **strs, size_t used)
{
	size_t	index;

	index = 0;
	while (index < used)
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*dup_word(char const *start, size_t len)
{
	char	*word;
	size_t	index;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	index = 0;
	while (index < len)
	{
		word[index] = start[index];
		index++;
	}
	word[index] = '\0';
	return (word);
}

static int	extract_word(char const **s, char c, char **slot)
{
	size_t		len;
	char const	*start;

	while (**s && **s == c)
		(*s)++;
	if (**s == '\0')
		return (0);
	start = *s;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	*slot = dup_word(start, len);
	if (!*slot)
		return (-1);
	*s += len;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**strs;
	size_t		i;
	size_t		words;
	int			status;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = malloc((words + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < words)
	{
		status = extract_word(&s, c, &strs[i]);
		if (status < 0)
			return (free_split(strs, i), NULL);
		if (status == 0)
			break ;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*temp_new;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	temp_new = new_str;
	while (*s1)
	{
		*new_str = *s1;
		new_str++;
		s1++;
	}
	while (*s2)
	{
		*new_str = *s2;
		new_str++;
		s2++;
	}
	*new_str = '\0';
	return (temp_new);
}

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

