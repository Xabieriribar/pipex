/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:09:16 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/01 11:09:18 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
// int main()
// {
// 	printf("<<< NORMAL TEST >>>\n");
// 	printf("Real function:\n");
// 	printf("My function:\n");
// 	printf("<<< EDGE TEST >>>\n");
// 	printf("Real function:\n");
// 	printf("My function:\n");
// }