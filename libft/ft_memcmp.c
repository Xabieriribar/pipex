/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:54:22 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/01 12:54:22 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s1_temp != *s2_temp)
			return (*s1_temp - *s2_temp);
		s1_temp++;
		s2_temp++;
		n--;
	}
	return (0);
}
/*
int main()
{
	printf("Test 1: %d\n", ft_memcmp("salut", "salut", 5));
	printf("Test 2: %d\n", ft_memcmp("t\200", "t\0", 2));
	printf("Test 3: %d\n", ft_memcmp("testss", "test", 5));
	printf("Test 4: %d\n", ft_memcmp("", "test", 4));
	printf("Test 5: %d\n", ft_memcmp("test", "tEst", 4));
	printf("Test 6: %d\n", ft_memcmp("test", "", 4));
	printf("Test 7: %d\n", ft_memcmp("abcdefghij", "abcdefgxyz", 7));
	printf("Test 8: %d\n", ft_memcmp("abcdefgh", "abcdwxyz", 6));
	printf("Test 9: %d\n", ft_memcmp("zyxbcdefgh", "abcdefgxyz", 0));
	return (0);
}*/