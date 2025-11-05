/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:37:24 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/22 14:37:25 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# ifndef OUTFILE
# define OUTFILE 1
# endif

#ifndef MAX_PIPES
#define MAX_PIPES 10000
#endif

#ifndef INFILE
#define INFILE 0
#endif

#ifndef READ_END
#define READ_END 0
#endif

#ifndef WRITE_END
#define WRITE_END 1
#endif

typedef struct  s_data
{
	int     in;
	int     ac;
	int     out;
	int     status;
	int     i;
	int     j;
	int     *pipefdes;
	char    **argv;
	char    **envp;
}   t_data;

void		free_splits(char **strs);
void		ft_close_fdes(int fdes[], int ac);
void		ft_execve_args(char ***cmds, char **path, char *cmd, char **envp);
void		ft_handle_exit(char *str, char **cmd_args, char *pathname);
int			ft_check_access(char *pathname);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_search_pathname(char **envp, char *cmd);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strdup(const char *s);
size_t      ft_strlen(const char *s);
void        ft_fork_error(void);
void        ft_dup_failed(void);
void        ft_wait_childs(int ac, int *status, int id);
void        ft_exec_child(t_data *data);
int			ft_parse_input(int *infile, int *outfile, int ac, char **argv);
int			ft_initialise_pipes(int pipefdes[], int ac);
char		*ft_check_routes(char **envp);
#endif
