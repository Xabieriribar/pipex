/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:59:47 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/03 13:59:48 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*temp_new;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	temp_new = new_str;
	while (*s1)
	{
		*new_str = *s1;
		new_str++;
		s1++;
	}
	while (*s2)
	{
		*new_str = *s2;
		new_str++;
		s2++;
	}
	*new_str = '\0';
	return (temp_new);
}
/*
int main()
{
	printf("<<< SUPREME FT_STRJOIN TESTER >>>\n");
	printf("Test 1: %s\n", ft_strjoin("lorem ipsum", " dolor sit amet"));
}*/