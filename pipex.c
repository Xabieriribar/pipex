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

void	ft_execute_execve(char **argv, char **envp, int i)
{
	char	*pathname;
	char	**cmd_args;

	ft_execve_args(&cmd_args, &pathname, argv[i], envp);
	if (execve(pathname, cmd_args, envp) == -1)
		ft_handle_exit(argv[i], cmd_args, pathname);
}


void	ft_close_them(int fdes[], int i)
{
	int		k;

	k = 0;
	while (k < i)
		close(fdes[k++]);

}

void	ft_fork_error()
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

void	ft_dup_failed()
{
	perror("Dup failed");
	exit(EXIT_FAILURE);
}

void ft_dup_it(int *file, int fdes[], int mode, int j_index)
{
	if (file != 0)
	{
		if (mode == OUTFILE)
		{
			if (dup2(*file, STDOUT_FILENO) < 0)
				ft_dup_failed();
		}
		else if (mode == INFILE)
		{
			if (dup2(*file, STDIN_FILENO) < 0)
				ft_dup_failed();
		}
	}
	else
	{
		if (mode == WRITE_END)
		{
			if (dup2(fdes[j_index + 1], STDOUT_FILENO) < 0)
				ft_dup_failed();
		}
		else if (mode == READ_END)
		{
			if (dup2(fdes[j_index - 2], STDIN_FILENO) < 0)
				ft_dup_failed();
		}
	}
}


int	main(int ac, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		fdes[(ac - 4) * 2];
	int j;
	int		status;
	int		i;
	pid_t	id;

	if (!ft_parse_input(&infile, &outfile, ac, argv)
		|| !ft_initialise_pipes(fdes, ac))
		return (1);
	j = 0;
	i = 1;
	while (++i < ac - 1)
	{
		id = fork();
		if (id == 0)
		{
			if (i != ac - 2)
			{
				if (j == 0)
					ft_dup_it(&infile, fdes, INFILE, 0);
				ft_dup_it(0, fdes, WRITE_END, j);
			}
			if (j != 0)
			{
				if (i == ac - 2)
					ft_dup_it(&outfile, fdes, OUTFILE, 0);
				ft_dup_it(0, fdes, READ_END, j);
			}
			ft_close_them(fdes, i);
			ft_execute_execve(argv, envp, i);
		}
		else if (id < 0)
			ft_fork_error();
		j += 2;
	}
	ft_close_fdes(fdes, ac);
	i = 0;
	while (i < ac - 2)
	{
		waitpid(id, &status, 0);
		i++;
		if (i == ac - 2)
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
	}
	exit(EXIT_SUCCESS);
}
