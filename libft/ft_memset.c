/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:10:31 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/01 11:10:33 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*byte;

	byte = s;
	while (n > 0)
	{
		*byte = c;
		byte++;
		n--;
	}
	return (s);
}
/*
int main(void)
{
	int mem_size = 15;
	printf("ft_memset: %p", ft_memset(1234, 3, 4));
	return 0;
}*/