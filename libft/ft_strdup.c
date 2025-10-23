/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:50:05 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/03 08:50:14 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*temp_dest;

	temp_dest = dest;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (temp_dest);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		s_len;

	s_len = ft_strlen(s);
	dup = malloc(s_len + 1);
	if (!dup)
		return (NULL);
	dup = ft_strcpy(dup, s);
	return (dup);
}
/*int main(void)
{
	char    s[] = "hola amigos";
	char    *copy;
	copy = ft_strdup(s);
	printf("Result: %s\n", copy);
	return (0);
}*/