/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:34:30 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/31 16:34:31 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_parse_input(int *infile, int *outfile, int ac, char **argv)
{
	int	i;

	i = 0;
	if (ac == 100)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2", 36);
		return (write(2, "\n", 1), 0);
	}
	*infile = open(argv[1], O_RDONLY, 0644);
	if (*infile < 0)
	{
		while (argv[1][i])
		{
			write(2, &argv[1][i], 1);
			i++;
		}
		write(2, ":", 1);
		write(2, " ", 1);
		perror(NULL);
	}
	*outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		return (perror("Open failed"), 0);
	return (1);
}

/*
This function takes the file descriptors and the number of arguments the user introduced and opens n - 2 pipes using the pipe function. For example, if we have an input of ./pipex infile cat cat cat hostname, since the number of arguments (ac)
is 5, it will open 5 - 2 pipes*/
int	ft_initialise_pipes(int fdes[], int ac)
{
	int i;

	i = 0;
	while (i < ac - 2)
	{
		if (pipe(fdes + i) < 0)
			return (perror("Pipe failed"), 0);
		i += 2;
	}
	return (1);
}

int	ft_check_access(char *pathname)
{
	if ((access(pathname, F_OK) == 0))
		return (0);
	else
		return (-1);
}

void	ft_handle_exit(char *str, char **cmd_args, char *pathname)
{
	if (pathname != NULL)
		free(pathname);
	perror(str);
	free_splits(cmd_args);
	exit(127);
}

char	*ft_check_routes(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		path = ft_strnstr(envp[i], "PATH=", 6);
		if (path != NULL)
			return (path + 5);
		i++;
	}
	return (NULL);
}
