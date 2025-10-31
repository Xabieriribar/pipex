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

void	ft_exec_read_child(int fdes[2], char **argv, char **envp, int *infile)
{
	char	*pathname;
	char	**cmd_args;

	close(fdes[0]);
	dup2(*infile, STDIN_FILENO);
	dup2(fdes[1], STDOUT_FILENO);
	ft_execve_args(&cmd_args, &pathname, argv[2], envp);
	if (!pathname)
		ft_handle_exit("Pathname failed", cmd_args, pathname);
	close(fdes[1]);
	if (execve(pathname, cmd_args, envp) == -1)
		ft_handle_exit("Execve failed", cmd_args, pathname);
}

void	ft_exec_write_child(int fdes[], char **argv, char **envp, int *outfile)
{
	char	*pathname;
	char	**cmd_args;

	close(fdes[1]);
	dup2(*outfile, STDOUT_FILENO);
	dup2(fdes[0], STDIN_FILENO);
	ft_execve_args(&cmd_args, &pathname, argv[3], envp);
	if (!pathname)
		ft_handle_exit("Pathname failed", cmd_args, pathname);
	close(fdes[0]);
	if (execve(pathname, cmd_args, envp) == -1)
		ft_handle_exit("Execve failed", cmd_args, pathname);
}

int	main(int ac, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		fdes[2];
	int		status;
	pid_t	id;

	if (!ft_parse_input(&infile, &outfile, ac, argv)
		|| !ft_initialise_pipes(fdes))
		return (1);
	if (infile != -1)
	{
		id = fork();
		if (id == 0)
			ft_exec_read_child(fdes, argv, envp, &infile);
	}
	id = fork();
	if (id == 0)
		ft_exec_write_child(fdes, argv, envp, &outfile);
	ft_close_fdes(fdes);
	if (infile >= 0)
		waitpid(id, &status, 0);
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	exit(EXIT_SUCCESS);
}
