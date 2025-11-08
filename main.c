/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:18:03 by xiribar           #+#    #+#             */
/*   Updated: 2025/11/05 15:18:03 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_wait_childs(int ac, int *status, int id)
{
	int		i;

	i = 0;
	while (i < ac - 2)
	{
		waitpid(id, status, 0);
		i++;
	}
}

void	ft_execute_execve(char **argv, char **envp, int i)
{
	char	*pathname;
	char	**cmd_args;

	ft_execve_args(&cmd_args, &pathname, argv[i], envp);
	if (!pathname)
		ft_handle_exit(argv[i], cmd_args, pathname);
	if (execve(pathname, cmd_args, envp) == -1)
		ft_handle_exit(argv[i], cmd_args, pathname);
}

void	ft_dup_it(int *file, int fdes[], int mode, int j_index)
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
		else
			exit(EXIT_FAILURE);
	}
	else if (mode == WRITE_END)
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

void	ft_exec_child(t_data *data)
{
	if (data->i != (data->ac - 2))
	{
		if (data->j == 0)
			ft_dup_it(&data->in, data->pipefdes, INFILE, 0);
		ft_dup_it(0, data->pipefdes, WRITE_END, data->j);
	}
	if (data->j != 0)
	{
		if (data->i == (data->ac - 2))
			ft_dup_it(&data->out, data->pipefdes, OUTFILE, 0);
		ft_dup_it(0, data->pipefdes, READ_END, data->j);
	}
	ft_close_fdes(data->pipefdes, data->ac);
	ft_execute_execve(data->argv, data->envp, data->i);
}
