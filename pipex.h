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
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef READ 
#define READ 0
#endif

#ifndef WRITE
#define WRITE 1
#endif

static void	free_splits(char **strs);
int ft_check_access(char *pathname);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char *ft_search_pathname(char **envp, char *cmd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s);
void	ft_putendl_fd(char *s, int fd);
int	ft_printf(const char *format, ...);
int	ft_file_exists(char **argv);
#endif
