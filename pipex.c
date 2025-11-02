/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:41:15 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/31 16:41:16 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	ft_exec_read_child(int fdes[], char **argv, char **envp, int *infile)
{
	char	*pathname;
	char	**cmd_args;

	close(fdes[0]);
	dup2(*infile, STDIN_FILENO);
	close(*infile);
	dup2(fdes[1], STDOUT_FILENO);
	ft_execve_args(&cmd_args, &pathname, argv[2], envp);
	close(fdes[1]);
	if (execve(pathname, cmd_args, envp) == -1)
		ft_handle_exit(argv[2], cmd_args, pathname);
}

void	ft_exec_write_child(int fdes[], char **argv, char **envp, int *outfile)
{
	char	*pathname;
	char	**cmd_args;

	close(fdes[1]);
	dup2(*outfile, STDOUT_FILENO);
	close(*outfile);
	dup2(fdes[0], STDIN_FILENO);
	ft_execve_args(&cmd_args, &pathname, argv[3], envp);
	close(fdes[0]);
	if (execve(pathname, cmd_args, envp) == -1)
		ft_handle_exit(argv[3], cmd_args, pathname);
}

int	main(int ac, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	char	*pathname;
	char	**cmd_args;
	int		fdes[(ac - 4) * 2];
	int j;
	int		status;
	int		i;
	pid_t	id;
	int		k;

	j = 0;
	i = 2;
	if (!ft_parse_input(&infile, &outfile, ac, argv)
		|| !ft_initialise_pipes(fdes, ac))
		return (1);
	j = 0;
	while (i < ac - 1)
	{
		id = fork();
		if (id == 0)
		{
			if (i != ac - 2)
			{
				if (dup2(fdes[j + 1], STDOUT_FILENO) < 0)
				{
					perror("Dup failed");
					exit(EXIT_FAILURE);
				}
				if (j == 0)
				{
					if (dup2(infile, STDIN_FILENO) < 0)
					{
						perror("Dup failed");
						exit(EXIT_FAILURE);
					}
					close(infile);
				}
			}
			if (i == 0)
			{
				if (dup2(fdes[j - 2], STDIN_FILENO) < 0)
				{
					perror("Dup failed");
					exit(EXIT_FAILURE);
				}
				if (j == ac - 2)
				{
					if (dup2(outfile, STDOUT_FILENO) < 0)
					{
						perror("Dup failed");
						exit(EXIT_FAILURE);
					}
					close(outfile);
				}
			}
			k = 0;
			while (k < ac - 2)
				close(fdes[k++]);
			ft_execve_args(&cmd_args, &pathname, argv[i], envp);
			if (execve(pathname, cmd_args, envp) == -1)
				ft_handle_exit(argv[i], cmd_args, pathname);
		}
		else
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		j += 2;
		i++;
	}
	ft_close_fdes(fdes, ac);
	i = 0;
	while (i < ac - 2)
	{
		printf("Waiting for %d child\n", id);
		waitpid(id, &status, 0);
		i++;
		if (i == ac - 1)
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
	}
	exit(EXIT_SUCCESS);
}
