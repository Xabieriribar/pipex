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


void ft_wait_childs(int ac, int *status, int id)
{
	int i;

	i = 0;
	while (i < ac - 2)
	{
		waitpid(id, status, 0);
		i++;
		if (i == ac - 2)
			break ;
	}
}

void	ft_execute_execve(char **argv, char **envp, int i)
{
	char	*pathname;
	char	**cmd_args;

	ft_execve_args(&cmd_args, &pathname, argv[i], envp);
	// if (!pathname && i != 2)
	// 	ft_handle_exit(argv[i], cmd_args, pathname);

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
		else if (mode == INFILE && *file != -1)
		{
			if (dup2(*file, STDIN_FILENO) < 0)
				ft_dup_failed();
		}
		else
			exit(EXIT_FAILURE);
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

int	ft_pipex(int ac, char **argv, char **envp, t_data *data)
{
	int		i;
	int		j;
	int		status;
	pid_t	id;

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
					ft_dup_it(&data->in, data->pipefdes, INFILE, 0);
				ft_dup_it(0, data->pipefdes, WRITE_END, j);
			}
			if (j != 0)
			{
				if (i == ac - 2)
					ft_dup_it(&data->out, data->pipefdes, OUTFILE, 0);
				ft_dup_it(0, data->pipefdes, READ_END, j);
			}
			ft_close_them(data->pipefdes, i);
			ft_execute_execve(argv, envp, i);
		}
		else if (id < 0)
			ft_fork_error();
		j += 2;
	}
	ft_close_fdes(data->pipefdes, ac);
	ft_wait_childs(ac, &status, id);
	return (status);
}

int	main(int ac, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	t_data	*data;
	int		*pipefdes;
	int		status;

	if (ac <= 3)
	{
		write(1, "Usage: ./pipex file1 cmd1 cmd2 file2", 37);
		return (write(2, "\n", 1), 1);
	}
	if (!ft_parse_input(&infile, &outfile, ac, argv))
		return (1);
	ft_initialise_pipes(&pipefdes, ac);
	if (pipefdes == 0)
		return (1);
	data = malloc(sizeof(struct s_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->in= infile;
	data->out= outfile;
	data->ac = ac;
	data->pipefdes = pipefdes;
	status = ft_pipex(ac, argv, envp, data);
	if (WIFEXITED(status))
		{
			free(data);
			return (WEXITSTATUS(status));
		}
	free(data);
	exit(EXIT_SUCCESS);
}
