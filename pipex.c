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

void	ft_fork_error(void)
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

void	ft_dup_failed(void)
{
	perror("Dup failed");
	exit(EXIT_FAILURE);
}

int	ft_pipex(int ac, char **argv, char **envp, t_data *data)
{
	pid_t	id;

	data->argv = argv;
	data->envp = envp;
	data->ac = ac;
	while (++data->i < ac - 1)
	{
		id = fork();
		if (id == 0)
			ft_exec_child(data);
		else if (id < 0)
			ft_fork_error();
		data->j += 2;
	}
	ft_close_fdes(data->pipefdes, ac);
	ft_wait_childs(ac, &data->status, id);
	if (WIFEXITED(data->status))
		return (WEXITSTATUS(data->status));
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	t_data	*data;
	int		pipefdes[MAX_PIPES];

	if (!ft_parse_input(&infile, &outfile, ac, argv)
		|| !ft_initialise_pipes(pipefdes, ac))
		return (1);
	data = malloc(sizeof(struct s_data));
	if (!data)
		exit(EXIT_FAILURE);
	if (infile != -1)
		data->in = infile;
	data->out = outfile;
	data->status = 0;
	data->pipefdes = pipefdes;
	data->i = 1;
	data->j = 0;
	data->status = ft_pipex(ac, argv, envp, data);
	if (data->status == 127)
		return (free(data), WEXITSTATUS(32512));
	close(data->out);
	close(data->in);
	return (free(data), 0);
}
