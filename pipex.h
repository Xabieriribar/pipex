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
#include <sys/types.h>
#include <sys/wait.h>

int ft_check_access(char *pathname);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char *ft_search_pathname(char **envp, char *argv);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
#endif
