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
	if (ac <= 3)
		return (write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37), 1);
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
		*infile = open("/dev/null", O_RDONLY);
		if (*infile == -1)
			return (perror("/dev/null open failed"), 0);
		perror(NULL);
	}
	*outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		return (perror("Open failed"), 0);
	return (1);
}

int	ft_initialise_pipes(int pipefdes[], int ac)
{
	int		i;

	i = 0;
	while (i < ac - 3)
	{
		if (pipe(pipefdes + i * 2) < 0)
			return (perror("Pipe failed"), 0);
		i++;
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

void	ft_handle_exit(char *str, char ***cmd_args, t_data *data)
{
	perror(str);
	free_splits(*cmd_args);
	free(data);
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
