/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:08:25 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/01 14:08:29 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_temp;
	unsigned char	c_temp;

	s_temp = (unsigned char *)s;
	c_temp = (unsigned char)c;
	while (n > 0)
	{
		if (*s_temp == c_temp)
			return (s_temp);
		s_temp++;
		n--;
	}
	return (NULL);
}
