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

void	ft_execute_execve(t_data *data)
{
	char	*pathname;
	char	**cmd_args;

	ft_execve_args(&cmd_args, &pathname, data->argv[data->i], data->envp);
	if (!pathname)
	{
		write(2, "command not found: ", 19);
		write(2, data->argv[data->i], ft_strlen(data->argv[data->i]));
		write(2, "\n", 1);
		free_splits(cmd_args);
		free(data);
		exit(127);
	}
	if (execve(pathname, cmd_args, data->envp) == -1)
		ft_handle_exit(data->argv[data->i], &cmd_args, data);
}

void	ft_dup_it(t_data *data, int mode)
{
	if (mode == OUTFILE)
	{
		if (dup2(data->out, STDOUT_FILENO) < 0)
			ft_dup_failed();
	}
	else if (mode == INFILE)
	{
		if (dup2(data->in, STDIN_FILENO) < 0)
			ft_dup_failed();
	}
	else if (mode == WRITE_END)
	{
		if (dup2(data->pipefdes[data->j + 1], STDOUT_FILENO) < 0)
			ft_dup_failed();
	}
	else if (mode == READ_END)
	{
		if (dup2(data->pipefdes[data->j - 2], STDIN_FILENO) < 0)
			ft_dup_failed();
	}
}

void	ft_exec_child(t_data *data)
{
	if (data->i != (data->ac - 2))
	{
		if (data->j == 0)
			ft_dup_it(data, INFILE);
		ft_dup_it(data, WRITE_END);
	}
	if (data->j != 0)
	{
		if (data->i == (data->ac - 2))
			ft_dup_it(data, OUTFILE);
		ft_dup_it(data, READ_END);
	}
	ft_close_fdes(data);
	ft_execute_execve(data);
}
