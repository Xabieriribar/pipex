/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:37:56 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/31 16:37:57 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splits(char **strs)
{
	size_t	index;

	index = 0;
	while (strs[index])
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}

int	ft_check_and_split(char **temp, char ***dirs, char **envp)
{
	*temp = ft_check_routes(envp);
	*dirs = ft_split(*temp, ':');
	if (!*dirs)
		return (1);
	return (0);
}

char	*ft_search_pathname(char **envp, char *cmd)
{
	char	*temp;
	char	**dirs;
	char	*full_path;
	char	*candidate;
	int		i;

	i = -1;
	full_path = NULL;
	if (ft_check_and_split(&temp, &dirs, envp))
		return (NULL);
	while (dirs[++i])
	{
		temp = ft_strjoin(dirs[i], "/");
		candidate = ft_strjoin(temp, cmd);
		if (candidate && ft_check_access(candidate) == 0)
		{
			full_path = ft_strdup(candidate);
			free(temp);
			free_splits(dirs);
			return (free(candidate), full_path);
		}
		free(temp);
		free(candidate);
	}
	return (free_splits(dirs), full_path);
}

void	ft_execve_args(char ***cmds, char **path, char *cmd, char **envp)
{
	char	**divide;
	int		i;

	i = 0;
	if (*cmd == '/')
	{
		divide = ft_split(cmd, ' ');
		if (ft_check_access(divide[0]) == 0)
		{
			*path = divide[0];
			*cmds = ft_split(cmd, ' ');
			return ;
		}
		else
		{
			*cmds = NULL;
			*path = NULL;
			return ;
		}
	}
	divide = NULL;
	*cmds = ft_split(cmd, ' ');
	*path = ft_search_pathname(envp, *cmds[0]);
}

void	ft_close_fdes(int fdes[], int ac)
{
	int i;
	
	i = 0;
	while (i < (ac - 4) * 2)
		close(fdes[i++]);
}
