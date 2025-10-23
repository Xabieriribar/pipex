/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:07:16 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/03 09:07:27 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <bsd/string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[j + i] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	printf("<<< SUPER TEST FT_STRNSTR >>>\n");
	printf("Is little empty?\n");
	printf("What does their function say?\n");
	printf("Test 1: %s\n", strnstr("lorem ipsum dolor sit amet", "ipsum", 15));
	printf("Test 2: %s\n", strnstr("lorem ipsum dolor sit amet", "dolor", 15));
	printf("Test 3: %s\n", strnstr("lorem ipsum dolor sit amet", "lorem", 15));
	printf("What does our function say?\n");
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15));
	//printf("Test 2: %s\n", ft_strnstr("lorem ipsum", "dolor", 15));
	printf("Test 3: %s\n", ft_strnstr("lorem ipsum dolor", "lorem", 15));
}*/
