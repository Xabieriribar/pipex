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

int ft_check_access(int ac, char **av);
char *ft_check_routes(char **envp);
char	**ft_split(char const *s, char c);
#endif
