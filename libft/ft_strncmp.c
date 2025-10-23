/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:20:51 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/03 11:20:52 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <bsd/string.h>
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	while ((*s1_temp != '\0' || *s2_temp != '\0') && n > 0)
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
	printf("<<< HYPER EFFECTIVE FT_STRNCMP TESTER >>>\n");
	printf("What we expect:\n");
	printf("Test 1: %d\n", strncmp("salut","salut", 5));
	printf("Test 2: %d\n", strncmp("test","testss", 7));
	printf("Test 3: %d\n", strncmp("test\0","test\200", 6));
	printf("What we got:\n");
	printf("Test 1: %d\n", ft_strncmp("salut","salut", 5));
	printf("Test 2: %d\n", ft_strncmp("test","testss", 7));
	printf("Test 3: %d\n", ft_strncmp("test\0","test\200", 6));
}*/
